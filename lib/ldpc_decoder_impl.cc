/* -*- c++ -*- */
/*
 * Copyright 2023 Daniel Estevez <daniel@destevez.net>.
 *
 * This file is part of gr-ldpc-toolbox
 *
 * SPDX-License-Identifier: MIT
 */

#include "ldpc_decoder_impl.h"
#include <gnuradio/io_signature.h>

#include <ldpc_toolbox.h>
#include <cstdint>
#include <stdexcept>

namespace gr {
namespace ldpc_toolbox {

const pmt::pmt_t iterations_key()
{
    static const auto key = pmt::string_to_symbol("iterations");
    return key;
}

ldpc_decoder::sptr ldpc_decoder::make(const std::string& alist,
                                      const std::string& implementation,
                                      const std::string& puncturing,
                                      int n,
                                      int k,
                                      int max_iterations)
{
    return gnuradio::make_block_sptr<ldpc_decoder_impl>(
        alist, implementation, puncturing, n, k, max_iterations);
}

ldpc_decoder_impl::ldpc_decoder_impl(const std::string& alist,
                                     const std::string& implementation,
                                     const std::string& puncturing,
                                     int n,
                                     int k,
                                     int max_iterations)
    : gr::block("ldpc_decoder",
                gr::io_signature::make(1, 1, n * sizeof(float)),
                gr::io_signature::make(1, 1, k * sizeof(uint8_t))),
      d_n(n),
      d_k(k),
      d_max_iterations(max_iterations),
      d_decoder(nullptr)
{
    d_decoder = ldpc_toolbox_decoder_ctor(
        alist.c_str(), implementation.c_str(), puncturing.c_str());
    if (!d_decoder) {
        throw std::runtime_error("LDPC decoder could not be constructed");
    }
}

ldpc_decoder_impl::~ldpc_decoder_impl()
{
    if (d_decoder) {
        ldpc_toolbox_decoder_dtor(d_decoder);
    }
}

void ldpc_decoder_impl::forecast(int noutput_items, gr_vector_int& ninput_items_required)
{
    // assume that all codewords will be decoded succesfully
    ninput_items_required[0] = noutput_items;
}

int ldpc_decoder_impl::general_work(int noutput_items,
                                    gr_vector_int& ninput_items,
                                    gr_vector_const_void_star& input_items,
                                    gr_vector_void_star& output_items)
{
    auto in = static_cast<const float*>(input_items[0]);
    auto out = static_cast<uint8_t*>(output_items[0]);
    int produced = 0;
    int consumed = 0;

    while ((consumed < ninput_items[0]) && (produced < noutput_items)) {
        const int32_t ret = ldpc_toolbox_decoder_decode_f32(
            d_decoder, out, d_k, in, d_n, d_max_iterations);
        if (ret >= 0) {
            // decoder success
            add_item_tag(
                0, nitems_written(0) + produced, iterations_key(), pmt::from_long(ret));
            ++produced;
            out += d_k;
        } else {
            d_logger->debug("decoding failed");
        }
        ++consumed;
        in += d_n;
    }

    consume(0, consumed);

    return produced;
}

} /* namespace ldpc_toolbox */
} /* namespace gr */
