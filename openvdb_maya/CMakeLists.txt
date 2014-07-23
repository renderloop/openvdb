# shihchin.weng@gmail.com

set(OPENVDB_MAYA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

if(WIN32)
	execute_process(COMMAND cmd.exe /c mklink /D openvdb_maya maya WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()

add_subdirectory(maya)