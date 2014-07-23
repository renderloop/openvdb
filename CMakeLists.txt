# shihchin.weng@gmail.com

cmake_minimum_required(VERSION 2.8)
project(OPENVDB)

set(PROJECT_VERSION_MAJOR  2)
set(PROJECT_VERSION_MINOR  3)
set(PROJECT_VERSION_PATCH  0)
set(PROJECT_VERSION
    ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH} )
set(VERSION ${PROJECT_VERSION})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/build)

# Create symlink
if(WIN32)
    execute_process(COMMAND cmd.exe /c mklink /D openvdb_viewer openvdb\\viewer WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
endif()

#set(Boost_USE_STATIC_LIBS TRUE)
#set(Boost_USE_MULTITHREADED TRUE)
find_package(boost)
find_package(zlib REQUIRED)
find_package(ilmbase REQUIRED)
find_package(tbb REQUIRED)

if(WIN32)
    option(BUILD_STATIC "Build static library" ON)
    if(BUILD_STATIC)
        add_definitions(-DOPENVDB_STATICLIB)
    endif()

    option(LINK_STATIC_OPENEXR "Link static OpenEXR library." ON)
    if(LINK_STATIC_OPENEXR)
        add_definitions(-DOPENVDB_OPENEXR_STATICLIB)
    endif()

    add_definitions(-DNOMINMAX)
        #-DTBB_USE_CAPTURED_EXCEPTION=1
        #-D_HAS_ITERATOR_DEBUGGING=0
        #-D_CRT_SECURE_NO_WARNINGS=1)
endif()

set(OPENVDB_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
    ${TBB_INCLUDE_DIR}
    ${ILMBASE_INCLUDE_DIRS}
    ${ZLIB_INCLUDE_DIRS})

set(OPENVDB_LINK_LIBRARIES
    ${TBB_LIBRARIES}
    ${ILMBASE_HALF_LIBRARY}
    ${ZLIB_LIBRARIES})

add_subdirectory(openvdb)

# option(BUILD_OPENVDB_HOUDINI "Build Houdini OpenVDB SOPs" OFF)
option(BUILD_OPENVDB_MAYA "Build OpenVDB for MAYA" OFF)

# if(BUILD_OPENVDB_HOUDINI)
#     add_subdirectory(openvdb_houdini)
# endif()

if(BUILD_OPENVDB_MAYA)
    find_package(Maya REQUIRED)
    add_subdirectory(openvdb_maya)
endif()