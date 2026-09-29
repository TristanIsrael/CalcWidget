/*
 * Copyright (c) 2026 Tristan Israël
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
 *
 * https://opensource.org/license/mit/
 */

#ifndef CALCWIDGET_H
#define CALCWIDGET_H

#include <QMainWindow>
#include <QTimer>
#include <QWidget>
#include "QHotkey"

namespace Ui {
class CalcWidget;
}
class QHotkey;
//class MacOsGlobalHotkey;
class ParametersDialog;


class CalcWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CalcWidget(QWidget *parent = nullptr);
    ~CalcWidget();

signals:
    void parametersChanged();

private:
    void resetFormulaColor();

public slots:
    void showParametersDialog();
    void showWidget();

private slots:
    void applyParameters();
    bool reInstallShortcut();
    void on_lineEdit_textChanged(const QString &);
    void on_btnShowParameters_clicked();
    void on_lineEdit_returnPressed();
    void hideWindow();
    void on_btnCopy_clicked();
    //void copyToClipboard();

private:
    Ui::CalcWidget* ui;
    QHotkey* hotkeyManager_ = nullptr;
    //MacOsGlobalHotkey *globalHotkey_ = nullptr;
    ParametersDialog* paramDialog_ = nullptr;
    QTimer hideTimer_;
    double lastResult_ = 0.0;
    QHotkey* hotkey_ = nullptr;

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // CALCWIDGET_H
