/**
 ******************************************************************************
 *
 * @file       nucleo.cpp
 * @author     Tau Labs, http://taulabs.org, Copyright (C) 2013
 * @author     dRonin, http://dronin.org Copyright (C) 2015
 *
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup Boards_Stm STM boards support Plugin
 * @{
 * @brief Plugin to support boards by STM
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "nucleo.h"

#include <uavobjectmanager.h>
#include "uavobjectutil/uavobjectutilmanager.h"
#include <extensionsystem/pluginmanager.h>

#include "hwnucleo.h"
/**
 * @brief Nucleo::Nucleo
 *  This is the Flying F3 board definition
 */
Nucleo::Nucleo(void)
{
    // Initialize our USB Structure definition here:
    USBInfo board;
    board.vendorID = 0x20A0;
    board.productID = 0x415b;

    setUSBInfo(board);

    boardType = 0xBE;

    // Define the bank of channels that are connected to a given timer
    channelBanks.resize(6);
    channelBanks[0] = QVector<int> () << 1 << 2 << 3 << 4;
    channelBanks[1] = QVector<int> () << 5 << 6;
    channelBanks[2] = QVector<int> () << 7;
    channelBanks[3] = QVector<int> () << 8;
}

Nucleo::~Nucleo()
{

}

QString Nucleo::shortName()
{
    return QString("nucleo");
}

QString Nucleo::boardDescription()
{
    return QString("Nucleo");
}

//! Return which capabilities this board has
bool Nucleo::queryCapabilities(BoardCapabilities capability)
{
    switch(capability) {
    case BOARD_CAPABILITIES_GYROS:
    case BOARD_CAPABILITIES_ACCELS:
    case BOARD_CAPABILITIES_MAGS:
    case BOARD_CAPABILITIES_BAROS:
    case BOARD_CAPABILITIES_UPGRADEABLE:
        return true;
    default:
        return false;
    }
    return false;
}


/**
 * @brief Nucleo::getSupportedProtocols
 *  TODO: this is just a stub, we'll need to extend this a lot with multi protocol support
 * @return
 */
QStringList Nucleo::getSupportedProtocols()
{

    return QStringList("uavtalk");
}

QPixmap Nucleo::getBoardPicture()
{
    return QPixmap(":/stm/images/nucleo.jpg");
}

QString Nucleo::getHwUAVO()
{
    return "HwNucleo";
}

int Nucleo::queryMaxGyroRate()
{
    ExtensionSystem::PluginManager *pm = ExtensionSystem::PluginManager::instance();
    UAVObjectManager *uavoManager = pm->getObject<UAVObjectManager>();
    HwNucleo *hwNucleo = HwNucleo::GetInstance(uavoManager);
    Q_ASSERT(hwNucleo);
    if (!hwNucleo)
        return 0;

    HwNucleo::DataFields settings = hwNucleo->getData();

    switch(settings.GyroRange) {
    case HwNucleo::GYRORANGE_250:
        return 250;
    case HwNucleo::GYRORANGE_500:
        return 500;
    case HwNucleo::GYRORANGE_1000:
        return 1000;
    case HwNucleo::GYRORANGE_2000:
        return 2000;
    default:
        return 500;
    }
}
