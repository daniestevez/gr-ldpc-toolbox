# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT ldpc_toolbox_sources)
    MESSAGE(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT ldpc_toolbox_sources)

########################################################################
# Check for pygccxml
########################################################################
GR_PYTHON_CHECK_MODULE_RAW(
    "pygccxml"
    "import pygccxml"
    PYGCCXML_FOUND
    )

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND ldpc_toolbox_python_files
    ldpc_decoder_python.cc python_bindings.cc)

GR_PYBIND_MAKE_OOT(ldpc_toolbox
   ../../..
   gr::ldpc_toolbox
   "${ldpc_toolbox_python_files}")

# copy bindings extension for use in QA test module
add_custom_command(TARGET ldpc_toolbox_python POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:ldpc_toolbox_python>
    ${PROJECT_BINARY_DIR}/test_modules/gnuradio/ldpc_toolbox/
)

install(TARGETS ldpc_toolbox_python DESTINATION ${GR_PYTHON_DIR}/gnuradio/ldpc_toolbox COMPONENT pythonapi)
