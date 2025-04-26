########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(GSL_FIND_QUIETLY)
    set(GSL_MESSAGE_MODE VERBOSE)
else()
    set(GSL_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/module-GSLTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${gsl_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(GSL_VERSION_STRING "2.7")
set(GSL_INCLUDE_DIRS ${gsl_INCLUDE_DIRS_RELEASE} )
set(GSL_INCLUDE_DIR ${gsl_INCLUDE_DIRS_RELEASE} )
set(GSL_LIBRARIES ${gsl_LIBRARIES_RELEASE} )
set(GSL_DEFINITIONS ${gsl_DEFINITIONS_RELEASE} )


# Only the last installed configuration BUILD_MODULES are included to avoid the collision
foreach(_BUILD_MODULE ${gsl_BUILD_MODULES_PATHS_RELEASE} )
    message(${GSL_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


include(FindPackageHandleStandardArgs)
set(GSL_FOUND 1)
set(GSL_VERSION "2.7")

find_package_handle_standard_args(GSL
                                  REQUIRED_VARS GSL_VERSION
                                  VERSION_VAR GSL_VERSION)
mark_as_advanced(GSL_FOUND GSL_VERSION)

set(GSL_FOUND 1)
set(GSL_VERSION "2.7")
mark_as_advanced(GSL_FOUND GSL_VERSION)

