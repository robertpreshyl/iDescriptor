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
#include <libimobiledevice/diagnostics_relay.h>
#include <libimobiledevice/libimobiledevice.h>
#include <plist/plist.h>

void get_cable_info(idevice_t device, plist_t &response)
{
    lockdownd_client_t lockdown_client = NULL;
    diagnostics_relay_client_t diagnostics_client = NULL;
    lockdownd_error_t ret = LOCKDOWN_E_UNKNOWN_ERROR;
    lockdownd_service_descriptor_t service = NULL;
    int use_network = 0;

    if (LOCKDOWN_E_SUCCESS != (ret = lockdownd_client_new_with_handshake(
                                   device, &lockdown_client, TOOL_NAME))) {
        idevice_free(device);
        printf("ERROR: Could not connect to lockdownd, error code %d\n", ret);
    }

    /*  attempt to use newer diagnostics service available on iOS 5 and later */
    ret = lockdownd_start_service(
        lockdown_client, "com.apple.mobile.diagnostics_relay", &service);
    if (ret == LOCKDOWN_E_INVALID_SERVICE) {
        /*  attempt to use older diagnostics service */
        ret = lockdownd_start_service(
            lockdown_client, "com.apple.iosdiagnostics.relay", &service);
    }
    lockdownd_client_free(lockdown_client);

    if (ret != LOCKDOWN_E_SUCCESS) {
        idevice_free(device);
        printf("ERROR: Could not start diagnostics relay service: %s\n",
               lockdownd_strerror(ret));
    }

    if ((ret == LOCKDOWN_E_SUCCESS) && service && (service->port > 0)) {
        if (diagnostics_relay_client_new(device, service,
                                         &diagnostics_client) !=
            DIAGNOSTICS_RELAY_E_SUCCESS) {
            printf("ERROR: Could not connect to diagnostics_relay!\n");
        }
    }

    diagnostics_relay_error_t err = diagnostics_relay_query_ioregistry_entry(
        diagnostics_client, NULL, "AppleTriStarBuiltIn", &response);

    if (diagnostics_client)
        diagnostics_relay_client_free(diagnostics_client);
}