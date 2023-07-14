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
    from gnuradio.ldpc_toolbox import ldpc_decoder
except ImportError:
    import os
    import sys
    dirname, filename = os.path.split(os.path.abspath(__file__))
    sys.path.append(os.path.join(dirname, "bindings"))
    from gnuradio.ldpc_toolbox import ldpc_decoder


class qa_ldpc_decoder(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_instance(self):
        datadir = pathlib.Path(__file__).parent
        instance = ldpc_decoder(
            str(datadir / 'ar4ja_1_2_1024.alist'), 'Phif64', '1,1,1,1,0',
            2048, 1024, 200)

    def test_decode_codeword(self):
        n = 2048
        k = 1024
        datadir = pathlib.Path(__file__).parent
        self.decoder = ldpc_decoder(
            str(datadir / 'ar4ja_1_2_1024.alist'), 'Phif64', '1,1,1,1,0',
            n, k, 200)
        codeword = np.fromfile(datadir / 'ar4ja_1_2_1024_codeword', 'uint8')
        # Enough LLR "amplitude" is required for the decoder to successfully
        # solve the punctured symbols. We use amplitude 3 instead of amplitude
        # 1.
        symbols = (1 - 2*codeword[:n].astype('float')) * 3.0
        self.source = blocks.vector_source_f(symbols, False, n)
        self.sink = blocks.vector_sink_b(k, 1)
        self.tb.connect(self.source, self.decoder, self.sink)

        self.tb.run()

        self.assertEqual(self.sink.data(), list(codeword[:k]))


if __name__ == '__main__':
    gr_unittest.run(qa_ldpc_decoder)
