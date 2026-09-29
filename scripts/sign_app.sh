#!/bin/sh

echo
echo *********************************
echo Signing app
echo *********************************
echo

MACDEPLOYQT=/Applications/Developpement/Qt/5.15.2/clang_64/bin/macdeployqt
DEVELOPER_IDENTITY="3rd Party Mac Developer Application: Tristan Israel (ZH4Z328B5F)"
INSTALLER_IDENTITY="Developer ID Installer: Tristan Israel (ZH4Z328B5F)"
BUNDLE_ID="net.alefbet.easycalc"

if [ "$#" -ne 3 ]; then
    echo "Missing arguments: [bundle path] [entitlements] [app name]";
    exit 1
fi

echo Using macdeployqt at $MACDEPLOYQT
echo Using Bundle path $1/Library/LoginItems

echo Extract debug symbols
dsymutil $1.app/Contents/MacOS/$3 -o $1.app.dSYM

echo - Deploy Qt libs and sign libraries
$MACDEPLOYQT $1.app -appstore-compliant -sign-for-notarization="$DEVELOPER_IDENTITY"

echo - Sign application with entitlements
codesign -f -v -s "$DEVELOPER_IDENTITY" --entitlements $2 $1.app

echo "Verify bundle"
codesign --verbose --verify "$1.app"

