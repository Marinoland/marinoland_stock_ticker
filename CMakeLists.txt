cmake_minimum_required(VERSION 2.8)
project (stock_ticker)

if(NOT EXISTS ./depend)
	execute_process(COMMAND git clone git@github.com:Marinoland/marinoland_depend.git depend)
	execute_process(COMMAND cmake . WORKING_DIRECTORY depend)
endif()

if(WIN32)
    set(CMAKE_WIN32_EXECUTABLE ON)
ENDIF()

file(STRINGS depend/depend.includedirs DEP_INC_DIRS)
file(STRINGS depend/depend.linkdirs DEP_LINK_DIRS)
file(STRINGS depend/depend.libs DEP_LIBS)
file(STRINGS depend/depend.defs DEP_DEFS)

include_directories( ${UI_INC_DIRS} )
link_directories( ${DEP_LINK_DIRS} )
add_definitions( ${DEP_DEFS} )

add_executable(testui testui.cpp)
target_link_libraries(
    testui
    ${DEP_LIBS}
)
