QT       += core
QT       -= gui svg printsupport widgets

TARGET = EasyCalcLauncher
TEMPLATE = app
DESTDIR = $$PWD/../../bin.nosync/

CONFIG += c++11

SOURCES += \        
        main.cpp

OTHER_FILES += \
    Info.plist \
    launcher.entitlements \
    scripts/sign_app.sh

MACX_SDK_BASE = /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.15.sdk/System/Library/Frameworks
if(!exists($$MACX_SDK_BASE)) {
    error("The SDK path was not found !");
}

INCLUDEPATH += $$MACX_SDK_BASE/CoreFoundation.framework/Headers $$MACX_SDK_BASE/IOKit.framework/Headers $$MACX_SDK_BASE/SystemConfiguration.framework/Headers $$MACX_SDK_BASE/Security.framework/Headers
#LIBS += -framework CoreServices -framework CoreFoundation -framework SystemConfiguration -framework IOKit -framework Security
LIBS += -framework ServiceManagement -framework CoreFoundation

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.11
QMAKE_CFLAGS += -gdwarf-2
QMAKE_CXXFLAGS += -gdwarf-2

QMAKE_INFO_PLIST = Info.plist

PACKAGING_SCRIPT = $${PWD}/scripts/sign_app.sh
QMAKE_POST_LINK += chmod +x $${PACKAGING_SCRIPT} && $${PACKAGING_SCRIPT} $${DESTDIR}$${TARGET} $${PWD}/launcher.entitlements

# To extract symbols: dsymutil MyApp.app/Contents/MacOS/MyApp -o MyApp.app.dSYM

DISTFILES += \
    scripts/sign_app_old.sh
