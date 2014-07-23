# shihchin.weng@gmail.com

if(DEFINED ENV{MAYA_ROOT})
    set(MAYA_ROOT $ENV{MAYA_ROOT})
endif()

if(NOT DEFINED MAYA_ROOT)
    message(FATAL_ERROR "Can't find Maya root!")
endif()

find_path(MAYA_INCLUDE_DIR maya/MTypes.h
          PATHS ${MAYA_ROOT}/include
          NO_DEFAULT_PATH
          NO_CMAKE_ENVIRONMENT_PATH
          NO_CMAKE_PATH
          NO_SYSTEM_ENVIRONMENT_PATH
          NO_CMAKE_SYSTEM_PATH
          DOC "The directory where MTypes.h resides")

set(LIBRARY_DIRS ${MAYA_ROOT}/lib)
macro(FIND_MAYA_LIB lib_name libraries)
    string(TOUPPER ${lib_name} LIB_NAME)
    find_library(MAYA_${LIB_NAME}_LIBRARY ${lib_name}
        PATHS ${LIBRARY_DIRS}
        DOC "The directory where ${lib_name}.lib resides"
        NO_DEFAULT_PATH)
    list(APPEND ${libraries} ${MAYA_${LIB_NAME}_LIBRARY})
    mark_as_advanced(${MAYA_${LIB_NAME}_LIBRARY})
endmacro(FIND_MAYA_LIB)


unset(MAYA_SDK_LIBRARIES CACHE)
set(LIB_LIST Foundation OpenMaya OpenMayaAnim OpenMayaFX OpenMayaRender OpenMayaUI)
foreach(LIB ${LIB_LIST})
    FIND_MAYA_LIB(${LIB} MAYA_SDK_LIBRARIES)
endforeach()

include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(MAYA DEFAULT_MSG MAYA_SDK_LIBRARIES MAYA_INCLUDE_DIR)

if(MAYA_FOUND)
    set(MAYA_INCLUDE_DIRS ${MAYA_INCLUDE_DIR})
    set(MAYA_LIBRARIES ${MAYA_SDK_LIBRARIES})
    message(STATUS "Found Maya ${MAYA_ROOT}")
endif()
mark_as_advanced(MAYA_INCLUDE_DIR MAYA_SDK_LIBRARIES)
