cmake_minimum_required(VERSION 3.19)
project(SidboxIDE LANGUAGES CXX)

include(GNUInstallDirs)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Gui Widgets)
# Optional native WAV preview: no Qt Multimedia dependency when absent.
find_package(Qt6 6.5 QUIET COMPONENTS Multimedia)

qt_standard_project_setup()

find_package(ZLIB REQUIRED)

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
    gamedesigner.cpp
    gamedesigner.h
    gamemainownership.h
    gametilemap.cpp
    gametilemap.h
    gameanimationeditor.cpp
    gameanimationeditor.h
    gameaudio.cpp
    gameaudio.h
    gamepalette.cpp
    gamepalette.h
    gamepaletteeditor.cpp
    gamepaletteeditor.h
    gamecodegen.cpp
    gamecodegen.h
    ppbcodec.cpp
    ppbcodec.h
    pngpaletteimport.cpp
    pngpaletteimport.h
    mainwindow.ui
    findreplacedialog.cpp
    findreplacedialog.h
    splashscreenwidget.cpp
    splashscreenwidget.h
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
        icons/tree_guidesigner.png
        icons/search_term.png
        icons/ide_icon_32x32.png
        icons/toolbar_cheatsheet.png
        icons/toolbar_guidesigner.png
        icons/toolbar_gamedesigner.png
        icons/tree_file_res.png
        icons/gadget_button.png
        icons/gadget_checkbox.png
        icons/gadget_label.png
        icons/gadget_progressbar.png
        icons/gadget_scrollbar.png
        icons/gadget_tabgroup.png
        icons/gadget_textbox.png
        icons/gadget_textarea.png
        icons/gadget_bitmapview.png
        icons/gadget_canvas.png
        icons/gadget_gridselect.png
        icons/gadget_listbox.png
        icons/gadget_radio.png
        icons/gadget_slider.png
        icons/gadget_timer.png
        icons/gadget_media.png
        icons/gadget_filerequester.png
        icons/gadget_messagebox.png
        icons/gadget_msinput.png
        icons/gadget_kbinput.png
        icons/gadget_uart1.png
        icons/nagelgirl.png
        icons/gr_icon_sprite.png
        icons/gr_icon_background.png
        icons/gr_icon_palette.png
        icons/gr_icon_audio.png
        icons/gr_icon_object.png
        icons/gr_icon_spline.png
    )

# Optional user-provided Home artwork. The IDE still configures and builds
# before icons/toolbar_home.png is drawn; reconfigure CMake after adding it.
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/icons/toolbar_home.png")
    qt_add_resources(SidboxIDE "home_toolbar_icon"
        PREFIX "/icons"
        BASE icons
        FILES icons/toolbar_home.png
    )
endif()

set(CMAKE_AUTORCC ON)

target_link_libraries(SidboxIDE
    PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Widgets
        ZLIB::ZLIB
)

if(TARGET Qt6::Multimedia)
    target_link_libraries(SidboxIDE PRIVATE Qt6::Multimedia)
    target_compile_definitions(SidboxIDE PRIVATE SIDBOX_HAS_QT_MULTIMEDIA=1)
endif()

# Native host-side converter: ELF32 ARM PIE -> CoderGirl SBAPV2.
# Keep its SOURCE beside mainwindow.cpp, but stage its BINARY beside the
# other IDE toolchain utilities, under idelibs/tools/.
add_executable(sidbox-v2-packer v2_packer.cpp)
set_target_properties(sidbox-v2-packer PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)
set(SIDBOX_IDELIBS_TOOLS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/idelibs/tools")
add_custom_command(TARGET sidbox-v2-packer POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E make_directory "${SIDBOX_IDELIBS_TOOLS_DIR}"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
        "$<TARGET_FILE:sidbox-v2-packer>"
        "${SIDBOX_IDELIBS_TOOLS_DIR}/$<TARGET_FILE_NAME:sidbox-v2-packer>"
    COMMENT "Installing native V2 packer into idelibs/tools"
    VERBATIM
)
# CGARM V2 standalone compiler frontend, built and shipped with the IDE.
# Its source remains in development/, not in the end-user idelibs folder.
# This first host implementation uses Linux POSIX process APIs.
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_executable(cgarm-build development/tools/cgarm-build/cgarm-build.cpp)
    set_target_properties(cgarm-build PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)
    add_custom_command(TARGET cgarm-build POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E make_directory "${SIDBOX_IDELIBS_TOOLS_DIR}/bin"
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "$<TARGET_FILE:cgarm-build>"
            "${SIDBOX_IDELIBS_TOOLS_DIR}/bin/$<TARGET_FILE_NAME:cgarm-build>"
        COMMENT "Staging cgarm-build in idelibs/tools/bin"
        VERBATIM
    )
    # Real standalone experimental linker. Its diagnostics/verification tools
    # remain development-only and are NOT shipped in the normal IDE.
    add_executable(cgarm-ld development/tools/cgarm-ld/cgarm-ld.cpp)
    set_target_properties(cgarm-ld PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)
    add_custom_command(TARGET cgarm-ld POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E make_directory "${SIDBOX_IDELIBS_TOOLS_DIR}/bin"
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different
            "$<TARGET_FILE:cgarm-ld>"
            "${SIDBOX_IDELIBS_TOOLS_DIR}/bin/$<TARGET_FILE_NAME:cgarm-ld>"
        COMMENT "Staging cgarm-ld in idelibs/tools/bin"
        VERBATIM
    )
    add_dependencies(SidboxIDE cgarm-build cgarm-ld)
    install(TARGETS cgarm-ld
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}/idelibs/tools/bin"
    )
    install(TARGETS cgarm-build
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}/idelibs/tools/bin"
    )
endif()

# Building only SidboxIDE in Qt Creator must also rebuild/stage the packer.
add_dependencies(SidboxIDE sidbox-v2-packer)
# Installed layouts keep the same app-relative idelibs/tools lookup.
install(TARGETS sidbox-v2-packer
    RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}/idelibs/tools"
)

# Keep optional V1 helper templates alongside the installed IDE executable.
# They are discovered at runtime; no helper C source is baked into Qt.
install(DIRECTORY idelibs/codehelpers
    DESTINATION "${CMAKE_INSTALL_BINDIR}/idelibs"
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
