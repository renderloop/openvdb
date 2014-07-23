file(GLOB H_FILES *.h)
file(GLOB CXX_FILES *.cc *.cpp)
set(SOURCE_FILES ${H_FILES} ${CXX_FILES})

find_package(OpenEXR REQUIRED)

if(NOT OPENEXR_FOUND)
	message(FATAL "Can't find OpenEXR library!")
endif()

include_directories(${OPENVDB_INCLUDE_DIR} ${OPENEXR_INCLUDE_DIRS})

add_executable(openvdb_render ${SOURCE_FILES})
target_link_libraries(openvdb_render openvdb openvdb_viewer
	${OPENVDB_LINK_LIBRARIES}
    ${OPENEXR_LIBRARIES})

install(TARGETS openvdb_render DESTINATION bin)