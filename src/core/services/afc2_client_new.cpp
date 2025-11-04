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
#include <QDebug>
#include <libimobiledevice/afc.h>
#include <libimobiledevice/libimobiledevice.h>
#include <libimobiledevice/lockdown.h>

afc_error_t afc2_client_new(idevice_t device, afc_client_t *afc)
{

    lockdownd_service_descriptor_t service = NULL;
    // TODO: should free service ?
    lockdownd_client_t client = NULL;

    if (lockdownd_client_new_with_handshake(device, &client, APP_LABEL) !=
        LOCKDOWN_E_SUCCESS) {
        qDebug() << "Could not connect to lockdownd";
        return AFC_E_UNKNOWN_ERROR;
    }
    if (lockdownd_start_service(client, AFC2_SERVICE_NAME, &service) !=
        LOCKDOWN_E_SUCCESS) {
        qDebug() << "Could not start AFC service";
        lockdownd_client_free(client);
        return AFC_E_UNKNOWN_ERROR;
    }

    return afc_client_new(device, service, afc);

    // char **dirs = NULL;
    // if (afc_read_directory(afc, argv[1], &dirs) == AFC_E_SUCCESS) {
    //     for (int i = 0; dirs[i]; i++) {
    //         printf("Entry: %s\n", dirs[i]);
    //     }
    //     // free(dirs);
    // }
}