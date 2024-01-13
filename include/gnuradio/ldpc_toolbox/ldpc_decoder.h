/* -*- c++ -*- */
/*
 * Copyright 2023 Daniel Estevez <daniel@destevez.net>.
 *
 * This file is part of gr-ldpc-toolbox
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef INCLUDED_LDPC_TOOLBOX_LDPC_DECODER_H
#define INCLUDED_LDPC_TOOLBOX_LDPC_DECODER_H

#include <gnuradio/block.h>
#include <gnuradio/ldpc_toolbox/api.h>

namespace gr {
namespace ldpc_toolbox {

LDPC_TOOLBOX_API const pmt::pmt_t iterations_key();

/*!
 * \brief LDPC Decoder
 * \ingroup ldpc_toolbox
 *
 */
class LDPC_TOOLBOX_API ldpc_decoder : virtual public gr::block
{
public:
    typedef std::shared_ptr<ldpc_decoder> sptr;

    /*!
     * \brief Creates an LDPC Decoder.
     *
     * \param alist Path to the alist file defining the LDPC code.
     * \param implementation Name of the decoder implementation to use.
     * \param puncturing Puncturing pattern (either "" or something like "1,1,1,1,0").
     * \param n LDPC code (n,k) parameter n.
     * \param k LDPC code (n,k) parameter k.
     * \param max_iterations Maximum number of decoder iterations.
     */
    static sptr make(const std::string& alist,
                     const std::string& implementation,
                     const std::string& puncturing,
                     int n,
                     int k,
                     int max_iterations);
};

} // namespace ldpc_toolbox
} // namespace gr

#endif /* INCLUDED_LDPC_TOOLBOX_LDPC_DECODER_H */
