cmake_minimum_required(VERSION 3.16)

project(ClunkCoinGUI VERSION 0.1 LANGUAGES CXX)

# Enable Qt features
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 package
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

# Set the source files
set(PROJECT_SOURCES
    main.cpp
    mainwindow.ui
    mainwindow.cpp
    mainwindow.h
    auth_interface.h
    walletwindow.ui
    walletwindow.h
    walletwindow.cpp
    auth.qrc
)

# Path to the dylib
set(AUTH_DYLIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libs/libauthentication.dylib")

# Add executable for the GUI
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ClunkCoinGUI
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )

    # Link Qt and the authentication dylib
    target_link_libraries(ClunkCoinGUI PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        ${AUTH_DYLIB_PATH}
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ClunkCoinGUI_en_GB.ts)
else()
    add_executable(ClunkCoinGUI
        ${PROJECT_SOURCES}
    )
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ClunkCoinGUI_en_GB.ts)
endif()

# Install the dylib
install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/libs/libauthentication.dylib
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ClunkCoinGUI)
endif()
