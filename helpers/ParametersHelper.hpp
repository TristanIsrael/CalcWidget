/*
 * Copyright (c) 2026 Tristan Israël
 *
 * Licensed under the MIT License.
 * See the LICENSE file in the project root for license information.
 *
 * https://opensource.org/license/mit/
 */

#ifndef PARAMETERSHELPER_HPP
#define PARAMETERSHELPER_HPP

#include <QKeySequence>
#include <QSettings>

/*!
 * \brief This class provides helpers to manage the app settings
 */
class ParametersHelper {
private:
    ParametersHelper() {}

public:
    /*!
     * \brief Returns the global shortcut
     */
    static QKeySequence shortcut()
    {
        QSettings settings;
        return QKeySequence::fromString(settings.value("Shortcut").toString());
    }

    /*!
     * \brief Defines the new global shortcut
     */
    static void setShortcut(const QKeySequence& sequence) {
        QSettings settings;
        settings.setValue("Shortcut", sequence.toString());
    }

    /*!
     * \brief Returns the visibility duration
     */
    static int visibilityDuration()
    {
        QSettings settings;
        int duration = settings.value("VisibilityDuration").toInt();
        if(duration < 5) {
            duration = 5;
        }

        return duration;
    }

    /*!
     * \brief Defines the visibility duration
     */
    static void setVisibilityDuration(const int& duration) {
        QSettings settings;
        settings.setValue("VisibilityDuration", duration);
    }

    /*!
     * \brief Returns the precision digits
     */
    static int precisionDigits()
    {
        QSettings settings;
        return settings.value("PrecisionDigits").toInt();
    }

    /*!
     * \brief Sets the precision digits
     */
    static void setPrecisionDigits(const int& precision) {
        QSettings settings;
        settings.setValue("PrecisionDigits", precision);
    }

};

#endif // PARAMETERSHELPER_HPP
