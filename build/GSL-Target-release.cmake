# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(gsl_FRAMEWORKS_FOUND_RELEASE "") # Will be filled later
conan_find_apple_frameworks(gsl_FRAMEWORKS_FOUND_RELEASE "${gsl_FRAMEWORKS_RELEASE}" "${gsl_FRAMEWORK_DIRS_RELEASE}")

set(gsl_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET gsl_DEPS_TARGET)
    add_library(gsl_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET gsl_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Release>:${gsl_FRAMEWORKS_FOUND_RELEASE}>
             $<$<CONFIG:Release>:${gsl_SYSTEM_LIBS_RELEASE}>
             $<$<CONFIG:Release>:GSL::gslcblas>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### gsl_DEPS_TARGET to all of them
conan_package_library_targets("${gsl_LIBS_RELEASE}"    # libraries
                              "${gsl_LIB_DIRS_RELEASE}" # package_libdir
                              "${gsl_BIN_DIRS_RELEASE}" # package_bindir
                              "${gsl_LIBRARY_TYPE_RELEASE}"
                              "${gsl_IS_HOST_WINDOWS_RELEASE}"
                              gsl_DEPS_TARGET
                              gsl_LIBRARIES_TARGETS  # out_libraries_targets
                              "_RELEASE"
                              "gsl"    # package_name
                              "${gsl_NO_SONAME_MODE_RELEASE}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${gsl_BUILD_DIRS_RELEASE} ${CMAKE_MODULE_PATH})

########## COMPONENTS TARGET PROPERTIES Release ########################################

    ########## COMPONENT GSL::gsl #############

        set(gsl_GSL_gsl_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(gsl_GSL_gsl_FRAMEWORKS_FOUND_RELEASE "${gsl_GSL_gsl_FRAMEWORKS_RELEASE}" "${gsl_GSL_gsl_FRAMEWORK_DIRS_RELEASE}")

        set(gsl_GSL_gsl_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET gsl_GSL_gsl_DEPS_TARGET)
            add_library(gsl_GSL_gsl_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET gsl_GSL_gsl_DEPS_TARGET
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${gsl_GSL_gsl_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${gsl_GSL_gsl_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${gsl_GSL_gsl_DEPENDENCIES_RELEASE}>
                     )

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'gsl_GSL_gsl_DEPS_TARGET' to all of them
        conan_package_library_targets("${gsl_GSL_gsl_LIBS_RELEASE}"
                              "${gsl_GSL_gsl_LIB_DIRS_RELEASE}"
                              "${gsl_GSL_gsl_BIN_DIRS_RELEASE}" # package_bindir
                              "${gsl_GSL_gsl_LIBRARY_TYPE_RELEASE}"
                              "${gsl_GSL_gsl_IS_HOST_WINDOWS_RELEASE}"
                              gsl_GSL_gsl_DEPS_TARGET
                              gsl_GSL_gsl_LIBRARIES_TARGETS
                              "_RELEASE"
                              "gsl_GSL_gsl"
                              "${gsl_GSL_gsl_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET GSL::gsl
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${gsl_GSL_gsl_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${gsl_GSL_gsl_LIBRARIES_TARGETS}>
                     )

        if("${gsl_GSL_gsl_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET GSL::gsl
                         APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                         gsl_GSL_gsl_DEPS_TARGET)
        endif()

        set_property(TARGET GSL::gsl APPEND PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${gsl_GSL_gsl_LINKER_FLAGS_RELEASE}>)
        set_property(TARGET GSL::gsl APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${gsl_GSL_gsl_INCLUDE_DIRS_RELEASE}>)
        set_property(TARGET GSL::gsl APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${gsl_GSL_gsl_LIB_DIRS_RELEASE}>)
        set_property(TARGET GSL::gsl APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${gsl_GSL_gsl_COMPILE_DEFINITIONS_RELEASE}>)
        set_property(TARGET GSL::gsl APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${gsl_GSL_gsl_COMPILE_OPTIONS_RELEASE}>)


    ########## COMPONENT GSL::gslcblas #############

        set(gsl_GSL_gslcblas_FRAMEWORKS_FOUND_RELEASE "")
        conan_find_apple_frameworks(gsl_GSL_gslcblas_FRAMEWORKS_FOUND_RELEASE "${gsl_GSL_gslcblas_FRAMEWORKS_RELEASE}" "${gsl_GSL_gslcblas_FRAMEWORK_DIRS_RELEASE}")

        set(gsl_GSL_gslcblas_LIBRARIES_TARGETS "")

        ######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
        if(NOT TARGET gsl_GSL_gslcblas_DEPS_TARGET)
            add_library(gsl_GSL_gslcblas_DEPS_TARGET INTERFACE IMPORTED)
        endif()

        set_property(TARGET gsl_GSL_gslcblas_DEPS_TARGET
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${gsl_GSL_gslcblas_FRAMEWORKS_FOUND_RELEASE}>
                     $<$<CONFIG:Release>:${gsl_GSL_gslcblas_SYSTEM_LIBS_RELEASE}>
                     $<$<CONFIG:Release>:${gsl_GSL_gslcblas_DEPENDENCIES_RELEASE}>
                     )

        ####### Find the libraries declared in cpp_info.component["xxx"].libs,
        ####### create an IMPORTED target for each one and link the 'gsl_GSL_gslcblas_DEPS_TARGET' to all of them
        conan_package_library_targets("${gsl_GSL_gslcblas_LIBS_RELEASE}"
                              "${gsl_GSL_gslcblas_LIB_DIRS_RELEASE}"
                              "${gsl_GSL_gslcblas_BIN_DIRS_RELEASE}" # package_bindir
                              "${gsl_GSL_gslcblas_LIBRARY_TYPE_RELEASE}"
                              "${gsl_GSL_gslcblas_IS_HOST_WINDOWS_RELEASE}"
                              gsl_GSL_gslcblas_DEPS_TARGET
                              gsl_GSL_gslcblas_LIBRARIES_TARGETS
                              "_RELEASE"
                              "gsl_GSL_gslcblas"
                              "${gsl_GSL_gslcblas_NO_SONAME_MODE_RELEASE}")


        ########## TARGET PROPERTIES #####################################
        set_property(TARGET GSL::gslcblas
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     $<$<CONFIG:Release>:${gsl_GSL_gslcblas_OBJECTS_RELEASE}>
                     $<$<CONFIG:Release>:${gsl_GSL_gslcblas_LIBRARIES_TARGETS}>
                     )

        if("${gsl_GSL_gslcblas_LIBS_RELEASE}" STREQUAL "")
            # If the component is not declaring any "cpp_info.components['foo'].libs" the system, frameworks etc are not
            # linked to the imported targets and we need to do it to the global target
            set_property(TARGET GSL::gslcblas
                         APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                         gsl_GSL_gslcblas_DEPS_TARGET)
        endif()

        set_property(TARGET GSL::gslcblas APPEND PROPERTY INTERFACE_LINK_OPTIONS
                     $<$<CONFIG:Release>:${gsl_GSL_gslcblas_LINKER_FLAGS_RELEASE}>)
        set_property(TARGET GSL::gslcblas APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                     $<$<CONFIG:Release>:${gsl_GSL_gslcblas_INCLUDE_DIRS_RELEASE}>)
        set_property(TARGET GSL::gslcblas APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                     $<$<CONFIG:Release>:${gsl_GSL_gslcblas_LIB_DIRS_RELEASE}>)
        set_property(TARGET GSL::gslcblas APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                     $<$<CONFIG:Release>:${gsl_GSL_gslcblas_COMPILE_DEFINITIONS_RELEASE}>)
        set_property(TARGET GSL::gslcblas APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                     $<$<CONFIG:Release>:${gsl_GSL_gslcblas_COMPILE_OPTIONS_RELEASE}>)


    ########## AGGREGATED GLOBAL TARGET WITH THE COMPONENTS #####################
    set_property(TARGET GSL::gsl APPEND PROPERTY INTERFACE_LINK_LIBRARIES GSL::gsl)
    set_property(TARGET GSL::gsl APPEND PROPERTY INTERFACE_LINK_LIBRARIES GSL::gslcblas)

########## For the modules (FindXXX)
set(gsl_LIBRARIES_RELEASE GSL::gsl)
