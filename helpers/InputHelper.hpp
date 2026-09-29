/*
 * Copyright (c) 2026 Tristan Israël
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
 *
 * https://opensource.org/license/mit/
 */

#ifndef INPUTHELPER_HPP
#define INPUTHELPER_HPP

#include <QString>
#include <QLocale>
#include <QList>
#include <QDebug>

/*!
 * \brief This class provides helpers to handle the user inputs.
 */
class InputHelper {
private:
    static const QList<QChar> operators() {
        return QList<QChar>() << '+' << '-' << '/' << '*' << '^' << '%';
    }

public:
    /*!
     * \brief Reformats the user's input.
     *
     * This function replaces commas with dots in order to be computable.
     */
    static QString reformatInputNumber(const QString& number) {
        QString nnumber(number);
        nnumber.replace(",", ".");

        return nnumber;
    }

    /*!
     * \brief Verified whether the formula begins with an operator.
     *
     * When a formula begins with an operator it uses the previous result as the
     * first operand.
     */
    static bool isCumulatedFormula(const QString& formula) {
        // Verify whether formula starts with an operator
        if(formula.length() == 0) {
            return false;
        }

        if(operators().contains(formula.at(0))) {
            return true;
        }

        return false;
    }

};

#endif // INPUTHELPER_HPP
