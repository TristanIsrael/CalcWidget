/*
 * Copyright (c) 2026 Tristan Israël
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
 *
 * https://opensource.org/license/mit/
 */

#ifndef PARAMETERSDIALOG_H
#define PARAMETERSDIALOG_H

#include <QDialog>

namespace Ui {
class ParametersDialog;
}

class ParametersDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ParametersDialog(QWidget *parent = nullptr);
    ~ParametersDialog();

    void loadParameters();
    QKeySequence evaluateShortcut();
    QKeySequence getShortcut() const;
    int visibilityDuration() const;
    int precisionDigits() const;

signals:
    void parametersChanged();

private slots:
    void on_btnCancel_clicked();
    void on_btnOk_clicked();
    void on_keySequenceEdit_keySequenceChanged(const QKeySequence &);

private:
    Ui::ParametersDialog *ui;    
};

#endif // PARAMETERSDIALOG_H
