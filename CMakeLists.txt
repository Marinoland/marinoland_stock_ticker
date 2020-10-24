cmake_minimum_required(VERSION 2.8)
project (stock_ticker)

if(NOT EXISTS ./depend)
	execute_process(COMMAND git clone git@github.com:Marinoland/marinoland_depend.git depend)
	execute_process(COMMAND cmake . WORKING_DIRECTORY depend)
endif()

if(WIN32)
    set(CMAKE_WIN32_EXECUTABLE ON)
    set(UI_FRAMEWORK_DIR depend/gui/ui_framework/win)
    set(UI_INCLUDE
        ${UI_FRAMEWORK_DIR}
    )
    set(UI_LINK ${CMAKE_CURRENT_SOURCE_DIR}/depend/gui)
    set(UI_DEFS )
    set(UI_LIBS gui)
ELSE()
    set(UI_FRAMEWORK_DIR depend/gui/ui_framework/gtk)
    find_package(PkgConfig REQUIRED)
    PKG_CHECK_MODULES(GTK3 REQUIRED gtk+-3.0)
    set(UI_INCLUDE
        ${GTK3_INCLUDE_DIRS}
        ${UI_FRAMEWORK_DIR}
    )
    set(UI_LINK ${CMAKE_CURRENT_SOURCE_DIR}/depend/gui ${GTK3_LIBRARY_DIRS})
    set(UI_DEFS ${GTK3_CFLAGS_OTHER})
    set(UI_LIBS gui ${GTK3_LIBRARIES})
ENDIF()

include_directories( ${UI_INCLUDE} )
link_directories( ${UI_LINK} )
add_definitions( ${UI_DEFS} )

add_executable(testui testui.cpp)
target_link_libraries(
    testui
    gui
    ${UI_LIBS}
)
