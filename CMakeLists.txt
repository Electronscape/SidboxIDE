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
    guidesigner.cpp
    guidesigner.h
    mainwindow.ui
    findreplacedialog.cpp
    findreplacedialog.h
)

qt_add_resources(SidboxIDE "app_icons"
    PREFIX "/icons"
    BASE icons
    FILES
        icons/icon_save.png
        icons/new_project.png
        icons/open_project.png
        icons/save_project.png
        icons/compile.png
        icons/options.png
        icons/project_settings.png
        icons/close_tab.png
        icons/icon.png
        icons/icon.ico
        icons/tree_folder.png
        icons/tree_file_c.png
        icons/tree_file_h.png
        icons/tree_file_inc.png
        icons/tree_file_md.png
        icons/tree_file_unknown.png
        icons/tree_file_txt.png
        icons/tree_scope_function.png
        icons/tree_scope_globals.png
        icons/tree_scope_types.png
        icons/tree_scope_defines.png
        icons/tree_scope_params.png
        icons/tree_scope_locals.png
        icons/search_term.png
        icons/ide_icon_32x32.png
        icons/toolbar_cheatsheet.png
        icons/toolbar_guidesigner.png
        icons/tree_file_res.png
    )

set(CMAKE_AUTORCC ON)

target_link_libraries(SidboxIDE
    PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

install(FILES icons/icon.png
    DESTINATION share/icons/hicolor/256x256/apps
    RENAME SidboxIDE.png
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

target_compile_options(SidboxIDE PRIVATE
    $<$<CONFIG:Release>:-O3>
    $<$<CONFIG:Release>:-march=native>
    $<$<CONFIG:Release>:-flto>
)

target_link_options(SidboxIDE PRIVATE
    $<$<CONFIG:Release>:-flto>
)

install(SCRIPT ${deploy_script})
