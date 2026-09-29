/*
 * Copyright (c) 2026 Tristan Israël
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
 *
 * https://opensource.org/license/mit/
 */

#include <QApplication>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include "SystemTrayIconController.h"
#include "CalcWidget.h"
#include "AboutDialog.h"
#include <QTranslator>
#include <QString>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication::setApplicationName("CalcWidget");
    QApplication::setOrganizationName("alefbet");
    QApplication::setOrganizationDomain("alefbet.net");
    QApplication::setApplicationVersion("1.4.1");

    QApplication a(argc, argv);    
    a.setQuitOnLastWindowClosed(false);

    qDebug() << "Current plugins path is " << QApplication::libraryPaths();
    qDebug() << "Starting CalcWidget version " << QApplication::applicationVersion();

    QTranslator translator;    
    QString lang = QLocale::system().name().split("_").last();
    if(lang == "FR") {
        qDebug() << "Using french language";
        if(translator.load(QLocale(QLocale::French), "", "", ":/i18n")) {
            a.installTranslator(&translator);
        }
    }

    SystemTrayIconController trayIcon;
    CalcWidget w;    
    AboutDialog about;

    QObject::connect(&trayIcon, &SystemTrayIconController::showAboutDialog, &about, &AboutDialog::show);
    QObject::connect(&trayIcon, &SystemTrayIconController::showCalcWidget, &w, &CalcWidget::showWidget);
    QObject::connect(&trayIcon, &SystemTrayIconController::showParametersDialog, &w, &CalcWidget::showParametersDialog);
    QObject::connect(&w, &CalcWidget::parametersChanged, &trayIcon, &SystemTrayIconController::refreshMenu);

    return a.exec();
}
