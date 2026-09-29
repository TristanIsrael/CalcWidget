#!/bin/sh

echo
echo *********************************
echo Signing app
echo *********************************
echo 

MACDEPLOYQT=/Applications/Developpement/Qt/5.14.2/clang_64/bin/macdeployqt
DEVELOPER_IDENTITY="Apple Development: Tristan Israel (2X7Z5P65RM)"
INSTALLER_IDENTITY="Developer ID Installer: Tristan Israel (ZH4Z328B5F)"

if [ "$#" -ne 2 ]; then
    echo "Missing arguments: [bundle path] [entitlements]";
    exit 1
fi

echo Using macdeployqt at $MACDEPLOYQT
echo Using Bundle path $1/Library/LoginItems

echo - Deploy Qt libs and sign application
$MACDEPLOYQT $1.app -appstore-compliant
#-codesign="$DEVELOPER_IDENTITY"

echo - Remove unnecessary frameworks
rm -rf $1.app/Contents/Frameworks/QtGui.framework $1.app/Contents/Frameworks/QtPrintSupport.framework $1.app/Contents/Frameworks/QtSvg.framework $1.app/Contents/Frameworks/QtWidgets.framework $1.app/Contents/Frameworks/QtDBus.framework

echo - Remove unnecessary plugins
rm -rf $1.app/Contents/PlugIns/iconengines $1.app/Contents/PlugIns/imageformats $1.app/Contents/PlugIns/printsupport $1.app/Contents/PlugIns/styles

echo - Sign frameworks
codesign -s "$DEVELOPER_IDENTITY" $1.app/Contents/Frameworks/QtCore.framework

echo - Sign plugins
codesign -s "$DEVELOPER_IDENTITY" $1.app/Contents/PlugIns/platforms/libqcocoa.dylib

echo - Sign application with entitlements
codesign -s "$DEVELOPER_IDENTITY" --entitlements $2 $1.app
