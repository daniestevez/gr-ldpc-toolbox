find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_LDPC_TOOLBOX gnuradio-ldpc_toolbox)

FIND_PATH(
    GR_LDPC_TOOLBOX_INCLUDE_DIRS
    NAMES gnuradio/ldpc_toolbox/api.h
    HINTS $ENV{LDPC_TOOLBOX_DIR}/include
        ${PC_LDPC_TOOLBOX_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_LDPC_TOOLBOX_LIBRARIES
    NAMES gnuradio-ldpc_toolbox
    HINTS $ENV{LDPC_TOOLBOX_DIR}/lib
        ${PC_LDPC_TOOLBOX_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-ldpc_toolboxTarget.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_LDPC_TOOLBOX DEFAULT_MSG GR_LDPC_TOOLBOX_LIBRARIES GR_LDPC_TOOLBOX_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_LDPC_TOOLBOX_LIBRARIES GR_LDPC_TOOLBOX_INCLUDE_DIRS)
