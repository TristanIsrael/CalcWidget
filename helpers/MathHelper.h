/*
 * Copyright (c) 2026 Tristan Israël
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
 *
 * https://opensource.org/license/mit/
 */

#ifndef MATHHELPER_H
#define MATHHELPER_H

#include <QString>

class MathHelper
{
private:
    MathHelper(){}

public:    
    static double computeFormula(const QString&, bool *ok = nullptr);
};

#endif // MATHHELPER_H
