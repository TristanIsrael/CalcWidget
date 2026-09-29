#!/bin/sh

echo
echo *********************************
echo Signing app
echo *********************************
echo 

#$1 = appname
#$2 = entitlements

MACDEPLOYQT=/Applications/Developpement/Qt/5.14.2/clang_64/bin/macdeployqt
DEVELOPER_IDENTITY="Apple Development: Tristan Israel (2X7Z5P65RM)"
INSTALLER_IDENTITY="Developer ID Installer: Tristan Israel (ZH4Z328B5F)"
BUNDLE_ID="net.alefbet.easycalclauncher"

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

CODESIGN_OPTIONS="-f --timestamp --verbose=4 --options=runtime -i ${BUNDLE_ID} --entitlements $2"
echo "Signing the frameworks..."
for FRAMEWORK in $(ls "$1.app"/Contents/Frameworks | grep framework | sed 's/\.framework//')
do
    echo "About to sign $FRAMEWORK"
    codesign ${CODESIGN_OPTIONS} --sign "${DEVELOPER_IDENTITY}" "$1.app"/Contents/Frameworks/$FRAMEWORK.framework
done

echo "Signing the dylibs..."
find "$1.app"/Contents/Frameworks -name "*.dylib" -exec codesign ${CODESIGN_OPTIONS} --sign "${DEVELOPER_IDENTITY}" '{}' \;

echo "Signing the plugins..."
find "$1.app"/Contents/PlugIns -name "*.dylib" -exec codesign ${CODESIGN_OPTIONS} --sign "${DEVELOPER_IDENTITY}" '{}' \;
