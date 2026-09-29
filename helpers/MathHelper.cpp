/*
 * Copyright (c) 2026 Tristan Israël
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
 *
 * https://opensource.org/license/mit/
 */

#include "MathHelper.h"
#include <QDebug>
#include "3rdParty/exprtk.hpp"

typedef exprtk::symbol_table<double> symbol_table_t;
typedef exprtk::expression<double> expression_t;
typedef exprtk::parser<double> parser_t;
typedef exprtk::parser_error::type error_t;

double MathHelper::computeFormula(const QString &formula, bool* ok)
{
    //Calculate the result
    symbol_table_t symbolTable;
    expression_t expression;
    parser_t parser;

    expression.register_symbol_table(symbolTable);
    qDebug() << "Compute formula" << formula;
    if(!parser.compile(formula.toStdString(), expression)) {
        qWarning() << QString::fromStdString(parser.error());
        if(ok != nullptr) {
            *ok = false;
        }
    } else {
        if(ok != nullptr) {
            *ok = true;
        }
        return expression.value();
    }

    return 0.0;
}
