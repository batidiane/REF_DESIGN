/* -*- c++ -*- */
/* 
 * Copyright 2013 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include <math.h>
#include "change_fb_impl.h"

namespace gr {
  namespace cw_binary {

    change_fb::sptr
    change_fb::make(float epsilon)
    {
      return gnuradio::get_initial_sptr
        (new change_fb_impl(epsilon));
    }

    /*
     * The private constructor
     */
    change_fb_impl::change_fb_impl(float epsilon)
      : gr::sync_block("change_fb",
              gr::io_signature::make(1, 1, sizeof(float)),
              gr::io_signature::make(1, 1, sizeof(char)))
    {
        _epsilon = epsilon;
        _last = 0;
        _started = false;
    }

    /*
     * Our virtual destructor.
     */
    change_fb_impl::~change_fb_impl()
    {
    }

    int
    change_fb_impl::work(int noutput_items,
			  gr_vector_const_void_star &input_items,
			  gr_vector_void_star &output_items)
    {
        const float *in = (const float *) input_items[0];
        char *out = (char *) output_items[0];

        // Do <+signal processing+>
        for(size_t i = 0; i < noutput_items; i++) {
            if (_started && abs(_last - in[i]) > _epsilon) {
                out[i] = 1;
            } else {
                out[i] = 0;
            }
            _started = true;
            _last = in[i];
        }

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace cw_binary */
} /* namespace gr */

