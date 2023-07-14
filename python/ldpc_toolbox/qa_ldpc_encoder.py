#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2023 Daniel Estevez <daniel@destevez.net>
#
# This file is part of gr-ldpc-toolbox
#
# SPDX-License-Identifier: MIT
#

import pathlib

from gnuradio import gr, gr_unittest, blocks
import numpy as np
try:
    from gnuradio.ldpc_toolbox import ldpc_encoder
except ImportError:
    import os
    import sys
    dirname, filename = os.path.split(os.path.abspath(__file__))
    sys.path.append(os.path.join(dirname, "bindings"))
    from gnuradio.ldpc_toolbox import ldpc_encoder


class qa_ldpc_encoder(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_instance(self):
        datadir = pathlib.Path(__file__).parent
        instance = ldpc_encoder(
            str(datadir / 'ar4ja_1_2_1024.alist'), '1,1,1,1,0',
            2048, 1024)

    def test_001_descriptive_test_name(self):
        n = 2048
        k = 1024
        datadir = pathlib.Path(__file__).parent
        self.encoder = ldpc_encoder(
            str(datadir / 'ar4ja_1_2_1024.alist'), '1,1,1,1,0',
            n, k)
        codeword = np.fromfile(datadir / 'ar4ja_1_2_1024_codeword', 'uint8')
        self.source = blocks.vector_source_b(codeword[:k], False, k)
        self.sink = blocks.vector_sink_b(n, 1)
        self.tb.connect(self.source, self.encoder, self.sink)

        self.tb.run()

        self.assertEqual(self.sink.data(), list(codeword[:n]))


if __name__ == '__main__':
    gr_unittest.run(qa_ldpc_encoder)
