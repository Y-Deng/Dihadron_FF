########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(qcdnum_COMPONENT_NAMES "")
if(DEFINED qcdnum_FIND_DEPENDENCY_NAMES)
  list(APPEND qcdnum_FIND_DEPENDENCY_NAMES )
  list(REMOVE_DUPLICATES qcdnum_FIND_DEPENDENCY_NAMES)
else()
  set(qcdnum_FIND_DEPENDENCY_NAMES )
endif()

########### VARIABLES #######################################################################
#############################################################################################
set(qcdnum_PACKAGE_FOLDER_RELEASE "/root/.conan2/p/b/qcdnu32c1a22ccb0f1/p")
set(qcdnum_BUILD_MODULES_PATHS_RELEASE )


set(qcdnum_INCLUDE_DIRS_RELEASE "${qcdnum_PACKAGE_FOLDER_RELEASE}/include")
set(qcdnum_RES_DIRS_RELEASE )
set(qcdnum_DEFINITIONS_RELEASE )
set(qcdnum_SHARED_LINK_FLAGS_RELEASE )
set(qcdnum_EXE_LINK_FLAGS_RELEASE )
set(qcdnum_OBJECTS_RELEASE )
set(qcdnum_COMPILE_DEFINITIONS_RELEASE )
set(qcdnum_COMPILE_OPTIONS_C_RELEASE )
set(qcdnum_COMPILE_OPTIONS_CXX_RELEASE )
set(qcdnum_LIB_DIRS_RELEASE "${qcdnum_PACKAGE_FOLDER_RELEASE}/lib")
set(qcdnum_BIN_DIRS_RELEASE )
set(qcdnum_LIBRARY_TYPE_RELEASE UNKNOWN)
set(qcdnum_IS_HOST_WINDOWS_RELEASE 0)
set(qcdnum_LIBS_RELEASE QCDNUM)
set(qcdnum_SYSTEM_LIBS_RELEASE )
set(qcdnum_FRAMEWORK_DIRS_RELEASE )
set(qcdnum_FRAMEWORKS_RELEASE )
set(qcdnum_BUILD_DIRS_RELEASE )
set(qcdnum_NO_SONAME_MODE_RELEASE FALSE)


# COMPOUND VARIABLES
set(qcdnum_COMPILE_OPTIONS_RELEASE
    "$<$<COMPILE_LANGUAGE:CXX>:${qcdnum_COMPILE_OPTIONS_CXX_RELEASE}>"
    "$<$<COMPILE_LANGUAGE:C>:${qcdnum_COMPILE_OPTIONS_C_RELEASE}>")
set(qcdnum_LINKER_FLAGS_RELEASE
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${qcdnum_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${qcdnum_SHARED_LINK_FLAGS_RELEASE}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${qcdnum_EXE_LINK_FLAGS_RELEASE}>")


set(qcdnum_COMPONENTS_RELEASE )