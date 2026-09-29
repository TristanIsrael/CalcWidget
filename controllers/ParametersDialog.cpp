/*
 * Copyright (c) 2026 Tristan Israël
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
 *
 * https://opensource.org/license/mit/
 */

#include "controllers/ParametersDialog.h"
#include "ui_ParametersDialog.h"
#include <QDebug>
#include <QMessageBox>
#include <QToolTip>
#include <QSettings>
#include "MacOsHelper.h"
#include "ParametersHelper.hpp"

/*!
 * \brief This class defines the dialog with the settings of the app
 */
ParametersDialog::ParametersDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ParametersDialog)
{
    ui->setupUi(this);
    loadParameters();
}

ParametersDialog::~ParametersDialog()
{    
    delete ui;
}

/*!
 * \brief Loads the parameters from the settings file
 */
void ParametersDialog::loadParameters()
{
    QSettings settings;
    const auto& sequence = ParametersHelper::shortcut();
    ui->keySequenceEdit->setKeySequence(sequence);
    ui->visibilityDuration->setValue(ParametersHelper::visibilityDuration());
    ui->precisionDigits->setValue(ParametersHelper::precisionDigits());    
}

/*!
 * \brief Returns the shortcut defined in the settings
 */
QKeySequence ParametersDialog::getShortcut() const
{
    return ui->keySequenceEdit->keySequence();
}

/*!
 * \brief Verifies and reformats the shortcut if needed
 */
QKeySequence ParametersDialog::evaluateShortcut()
{
    auto sequence = ui->keySequenceEdit->keySequence();
    qDebug() << "Shortcut:" << sequence.toString();

    if(ui->keySequenceEdit->keySequence().isEmpty()) {        
        return QKeySequence();
    }

    // We accept only one component in the shortcut
    if(sequence.count() > 1) {
        qDebug() << "Sequence is to long, keeping only the first part";
        sequence = sequence[0];
        ui->keySequenceEdit->setKeySequence(sequence);        
        QMessageBox::warning(this, tr("Shortcut changed"), tr("This sequence has been truncated to the first key only"));
    }

    // mac OS Notice:
    // The key "Command" is enumerated as CTRL
    // The key "Option" is enumerated as ALT
    // The key "Control" is enumerated as Meta
    // So we need to invert CTRL and META

    qDebug() << "Analyze the sequence " << sequence;
    auto fixedSequence = sequence.toString();
    fixedSequence.replace("Ctrl", "FIXCTRL");
    fixedSequence.replace("Meta", "Ctrl");
    fixedSequence.replace("FIXCTRL", "Meta");
    qDebug() << "Sequence has been fixed to " << fixedSequence;

    return QKeySequence::fromString(fixedSequence);
}

/*!
 * \brief Returns the visibility duration setting
 */
int ParametersDialog::visibilityDuration() const
{
    return ui->visibilityDuration->value();
}

/*!
 * \brief Returns the precision digits setting
 */
int ParametersDialog::precisionDigits() const
{
    return ui->precisionDigits->value();
}

/*!
 * \brief Called when the cancel button has been clicked
 */
void ParametersDialog::on_btnCancel_clicked()
{
    reject();
}

/*!
 * \brief Called when the OK button has been clicked
 */
void ParametersDialog::on_btnOk_clicked()
{
    ParametersHelper::setVisibilityDuration(ui->visibilityDuration->value());
    ParametersHelper::setPrecisionDigits(ui->precisionDigits->value());

    if(!getShortcut().isEmpty()) {
        ParametersHelper::setShortcut(ui->keySequenceEdit->keySequence().toString());
        emit parametersChanged();

        accept();
    }
}

/*!
 * \brief Called when the shortcut has been changed
 */
void ParametersDialog::on_keySequenceEdit_keySequenceChanged(const QKeySequence&)
{
    const auto& sequence = ui->keySequenceEdit->keySequence();
    if(sequence.isEmpty())
        return;


}
