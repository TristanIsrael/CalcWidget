#!/bin/sh

echo
echo *********************************
echo Signing app
echo *********************************
echo

MACDEPLOYQT=/Applications/Developpement/Qt/5.14.2/clang_64/bin/macdeployqt
DEVELOPER_IDENTITY="Apple Development: Tristan Israel (2X7Z5P65RM)"
INSTALLER_IDENTITY="Developer ID Installer: Tristan Israel (ZH4Z328B5F)"

if [ "$#" -ne 3 ]; then
    echo "Missing arguments: [bundle path] [entitlements] [app name]";
    exit 1
fi

echo App bundle: $1
echo App name:$3
echo
echo Using macdeployqt at $MACDEPLOYQT
#echo Using Bundle path $1/Library/LoginItems

echo Extract debug symbols
dsymutil $1.app/Contents/MacOS/$3 -o $1.app.dSYM

echo - Deploy Qt libs and sign application
$MACDEPLOYQT $1.app -appstore-compliant
#-codesign="$DEVELOPER_IDENTITY"

echo - Remove unnecessary frameworks

echo - Remove unnecessary plugins

echo - Sign frameworks
codesign -s "$DEVELOPER_IDENTITY" $1.app/Contents/Frameworks/QtCore.framework
codesign -s "$DEVELOPER_IDENTITY" $1.app/Contents/Frameworks/QtGui.framework
codesign -s "$DEVELOPER_IDENTITY" $1.app/Contents/Frameworks/QtWidgets.framework
codesign -s "$DEVELOPER_IDENTITY" $1.app/Contents/Frameworks/QtSvg.framework
codesign -s "$DEVELOPER_IDENTITY" $1.app/Contents/Frameworks/QtDBus.framework
codesign -s "$DEVELOPER_IDENTITY" $1.app/Contents/Frameworks/QtPrintSupport.framework

echo - Sign plugins
codesign -s "$DEVELOPER_IDENTITY" $1.app/Contents/PlugIns/iconengines/libqsvgicon.dylib
codesign -s "$DEVELOPER_IDENTITY" $1.app/Contents/PlugIns/platforms/libqcocoa.dylib
codesign -s "$DEVELOPER_IDENTITY" $1.app/Contents/PlugIns/styles/libqmacstyle.dylib
codesign -s "$DEVELOPER_IDENTITY" $1.app/Contents/PlugIns/imageformats/*.dylib
codesign -s "$DEVELOPER_IDENTITY" $1.app/Contents/PlugIns/printsupport/*.dylib

echo - Sign application with entitlements
codesign -f -v -s "$DEVELOPER_IDENTITY" --entitlements $2 $1.app
