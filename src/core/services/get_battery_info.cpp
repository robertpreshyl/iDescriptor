/*
 * iDescriptor: A free and open-source idevice management tool.
 *
 * Copyright (C) 2025 Uncore <https://github.com/uncor3>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include "../../iDescriptor.h"
#include "plist/plist.h"
#include <QDebug>
#include <libimobiledevice/diagnostics_relay.h>
#include <string>

void get_battery_info(std::string productType, idevice_t idevice,
                      bool is_iphone, plist_t &diagnostics)
{
    diagnostics_relay_client_t diagnostics_client = nullptr;
    try {

        if (diagnostics_relay_client_start_service(idevice, &diagnostics_client,
                                                   nullptr) !=
            DIAGNOSTICS_RELAY_E_SUCCESS) {
            qDebug() << "Failed to start diagnostics relay service.";
            return;
        }

        if (diagnostics_relay_query_ioregistry_entry(
                diagnostics_client, nullptr, "IOPMPowerSource", &diagnostics) !=
                DIAGNOSTICS_RELAY_E_SUCCESS &&
            !diagnostics) {

            qDebug()
                << "Failed to query diagnostics relay for AppleARMPMUCharger.";
            if (diagnostics_client)
                diagnostics_relay_client_free(diagnostics_client);
        }
    } catch (const std::exception &e) {
        if (diagnostics_client)
            diagnostics_relay_client_free(diagnostics_client);
        qDebug() << "Exception in get_battery_info: " << e.what();
    }
}