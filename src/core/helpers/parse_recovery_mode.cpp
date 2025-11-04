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

#include "libirecovery.h"
#include <string>

std::string parse_recovery_mode(irecv_mode productType)
{
    switch (productType) {
    case irecv_mode::IRECV_K_RECOVERY_MODE_1:
    case irecv_mode::IRECV_K_RECOVERY_MODE_2:
    case irecv_mode::IRECV_K_RECOVERY_MODE_3:
    case irecv_mode::IRECV_K_RECOVERY_MODE_4:
        return "Recovery Mode";
    case irecv_mode::IRECV_K_WTF_MODE:
        return "WTF Mode";
    case irecv_mode::IRECV_K_DFU_MODE:
    case irecv_mode::IRECV_K_PORT_DFU_MODE:
        return "DFU Mode";
    default:
        return "Unknown Mode";
    }
}
