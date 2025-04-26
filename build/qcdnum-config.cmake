########## MACROS ###########################################################################
#############################################################################################

# Requires CMake > 3.15
if(${CMAKE_VERSION} VERSION_LESS "3.15")
    message(FATAL_ERROR "The 'CMakeDeps' generator only works with CMake >= 3.15")
endif()

if(qcdnum_FIND_QUIETLY)
    set(qcdnum_MESSAGE_MODE VERBOSE)
else()
    set(qcdnum_MESSAGE_MODE STATUS)
endif()

include(${CMAKE_CURRENT_LIST_DIR}/cmakedeps_macros.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/qcdnumTargets.cmake)
include(CMakeFindDependencyMacro)

check_build_type_defined()

foreach(_DEPENDENCY ${qcdnum_FIND_DEPENDENCY_NAMES} )
    # Check that we have not already called a find_package with the transitive dependency
    if(NOT ${_DEPENDENCY}_FOUND)
        find_dependency(${_DEPENDENCY} REQUIRED ${${_DEPENDENCY}_FIND_MODE})
    endif()
endforeach()

set(qcdnum_VERSION_STRING "1.0")
set(qcdnum_INCLUDE_DIRS ${qcdnum_INCLUDE_DIRS_RELEASE} )
set(qcdnum_INCLUDE_DIR ${qcdnum_INCLUDE_DIRS_RELEASE} )
set(qcdnum_LIBRARIES ${qcdnum_LIBRARIES_RELEASE} )
set(qcdnum_DEFINITIONS ${qcdnum_DEFINITIONS_RELEASE} )


# Only the last installed configuration BUILD_MODULES are included to avoid the collision
foreach(_BUILD_MODULE ${qcdnum_BUILD_MODULES_PATHS_RELEASE} )
    message(${qcdnum_MESSAGE_MODE} "Conan: Including build module from '${_BUILD_MODULE}'")
    include(${_BUILD_MODULE})
endforeach()


