# shihchin.weng@gmail.com

set(LIBRARY_DIRS
    ${ILMBASE_ROOT}/lib
    /usr/lib
    /usr/local/lib
    /opt/local/lib)

find_path(ILMBASE_INCLUDE_DIR OpenEXR/ImathMath.h
    PATHS
    ${ILMBASE_ROOT}/include
    /usr/include
    /usr/local/include
    /opt/local/include
    PATH_SUFFIXES OpenEXR)

macro(FIND_ILMBASE_LIB lib_name libraries)
    string(TOUPPER ${lib_name} LIB_NAME)
    find_library(ILMBASE_${LIB_NAME}_LIBRARY ${lib_name}
        PATHS ${LIBRARY_DIRS}
        DOC "The directory where ${lib_name}.lib resides"
        NO_DEFAULT_PATH)
    list(APPEND ${libraries} ${ILMBASE_${LIB_NAME}_LIBRARY})
    mark_as_advanced(${ILMBASE_${LIB_NAME}_LIBRARY})
endmacro(FIND_ILMBASE_LIB)

unset(ILMBASE_LIBRARIES CACHE)
set(LIB_LIST Half Iex Imath IlmThread)
foreach(LIB ${LIB_LIST})
    FIND_ILMBASE_LIB(${LIB} ILMBASE_LIBRARIES)
endforeach()

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(ILMBASE DEFAULT_MSG ILMBASE_LIBRARIES ILMBASE_INCLUDE_DIR)

if(ILMBASE_FOUND)
    set(ILMBASE_INCLUDE_DIRS ${ILMBASE_INCLUDE_DIR} CACHE STRING "The include paths IlmBase")
    message(STATUS "Found IlmBase libraries: ${ILMBASE_LIBRARIES}")
endif()
