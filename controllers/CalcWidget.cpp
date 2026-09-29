/*
 * Copyright (c) 2026 Tristan Israël
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
 *
 * https://opensource.org/license/mit/
 */

#include "CalcWidget.h"
#include "ui_CalcWidget.h"
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QPropertyAnimation>
#include <QSize>
#include <QLocale>
#include <QClipboard>
#include <QKeyEvent>
#include "QHotkey"
#include "ParametersDialog.h"
#include "MathHelper.h"
#include "InputHelper.hpp"

/*!
 * \brief This is the main controller of the application
 */
CalcWidget::CalcWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalcWidget),
    hotkeyManager_(new QHotkey{this}),
    paramDialog_(new ParametersDialog{parent})
{
    ui->setupUi(this);
    resetFormulaColor();

    applyParameters();
    connect(paramDialog_, &ParametersDialog::parametersChanged, this, &CalcWidget::applyParameters);
    connect(paramDialog_, &ParametersDialog::parametersChanged, this, &CalcWidget::parametersChanged);

    hideTimer_.setSingleShot(true);
    connect(&hideTimer_, &QTimer::timeout, this, &CalcWidget::hideWindow);

    setWindowFlags(windowFlags() | Qt::Window | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
}

CalcWidget::~CalcWidget()
{
    delete ui;
}

/*!
 * \brief Resets the text color when a formula's syntax has been fixed
 */
void CalcWidget::resetFormulaColor()
{
    QPalette palette = ui->lineEdit->palette();
    if(ui->lineEdit->text().isEmpty()) {
        palette.setColor(QPalette::Text, Qt::white);
    }
    ui->lineEdit->setPalette(palette);
}

/*!
 * \brief Shows the parameters dialog
 */
void CalcWidget::showParametersDialog()
{
    if(paramDialog_->exec() == QDialog::Accepted) {
        applyParameters();
    }
}

/*!
 * \brief Shows the app window
 */
void CalcWidget::showWidget()
{
    ui->lineEdit->clear();
    ui->lblResult->clear();
    showNormal();
    raise();
    activateWindow();
    ui->lineEdit->setFocus();
    hideTimer_.start();
}

/*!
 * \brief Applies the parameters defined by the user
 */
void CalcWidget::applyParameters()
{    
    hideTimer_.setInterval(paramDialog_->visibilityDuration()*1000);
    reInstallShortcut();
}

/*!
 * \brief Installs the global shortcut to show the app
 */
bool CalcWidget::reInstallShortcut()
{
    if(paramDialog_->evaluateShortcut().isEmpty()) {
        qDebug() << "No shortcut defined.";
        QMessageBox warning;
        warning.setStyleSheet("background-color: lightgray");
        warning.setWindowTitle(tr("Configuration"));
        warning.setText(tr("No shortcut defined. Please mofify the settings."));
        warning.setIcon(QMessageBox::Warning);
        warning.exec();
        showParametersDialog();
        return false;
    }

    qDebug() << "Unregister hotkey";
    hotkeyManager_->resetShortcut();

    const auto sequence = paramDialog_->getShortcut();

    if(hotkey_ != nullptr) {
        delete hotkey_;
    }

    qDebug() << "Register hotkey" << sequence.toString();
    hotkey_ = new QHotkey{sequence, true, this};
    if(!hotkey_->isRegistered()) {
        QMessageBox warning;
        warning.setStyleSheet("background-color: lightgray");
        warning.setWindowTitle(tr("Configuration"));
        warning.setText(tr("Something went wrong when setting the application up. Please verify the shortcut."));
        warning.setIcon(QMessageBox::Warning);
        warning.exec();
        showParametersDialog();
        return false;
    }

    QObject::connect(hotkey_, &QHotkey::activated, [=] {
        // Wait for the shortcut to be triggered
        showWidget();
    });

    return true;
}

/*!
 * \brief This function is called when the text has been chaged by the user in the dialog
 */
void CalcWidget::on_lineEdit_textChanged(const QString &)
{
    resetFormulaColor();

    // Reset the timeout
    hideTimer_.start();
}

/*!
 * \brief This function is called when the user wants to show the parameters
 */
void CalcWidget::on_btnShowParameters_clicked()
{
    showParametersDialog();
}

/*!
 * \brief Called when the user pressed enter in the dialog
 */
void CalcWidget::on_lineEdit_returnPressed()
{
    // Calculate the result
    bool ok(false);
    const auto& enteredValue = ui->lineEdit->text();
    auto value = InputHelper::reformatInputNumber(enteredValue);

    if(InputHelper::isCumulatedFormula(value)) {
        value.prepend(QString::number(lastResult_));
    }

    const auto& result = MathHelper::computeFormula(value, &ok);

    if(!ok) {
        auto palette = ui->lineEdit->palette();
        palette.setColor(QPalette::Text, Qt::red);
        ui->lineEdit->setPalette(palette);
        ui->lblResult->setText(tr("There was an error in your formula. Please verify."));
    } else {
        auto palette = ui->lineEdit->palette();
        palette.setColor(QPalette::Text, Qt::white);
        ui->lineEdit->setPalette(palette);
        ui->lineEdit->clear();
        ui->lblResult->setText(QString("=%1").arg(QLocale::system().toString(result, 'f', paramDialog_->precisionDigits())));
        lastResult_ = result;
    }

}

/*!
 * \brief Hides the app window
 *
 * The app will not quit.
 */
void CalcWidget::hideWindow()
{
    auto currentGeometry = geometry();

    ui->lineEdit->hide();
    ui->btnShowParameters->hide();

    auto animation = new QPropertyAnimation(this, "size");
    animation->setDuration(200);
    animation->setStartValue(currentGeometry.size());
    animation->setEndValue(QSize(currentGeometry.width(), 0));
    animation->setEasingCurve(QEasingCurve::InCubic);

    animation->start(QAbstractAnimation::DeleteWhenStopped);
    connect(animation, &QAbstractAnimation::finished, [=]{
       hide();
       ui->lineEdit->show();
       ui->btnShowParameters->show();
       setGeometry(currentGeometry);
    });
}

/*!
 * \brief Called when a key is pressed inside the app window
 */
void CalcWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape) {
        hideWindow();
        hideTimer_.stop();
    }
}

/*!
 * \brief Called when the user asked to copy the text
 */
void CalcWidget::on_btnCopy_clicked()
{
    auto clipboard = QApplication::clipboard();
    clipboard->setText(QLocale::system().toString(lastResult_, 'f', paramDialog_->precisionDigits()));
    ui->lblInformation->setText(tr("Value copied."));
    QTimer::singleShot(1500, [=] { ui->lblInformation->clear(); });
}
