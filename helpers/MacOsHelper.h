/*
 * Copyright (c) 2026 Tristan Israël
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
 *
 * https://opensource.org/license/mit/
 */

#ifndef MACOSHELPER_H
#define MACOSHELPER_H

class MacOsHelper {
private:
    MacOsHelper() {}

public:
    static bool setAutostart(bool enabled = true);
};

#endif // MACOSHELPER_H
