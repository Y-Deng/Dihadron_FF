########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

list(APPEND gsl_COMPONENT_NAMES GSL::gslcblas GSL::gsl)
list(REMOVE_DUPLICATES gsl_COMPONENT_NAMES)
if(DEFINED gsl_FIND_DEPENDENCY_NAMES)
  list(APPEND gsl_FIND_DEPENDENCY_NAMES )
  list(REMOVE_DUPLICATES gsl_FIND_DEPENDENCY_NAMES)
else()
  set(gsl_FIND_DEPENDENCY_NAMES )
endif()

########### VARIABLES #######################################################################
#############################################################################################
set(gsl_PACKAGE_FOLDER_RELEASE "/root/.conan2/p/b/gsl23eb4a758651d/p")
set(gsl_BUILD_MODULES_PATHS_RELEASE )


set(gsl_INCLUDE_DIRS_RELEASE "${gsl_PACKAGE_FOLDER_RELEASE}/include")
set(gsl_RES_DIRS_RELEASE )
set(gsl_DEFINITIONS_RELEASE )
set(gsl_SHARED_LINK_FLAGS_RELEASE )
set(gsl_EXE_LINK_FLAGS_RELEASE )
set(gsl_OBJECTS_RELEASE )
set(gsl_COMPILE_DEFINITIONS_RELEASE )
set(gsl_COMPILE_OPTIONS_C_RELEASE )
set(gsl_COMPILE_OPTIONS_CXX_RELEASE )
set(gsl_LIB_DIRS_RELEASE "${gsl_PACKAGE_FOLDER_RELEASE}/lib")
set(gsl_BIN_DIRS_RELEASE )
set(gsl_LIBRARY_TYPE_RELEASE STATIC)
set(gsl_IS_HOST_WINDOWS_RELEASE 0)
set(gsl_LIBS_RELEASE gsl gslcblas)
set(gsl_SYSTEM_LIBS_RELEASE m)
set(gsl_FRAMEWORK_DIRS_RELEASE )
set(gsl_FRAMEWORKS_RELEASE )
set(gsl_BUILD_DIRS_RELEASE )
set(gsl_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(gsl_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${gsl_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${gsl_COMPILE_OPTIONS_C_RELEASE}>")
set(gsl_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${gsl_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${gsl_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${gsl_EXE_LINK_FLAGS_RELEASE}>")


set(gsl_COMPONENTS_RELEASE GSL::gslcblas GSL::gsl)
########### COMPONENT GSL::gsl VARIABLES ############################################

set(gsl_GSL_gsl_INCLUDE_DIRS_RELEASE "${gsl_PACKAGE_FOLDER_RELEASE}/include")
set(gsl_GSL_gsl_LIB_DIRS_RELEASE "${gsl_PACKAGE_FOLDER_RELEASE}/lib")
set(gsl_GSL_gsl_BIN_DIRS_RELEASE )
set(gsl_GSL_gsl_LIBRARY_TYPE_RELEASE STATIC)
set(gsl_GSL_gsl_IS_HOST_WINDOWS_RELEASE 0)
set(gsl_GSL_gsl_RES_DIRS_RELEASE )
set(gsl_GSL_gsl_DEFINITIONS_RELEASE )
set(gsl_GSL_gsl_OBJECTS_RELEASE )
set(gsl_GSL_gsl_COMPILE_DEFINITIONS_RELEASE )
set(gsl_GSL_gsl_COMPILE_OPTIONS_C_RELEASE "")
set(gsl_GSL_gsl_COMPILE_OPTIONS_CXX_RELEASE "")
set(gsl_GSL_gsl_LIBS_RELEASE gsl)
set(gsl_GSL_gsl_SYSTEM_LIBS_RELEASE m)
set(gsl_GSL_gsl_FRAMEWORK_DIRS_RELEASE )
set(gsl_GSL_gsl_FRAMEWORKS_RELEASE )
set(gsl_GSL_gsl_DEPENDENCIES_RELEASE GSL::gslcblas)
set(gsl_GSL_gsl_SHARED_LINK_FLAGS_RELEASE )
set(gsl_GSL_gsl_EXE_LINK_FLAGS_RELEASE )
set(gsl_GSL_gsl_NO_SONAME_MODE_RELEASE FALSE)

# COMPOUND VARIABLES
set(gsl_GSL_gsl_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${gsl_GSL_gsl_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${gsl_GSL_gsl_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${gsl_GSL_gsl_EXE_LINK_FLAGS_RELEASE}>
)
set(gsl_GSL_gsl_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${gsl_GSL_gsl_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${gsl_GSL_gsl_COMPILE_OPTIONS_C_RELEASE}>")
########### COMPONENT GSL::gslcblas VARIABLES ############################################

set(gsl_GSL_gslcblas_INCLUDE_DIRS_RELEASE "${gsl_PACKAGE_FOLDER_RELEASE}/include")
set(gsl_GSL_gslcblas_LIB_DIRS_RELEASE "${gsl_PACKAGE_FOLDER_RELEASE}/lib")
set(gsl_GSL_gslcblas_BIN_DIRS_RELEASE )
set(gsl_GSL_gslcblas_LIBRARY_TYPE_RELEASE STATIC)
set(gsl_GSL_gslcblas_IS_HOST_WINDOWS_RELEASE 0)
set(gsl_GSL_gslcblas_RES_DIRS_RELEASE )
set(gsl_GSL_gslcblas_DEFINITIONS_RELEASE )
set(gsl_GSL_gslcblas_OBJECTS_RELEASE )
set(gsl_GSL_gslcblas_COMPILE_DEFINITIONS_RELEASE )
set(gsl_GSL_gslcblas_COMPILE_OPTIONS_C_RELEASE "")
set(gsl_GSL_gslcblas_COMPILE_OPTIONS_CXX_RELEASE "")
set(gsl_GSL_gslcblas_LIBS_RELEASE gslcblas)
set(gsl_GSL_gslcblas_SYSTEM_LIBS_RELEASE m)
set(gsl_GSL_gslcblas_FRAMEWORK_DIRS_RELEASE )
set(gsl_GSL_gslcblas_FRAMEWORKS_RELEASE )
set(gsl_GSL_gslcblas_DEPENDENCIES_RELEASE )
set(gsl_GSL_gslcblas_SHARED_LINK_FLAGS_RELEASE )
set(gsl_GSL_gslcblas_EXE_LINK_FLAGS_RELEASE )
set(gsl_GSL_gslcblas_NO_SONAME_MODE_RELEASE FALSE)

# COMPOUND VARIABLES
set(gsl_GSL_gslcblas_LINKER_FLAGS_RELEASE
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${gsl_GSL_gslcblas_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${gsl_GSL_gslcblas_SHARED_LINK_FLAGS_RELEASE}>
        $<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${gsl_GSL_gslcblas_EXE_LINK_FLAGS_RELEASE}>
)
set(gsl_GSL_gslcblas_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${gsl_GSL_gslcblas_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${gsl_GSL_gslcblas_COMPILE_OPTIONS_C_RELEASE}>")