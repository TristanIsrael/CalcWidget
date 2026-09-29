cmake_minimum_required(VERSION 3.21)

project(CalcWidgetLauncher LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_OSX_DEPLOYMENT_TARGET "10.14")

find_package(Qt6 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(CalcWidgetLauncher
    main.cpp
)

target_link_libraries(CalcWidgetLauncher PRIVATE
    Qt6::Core
    "-framework ServiceManagement"
    "-framework CoreFoundation"
)

set_target_properties(CalcWidgetLauncher PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_INFO_PLIST
        "${CMAKE_CURRENT_SOURCE_DIR}/Info.plist"
    RUNTIME_OUTPUT_DIRECTORY
        "${CMAKE_CURRENT_SOURCE_DIR}/../../bin.nosync"
)

# Code signing / packaging
#set(PACKAGING_SCRIPT
#    "${CMAKE_CURRENT_SOURCE_DIR}/scripts/sign_app.sh"
#)

#add_custom_command(TARGET CalcWidgetLauncher POST_BUILD
#    COMMAND chmod +x "${PACKAGING_SCRIPT}"
#    COMMAND "${PACKAGING_SCRIPT}"
#        "$<TARGET_BUNDLE_DIR:CalcWidgetLauncher>"
#        "${CMAKE_CURRENT_SOURCE_DIR}/launcher.entitlements"
#    VERBATIM
#)