/* -*- c++ -*- */
/*
 * Copyright 2023 Daniel Estevez <daniel@destevez.net>.
 *
 * This file is part of gr-ldpc-toolbox
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef INCLUDED_LDPC_TOOLBOX_LDPC_ENCODER_IMPL_H
#define INCLUDED_LDPC_TOOLBOX_LDPC_ENCODER_IMPL_H

#include <gnuradio/ldpc_toolbox/ldpc_encoder.h>

namespace gr {
namespace ldpc_toolbox {

class ldpc_encoder_impl : public ldpc_encoder
{
private:
    const int d_n;
    const int d_k;
    void* d_encoder;

public:
    ldpc_encoder_impl(const std::string& alist,
                      const std::string& puncturing,
                      int n,
                      int k);
    ~ldpc_encoder_impl() override;

    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items) override;
};

} // namespace ldpc_toolbox
} // namespace gr

#endif /* INCLUDED_LDPC_TOOLBOX_LDPC_ENCODER_IMPL_H */
