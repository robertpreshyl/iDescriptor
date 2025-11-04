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
#include <libimobiledevice/afc.h>
// char *possible_jailbreak_paths[] = {
//     "/Applications/Cydia.app",
//     "/Library/MobileSubstrate/MobileSubstrate.dylib",
//     "/bin/bash",
//     "/usr/sbin/sshd",
//     "/etc/apt",
//     NULL
// };
#include <string>

bool detect_jailbroken(afc_client_t afc)
{
    char **dirs = NULL;
    if (afc_read_directory(afc, (std::string(POSSIBLE_ROOT) + "bin").c_str(),
                           &dirs) == AFC_E_SUCCESS) {
        // if we can loop through the directory, it means we have access to the
        // file system
        for (char **dir = dirs; *dir != nullptr; ++dir) {
            afc_dictionary_free(dirs);
            return true;
        }
    }
    afc_dictionary_free(dirs);
    return false;
}