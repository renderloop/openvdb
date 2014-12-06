# shihchin.weng@gmail.com

file(GLOB H_FILES *.h)
file(GLOB CXX_FILES *.cc *.cpp)
set(SOURCE_FILES ${H_FILES} ${CXX_FILES})

find_package(opengl REQUIRED)

include_directories(
    ${OPENVDB_INCLUDE_DIRS}
    ${OPENVDB_MAYA_SOURCE_DIR}
    ${MAYA_INCLUDE_DIRS})

link_directories(${Boost_LIBRARY_DIRS})

if(WIN32)
    find_package(glew REQUIRED)
    include_directories(${GLEW_INCLUDE_DIRS})

    set(MAYA_EXTENSION ".mll")
    set(MAYA_COMPILE_FLAGS "/MD /D \"NT_PLUGIN\" /D \"REQUIRE_IOSTREAM\" /D \"_BOOL\"")
    set(MAYA_LINK_FLAGS "/export:initializePlugin /export:uninitializePlugin")
endif()

add_library(openvdb_maya MODULE ${SOURCE_FILES})

target_link_libraries(openvdb_maya openvdb
    ${MAYA_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${OPENVDB_LINK_LIBRARIES})

if(WIN32)
    target_link_libraries(openvdb_maya ${GLEW_LIBRARIES})
endif()

set_target_properties(openvdb_maya
  PROPERTIES
  COMPILE_FLAGS ${MAYA_COMPILE_FLAGS}
  LINK_FLAGS ${MAYA_LINK_FLAGS}
  SUFFIX ${MAYA_EXTENSION})

install(TARGETS openvdb_maya
    DESTINATION maya/plug-ins
    RENAME OpenVDB)

file(GLOB SCRIPTS *.mel)
install(FILES ${SCRIPTS} DESTINATION maya/scripts)
