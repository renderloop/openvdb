file(GLOB H_FILES *.h)
file(GLOB CXX_FILES *.cc *.cpp)
set(SOURCE_FILES ${H_FILES} ${CXX_FILES})

add_executable(openvdb_print ${SOURCE_FILES})
target_link_libraries(openvdb_print openvdb ${OPENVDB_LINK_LIBRARIES})
install(TARGETS openvdb_print DESTINATION bin)