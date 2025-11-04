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

// TODO: move function declarations to a header file
#include <regex>
#include <stdexcept>
#include <string>

struct ProductTypeVersion {
    int major;
    int minor;

    ProductTypeVersion(int maj = 0, int min = 0) : major(maj), minor(min) {}

    // Compare two product type versions
    // Returns: -1 if this < other, 0 if equal, 1 if this > other
    int compareTo(const ProductTypeVersion &other) const
    {
        if (major != other.major) {
            return major < other.major ? -1 : 1;
        }
        if (minor != other.minor) {
            return minor < other.minor ? -1 : 1;
        }
        return 0; // Equal
    }

    bool operator<(const ProductTypeVersion &other) const
    {
        return compareTo(other) < 0;
    }

    bool operator==(const ProductTypeVersion &other) const
    {
        return compareTo(other) == 0;
    }

    bool operator>(const ProductTypeVersion &other) const
    {
        return compareTo(other) > 0;
    }
};

// Extract version numbers from iPhone product type string
// Example: "iPhone8,1" -> ProductTypeVersion{8, 1}
ProductTypeVersion extractProductTypeVersion(const std::string &productType)
{
    // Regex to match iPhone followed by major,minor numbers
    std::regex pattern(R"(iPhone(\d+),(\d+))");
    std::smatch matches;

    if (std::regex_search(productType, matches, pattern)) {
        if (matches.size() >= 3) {
            try {
                int major = std::stoi(matches[1].str());
                int minor = std::stoi(matches[2].str());
                return ProductTypeVersion(major, minor);
            } catch (const std::invalid_argument &e) {
                throw std::invalid_argument(
                    "Invalid numeric values in product type: " + productType);
            }
        }
    }

    throw std::invalid_argument("Invalid iPhone product type format: " +
                                productType);
}

/* use it only for iPhones*/
bool compare_product_type(std::string productType, std::string otherProductType)
{
    try {
        ProductTypeVersion version1 = extractProductTypeVersion(productType);
        ProductTypeVersion version2 =
            extractProductTypeVersion(otherProductType);

        // Return true if productType is newer/higher than otherProductType
        return version1 > version2;
    } catch (const std::exception &e) {
        // Handle invalid product types - you might want to log this
        return false;
    }
}

// Additional utility functions for more specific comparisons
bool are_product_types_equal(const std::string &productType,
                             const std::string &otherProductType)
{
    try {
        ProductTypeVersion version1 = extractProductTypeVersion(productType);
        ProductTypeVersion version2 =
            extractProductTypeVersion(otherProductType);
        return version1 == version2;
    } catch (const std::exception &e) {
        return false;
    }
}

bool is_product_type_newer(const std::string &productType,
                           const std::string &otherProductType)
{
    return compare_product_type(productType, otherProductType);
}

bool is_product_type_older(const std::string &productType,
                           const std::string &otherProductType)
{
    try {
        ProductTypeVersion version1 = extractProductTypeVersion(productType);
        ProductTypeVersion version2 =
            extractProductTypeVersion(otherProductType);
        return version1 < version2;
    } catch (const std::exception &e) {
        return false;
    }
}