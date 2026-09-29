# CalcWidget

CalcWidget — a simple calculator, always one shortcut away.

CalcWidget runs quietly in the background and provides a fast way to perform mathematical calculations without opening a traditional calculator application. The calculator can be displayed at any time using a configurable global keyboard shortcut.

## Features

* 🧮 Evaluate mathematical expressions directly from the widget
* ⌨️ Configurable global keyboard shortcut
* 📋 Copy the result to the clipboard
* 🎯 Configurable result precision
* ⏱️ Configurable widget visibility duration
* 🖥️ Runs as a menu bar application without a permanent window
* 🌍 Automatic localization based on the system language
* 💾 User preferences are persisted between sessions
* 🔢 Mathematical expressions are evaluated using ExprTk

## Usage

Once CalcWidget is running, use the configured global keyboard shortcut to display the calculator. 

Enter a mathematical expression and press Return to evaluate it.

For example:

`2 + 3 * 4`

produces:

`=14`

The result can be copied directly to the clipboard.

**Press Escape to hide the calculator.**

The calculator automatically hides itself after the configured visibility duration.

## Menu bar

CalcWidget runs as a menu bar application and does not keep a regular application window open.

The menu provides access to:

* Show Calculator
* Settings
* About
* Quit

The currently configured keyboard shortcut is displayed next to Show Calculator.

## Settings

The following settings can be configured:

**Global shortcut**

The keyboard shortcut used to display the calculator can be changed from the Settings dialog.

Only a single key combination is used as a global shortcut.

**Visibility duration**

Defines how long the calculator remains visible after being displayed.

**Result precision**

Defines the number of decimal digits displayed in calculation results.

Settings are stored in a user-wide preference file.

## Requirements

CalcWidget is a macOS application built with:

* macOS
* Qt 6
* C++11
* CMake 3.21.1 or later
* Qt Core
* Qt Gui
* Qt Widgets
* Qt LinguistTools

The current CMake configuration targets macOS 26.

## Dependencies

### QHotkey

CalcWidget uses QHotkey to register the global keyboard shortcut.

QHotkey supports Qt 6 and provides cross-platform global keyboard shortcuts. 

This library is linked as a submodule. It needs to be built before building CalcWidget.

### ExprTk

The mathematical expression parser is provided by ExprTk.

The exprtk.hpp header is included directly in the CalcWidget source tree under:

3rdParty/exprtk.hpp

ExprTk is distributed under the MIT License.

## Building

1. Clone CalcWidget

git clone https://github.com/TristanIsrael/CalcWidget.git
cd CalcWidget

2. Build QHotkey

QHotkey is a submodule so it is cloned inside the CalcWidget directory:

```
parent-directory/
├── CalcWidget/
    └── QHotkey/
```

Build QHotkey:

```
cd QHotkey
cmake -B build -S . -DQT_DEFAULT_MAJOR_VERSION=6
cmake --build build
```

Then return to the project folder

`cd ../CalcWidget`

3. Configure CalcWidget

`cmake -B build -S .`

4. Build

`cmake --build build`

The resulting application bundle is generated as:

`build/CalcWidget.app`

Project structure

```
CalcWidget/
├── 3rdParty/          Third-party libraries
├── app/               Application resources
├── controllers/       Main application controllers
├── documentation/     Project documentation
├── helpers/           Utility classes
├── i18n/              Translation files
├── images/            Application icons and images
├── launcher/          macOS Login Item launcher
├── scripts/            Build and utility scripts
├── views/              Qt Designer UI files
├── CMakeLists.txt      CMake configuration
├── Info.plist          macOS application metadata
├── app.entitlements    macOS entitlements
├── LICENSE             MIT License
└── main.cpp            Application entry point
```

The application is split into controllers, helpers and Qt Designer views. The main calculator controller manages the calculator window, global shortcut, input and result display. (GitHub)

## Localization

CalcWidget uses Qt’s translation system.

The application detects the system locale and currently provides a French translation in addition to the default English interface.

Translation files are located in: `i18n/`.

## macOS integration

CalcWidget is configured as a background/menu bar application rather than a conventional application window.

The application uses the macOS `LSUIElement` setting so that it does not appear as a normal application in the Dock.

A dedicated `CalcWidgetLauncher` application is also included in the macOS Login Items bundle so that CalcWidget can integrate with the macOS login/startup mechanism. 

## License

CalcWidget is released under the MIT License.

See LICENSE for the complete license text.

## Third-party components

CalcWidget includes or uses third-party components with their own licenses:

* QHotkey — BSD 3-Clause License
* ExprTk — MIT License
* Application icons — Freepik / Flaticon, licensed under Creative Commons BY 3.0

The icon attribution is also included in the project documentation. 

## Support

If you encounter a problem or have a suggestion, please open an issue on GitHub.

## Author

Copyright © 2019–2026 Tristan Israël / Alefbet.
