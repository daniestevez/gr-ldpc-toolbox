/* -*- c++ -*- */
/*
 * Copyright 2023 Daniel Estevez <daniel@destevez.net>.
 *
 * This file is part of gr-ldpc-toolbox
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef INCLUDED_LDPC_TOOLBOX_LDPC_DECODER_IMPL_H
#define INCLUDED_LDPC_TOOLBOX_LDPC_DECODER_IMPL_H

#include <gnuradio/ldpc_toolbox/ldpc_decoder.h>

namespace gr {
namespace ldpc_toolbox {

class ldpc_decoder_impl : public ldpc_decoder
{
private:
    const int d_n;
    const int d_k;
    const int d_max_iterations;
    void* d_decoder;

public:
    ldpc_decoder_impl(const std::string& alist,
                      const std::string& implementation,
                      const std::string& puncturing,
                      int n,
                      int k,
                      int max_iterations);
    ~ldpc_decoder_impl() override;

    void forecast(int noutput_items, gr_vector_int& ninput_items_required) override;

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items) override;
};

} // namespace ldpc_toolbox
} // namespace gr

#endif /* INCLUDED_LDPC_TOOLBOX_LDPC_DECODER_IMPL_H */
