# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(qcdnum_FRAMEWORKS_FOUND_RELEASE "") # Will be filled later
conan_find_apple_frameworks(qcdnum_FRAMEWORKS_FOUND_RELEASE "${qcdnum_FRAMEWORKS_RELEASE}" "${qcdnum_FRAMEWORK_DIRS_RELEASE}")

set(qcdnum_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET qcdnum_DEPS_TARGET)
    add_library(qcdnum_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET qcdnum_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Release>:${qcdnum_FRAMEWORKS_FOUND_RELEASE}>
             $<$<CONFIG:Release>:${qcdnum_SYSTEM_LIBS_RELEASE}>
             $<$<CONFIG:Release>:>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### qcdnum_DEPS_TARGET to all of them
conan_package_library_targets("${qcdnum_LIBS_RELEASE}"    # libraries
                              "${qcdnum_LIB_DIRS_RELEASE}" # package_libdir
                              "${qcdnum_BIN_DIRS_RELEASE}" # package_bindir
                              "${qcdnum_LIBRARY_TYPE_RELEASE}"
                              "${qcdnum_IS_HOST_WINDOWS_RELEASE}"
                              qcdnum_DEPS_TARGET
                              qcdnum_LIBRARIES_TARGETS  # out_libraries_targets
                              "_RELEASE"
                              "qcdnum"    # package_name
                              "${qcdnum_NO_SONAME_MODE_RELEASE}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${qcdnum_BUILD_DIRS_RELEASE} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Release ########################################
    set_property(TARGET qcdnum::qcdnum
                 APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Release>:${qcdnum_OBJECTS_RELEASE}>
                 $<$<CONFIG:Release>:${qcdnum_LIBRARIES_TARGETS}>
                 )

    if("${qcdnum_LIBS_RELEASE}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET qcdnum::qcdnum
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     qcdnum_DEPS_TARGET)
    endif()

    set_property(TARGET qcdnum::qcdnum
                 APPEND PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Release>:${qcdnum_LINKER_FLAGS_RELEASE}>)
    set_property(TARGET qcdnum::qcdnum
                 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Release>:${qcdnum_INCLUDE_DIRS_RELEASE}>)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET qcdnum::qcdnum
                 APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Release>:${qcdnum_LIB_DIRS_RELEASE}>)
    set_property(TARGET qcdnum::qcdnum
                 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Release>:${qcdnum_COMPILE_DEFINITIONS_RELEASE}>)
    set_property(TARGET qcdnum::qcdnum
                 APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Release>:${qcdnum_COMPILE_OPTIONS_RELEASE}>)

########## For the modules (FindXXX)
set(qcdnum_LIBRARIES_RELEASE qcdnum::qcdnum)
