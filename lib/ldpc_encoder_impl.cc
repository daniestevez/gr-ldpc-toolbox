/* -*- c++ -*- */
/*
 * Copyright 2023 Daniel Estevez <daniel@destevez.net>.
 *
 * This file is part of gr-ldpc-toolbox
 *
 * SPDX-License-Identifier: MIT
 */

#include "ldpc_encoder_impl.h"
#include <gnuradio/io_signature.h>

#include <ldpc_toolbox.h>
#include <cstdint>
#include <stdexcept>

namespace gr {
namespace ldpc_toolbox {

ldpc_encoder::sptr
ldpc_encoder::make(const std::string& alist, const std::string& puncturing, int n, int k)
{
    return gnuradio::make_block_sptr<ldpc_encoder_impl>(alist, puncturing, n, k);
}

ldpc_encoder_impl::ldpc_encoder_impl(const std::string& alist,
                                     const std::string& puncturing,
                                     int n,
                                     int k)
    : gr::sync_block("ldpc_encoder",
                     gr::io_signature::make(1, 1, k * sizeof(uint8_t)),
                     gr::io_signature::make(1, 1, n * sizeof(uint8_t))),
      d_n(n),
      d_k(k),
      d_encoder(nullptr)
{
    d_encoder = ldpc_toolbox_encoder_ctor(alist.c_str(), puncturing.c_str());
    if (!d_encoder) {
        throw std::runtime_error("LDPC encoder could not be constructed");
    }
}

ldpc_encoder_impl::~ldpc_encoder_impl()
{
    if (d_encoder) {
        ldpc_toolbox_encoder_dtor(d_encoder);
    }
}

int ldpc_encoder_impl::work(int noutput_items,
                            gr_vector_const_void_star& input_items,
                            gr_vector_void_star& output_items)
{
    auto in = static_cast<const uint8_t*>(input_items[0]);
    auto out = static_cast<uint8_t*>(output_items[0]);

    for (int j = 0; j < noutput_items; ++j) {
        ldpc_toolbox_encoder_encode(d_encoder, out, d_n, in, d_k);
        out += d_n;
        in += d_k;
    }

    return noutput_items;
}

} /* namespace ldpc_toolbox */
} /* namespace gr */
