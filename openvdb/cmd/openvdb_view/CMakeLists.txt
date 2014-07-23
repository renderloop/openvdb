file(GLOB H_FILES *.h)
file(GLOB CXX_FILES *.cc *.cpp)
set(SOURCE_FILES ${H_FILES} ${CXX_FILES})

find_package(opengl REQUIRED)
find_package(glfw REQUIRED)
set(LINK_LIBS
	${OPENVDB_LINK_LIBRARIES}
	${OPENGL_LIBRARIES}
	${GLFW_LIBRARIES})

# include_directories(${OPENVDB_SOURCE_DIR})

if(WIN32)
    find_package(glew REQUIRED)
    #include_directories(${GLEW_INCLUDE_DIRS})
    list(APPEND LINK_LIBS ${GLEW_LIBRARIES})
endif()

add_executable(openvdb_view ${SOURCE_FILES})
target_link_libraries(openvdb_view openvdb openvdb_viewer ${LINK_LIBS})
install(TARGETS openvdb_view DESTINATION bin)