cmake_minimum_required(VERSION 3.19)
project(SidboxIDE LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Widgets)

qt_standard_project_setup()

qt_add_executable(SidboxIDE
    WIN32 MACOSX_BUNDLE
    main.cpp
    codeeditor.cpp
    codeeditor.h
    csyntaxhighlighter.cpp
    csyntaxhighlighter.h
    optionsdialog.cpp
    optionsdialog.h
    projectsettingsdialog.cpp
    projectsettingsdialog.h
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
)

target_link_libraries(SidboxIDE
    PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

install(TARGETS SidboxIDE
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET SidboxIDE
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
