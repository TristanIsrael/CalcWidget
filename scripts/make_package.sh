#!/bin/sh

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 DIRECTORY APP_NAME"
    exit
fi

echo Build installer package
productbuild --component $1/$2.app /Applications --sign 3rd\ Party\ Mac\ Developer\ Installer:\ Tristan\ Israel $2.pkg
