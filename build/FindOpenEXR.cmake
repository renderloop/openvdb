# shihchin.weng@gmail.com

set(LIBRARY_DIRS
    ${OPENEXR_ROOT}/lib
    /usr/lib
    /usr/local/lib
    /sw/lib
    /opt/local/lib
    $ENV{PROGRAM_FILES}/OpenEXR/lib/static)

find_path(OPENEXR_INCLUDE_DIR OpenEXR/ImfRgbaFile.h
    PATHS
    ${OPENEXR_ROOT}/include
    /usr/include
    /usr/local/include
    /sw/include
    /opt/local/include)

macro(FIND_OPENEXR_LIB lib_name libraries)
    string(TOUPPER ${lib_name} LIB_NAME)
    find_library(OPENEXR_${LIB_NAME}_LIBRARY ${lib_name}
        PATHS ${LIBRARY_DIRS}
        DOC "The directory where ${lib_name}.lib resides"
        NO_DEFAULT_PATH)
    list(APPEND ${libraries} ${OPENEXR_${LIB_NAME}_LIBRARY})
    mark_as_advanced(${OPENEXR_${LIB_NAME}_LIBRARY})
endmacro(FIND_OPENEXR_LIB)

unset(OPENEXR_LIBRARIES CACHE)
set(LIB_LIST Half Iex Imath IlmImf IlmThread)
foreach(LIB ${LIB_LIST})
    FIND_OPENEXR_LIB(${LIB} OPENEXR_LIBRARIES)
endforeach()

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(OPENEXR DEFAULT_MSG OPENEXR_LIBRARIES OPENEXR_INCLUDE_DIR)

if(OPENEXR_FOUND)
    set(OPENEXR_INCLUDE_DIRS ${OPENEXR_INCLUDE_DIR})
    message(STATUS "Found OpenEXR! ${OPENEXR_LIBRARIES}")
endif()