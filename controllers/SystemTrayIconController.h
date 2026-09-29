/*
 * Copyright (c) 2026 Tristan Israël
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
 *
 * https://opensource.org/license/mit/
 */

#ifndef SYSTEMTRAYICONCONTROLLER_H
#define SYSTEMTRAYICONCONTROLLER_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QAction>

class SystemTrayIconController : public QWidget
{
    Q_OBJECT
public:
    explicit SystemTrayIconController();

signals:
    void showCalcWidget();
    void showParametersDialog();
    void showAboutDialog();

public slots:
    void refreshMenu();

private:
    QSystemTrayIcon *trayIcon_ = nullptr;
    QAction* actionShowCalcWidget_ = nullptr;

};

#endif // SYSTEMTRAYICONCONTROLLER_H
