#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2023 Daniel Estevez <daniel@destevez.net>
#
# This file is part of gr-ldpc-toolbox
#
# SPDX-License-Identifier: MIT
#

'''
gr-ldpc-toolbox

gr-ldpc-toolbox is a GNU Radio out-of-tree module containing a LDPC encoder and
decoder blocks using the ldpc-toolbox Rust library.
'''

import os

# import pybind11 generated symbols into the ldpc_toolbox namespace
from .ldpc_toolbox_python import *
