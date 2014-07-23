file(GLOB H_FILES "*.h")
file(GLOB CXX_FILES "*.cc")
set(SOURCE_FILES ${H_FILES} ${CXX_FILES})

find_package(glfw REQUIRED)
include_directories(${OPENVDB_INCLUDE_DIRS} ${GLFW_INCLUDE_DIRS})
set(LINK_LIBS ${GLFW_LIBRARIES})

if(WIN32)
    find_package(glew REQUIRED)
    include_directories(${GLEW_INCLUDE_DIRS})
    list(APPEND LINK_LIBS ${GLEW_LIBRARIES})

    add_definitions(-DNOGDI -DWIN32_LEAN_AND_MEAN -D_USE_MATH_DEFINES)
endif()

add_library(openvdb_viewer ${SOURCE_FILES})
target_link_libraries(openvdb_viewer openvdb ${LINK_LIBS})
