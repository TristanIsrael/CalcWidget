/*
 * Copyright (c) 2026 Tristan Israël
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
 *
 * https://opensource.org/license/mit/
 */

#include "SystemTrayIconController.h"
#include <QMenu>
#include <QApplication>
#include <QEvent>
#include <QDebug>
#include "ParametersHelper.hpp"

/*!
 * \brief This class handles the system tray icon
 */
SystemTrayIconController::SystemTrayIconController()
    : QWidget(), trayIcon_(new QSystemTrayIcon(this))
{
    QIcon icon(":/icons/appicon.icns");
    icon.setIsMask(true);
    trayIcon_->setIcon(icon);
    trayIcon_->show();

    actionShowCalcWidget_ = new QAction(this);
    const auto& actionShowAbout = new QAction(tr("About..."), this);
    const auto& actionShowParameters = new QAction(tr("Settings..."), this);
    const auto& actionQuit = new QAction(tr("Quit"), this);

    connect(actionShowCalcWidget_, &QAction::triggered, [=] {
       emit showCalcWidget();
    });
    connect(actionShowParameters, &QAction::triggered, [=] {
       emit showParametersDialog();
    });
    connect(actionQuit, &QAction::triggered, [=] {
       qApp->quit();
    });
    connect(actionShowAbout, &QAction::triggered, [=] {
        emit showAboutDialog();
    });

    const auto& menu = new QMenu(this);
    trayIcon_->setContextMenu(menu);

    menu->addAction(actionShowAbout);
    menu->addSeparator();
    menu->addAction(actionShowCalcWidget_);
    menu->addAction(actionShowParameters);
    menu->addSeparator();
    menu->addAction(actionQuit);

    refreshMenu();
}

/*!
 * \brief Refreshed the system tray menu
 */
void SystemTrayIconController::refreshMenu()
{
    actionShowCalcWidget_->setText(tr("Show Calculator\t%1").arg(ParametersHelper::shortcut().toString()));
}

