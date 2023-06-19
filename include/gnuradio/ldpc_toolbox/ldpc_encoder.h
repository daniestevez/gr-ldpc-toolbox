/* -*- c++ -*- */
/*
 * Copyright 2023 Daniel Estevez <daniel@destevez.net>.
 *
 * This file is part of gr-ldpc-toolbox
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef INCLUDED_LDPC_TOOLBOX_LDPC_ENCODER_H
#define INCLUDED_LDPC_TOOLBOX_LDPC_ENCODER_H

#include <gnuradio/ldpc_toolbox/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace ldpc_toolbox {

/*!
 * \brief LDPC Encoder
 * \ingroup ldpc_toolbox
 *
 */
class LDPC_TOOLBOX_API ldpc_encoder : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<ldpc_encoder> sptr;

    /*!
     * \brief Creates an LDPC Encoder.
     *
     * \param alist Path to the alist file defining the LDPC code.
     * \param puncturing Puncturing pattern (either "" or something like "1,1,1,1,0").
     * \param n LDPC code (n,k) parameter n.
     * \param k LDPC code (n,k) parameter k.
     */
    static sptr
    make(const std::string& alist, const std::string& puncturing, int n, int k);
};

} // namespace ldpc_toolbox
} // namespace gr

#endif /* INCLUDED_LDPC_TOOLBOX_LDPC_ENCODER_H */
