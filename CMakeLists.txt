cmake_minimum_required(VERSION 3.21.1)

project(CalcWidget
    VERSION 1.4.1
    LANGUAGES CXX OBJCXX
)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_OSX_DEPLOYMENT_TARGET "26")

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    LinguistTools
)

qt_standard_project_setup (
    I18N_TRANSLATED_LANGUAGES en
)

set(CMAKE_AUTOUIC_SEARCH_PATHS
    "${CMAKE_CURRENT_SOURCE_DIR}/views"
)

qt_add_executable(CalcWidget    
    controllers/AboutDialog.h controllers/AboutDialog.cpp
    controllers/ParametersDialog.h controllers/ParametersDialog.cpp
    controllers/SystemTrayIconController.h controllers/SystemTrayIconController.cpp
    controllers/CalcWidget.h controllers/CalcWidget.cpp
    #controllers/MacOsGlobalHotkey.h controllers/MacOsGlobalHotkey.cpp
    helpers/MathHelper.h helpers/MathHelper.cpp    
    helpers/MacOsHelper.h helpers/MacOsHelper.mm
    main.cpp
    3rdParty/exprtk.hpp
    helpers/InputHelper.hpp
    helpers/ParametersHelper.hpp
    views/AboutDialog.ui
    views/CalcWidget.ui
    views/ParametersDialog.ui
    main.qrc
    images/calcwidget.icns
)

target_include_directories(CalcWidget PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/controllers
    ${CMAKE_CURRENT_SOURCE_DIR}/helpers
    ${CMAKE_CURRENT_SOURCE_DIR}/factories
    ${CMAKE_CURRENT_SOURCE_DIR}/../QHotkey/QHotkey
)

target_link_libraries(CalcWidget PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    ${CMAKE_CURRENT_SOURCE_DIR}/../QHotkey/build/libqhotkey.a
    "-framework Carbon"
    "-framework ServiceManagement"
    "-framework CoreFoundation"
)

set_target_properties(CalcWidget PROPERTIES
    MACOSX_BUNDLE_ICON_FILE "calcwidget.icns"
)

set_source_files_properties(
    images/calcwidget.icns
    PROPERTIES
    MACOSX_PACKAGE_LOCATION "Resources"
)

target_compile_options(CalcWidget PRIVATE
    $<$<COMPILE_LANGUAGE:OBJCXX>:-fobjc-arc>
)

set_target_properties(CalcWidget PROPERTIES
    MACOSX_BUNDLE TRUE
    OUTPUT_NAME "CalcWidget"
    MACOSX_BUNDLE_INFO_PLIST
        "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist"
)

set_source_files_properties(
    helpers/MacOsHelper.mm
    PROPERTIES
    COMPILE_FLAGS "-fobjc-arc"
)

qt_add_translations(CalcWidget
    TS_FILES
        i18n/fr.ts
)

qt_add_executable(CalcWidgetLauncher
    launcher/main.cpp
)

set_target_properties(CalcWidgetLauncher PROPERTIES
    MACOSX_BUNDLE TRUE
)

add_dependencies(CalcWidget CalcWidgetLauncher)

add_custom_command(TARGET CalcWidget POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory
        "$<TARGET_BUNDLE_DIR:CalcWidget>/Contents/Library/LoginItems"
    COMMAND ${CMAKE_COMMAND} -E rm -rf
        "$<TARGET_BUNDLE_DIR:CalcWidget>/Contents/Library/LoginItems/CalcWidgetLauncher.app"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "$<TARGET_BUNDLE_DIR:CalcWidgetLauncher>"
        "$<TARGET_BUNDLE_DIR:CalcWidget>/Contents/Library/LoginItems/CalcWidgetLauncher.app"
    DEPENDS CalcWidgetLauncher
    VERBATIM
)
