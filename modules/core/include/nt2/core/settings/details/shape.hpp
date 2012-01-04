//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_DETAILS_SHAPE_HPP_INCLUDED
#define NT2_CORE_SETTINGS_DETAILS_SHAPE_HPP_INCLUDED

#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/buffer.hpp>
#include <nt2/sdk/memory/iliffe_buffer.hpp>

namespace nt2
{
  //============================================================================
  // Use iliffe_buffer to build a proper buffer
  //============================================================================
  struct rectangular_
  {
    template<class T, class S>
    struct apply
    {
      typedef typename meta::option<S,tag::buffer_>::type           buffer_t;

      typedef memory::iliffe_buffer < boost::mpl::_2
                                    , boost::mpl::_3
                                    >                               model_t;

      typedef typename buffer_t::template apply<model_t,T,S>::type  type;
    };
  };
}

#include <nt2/sdk/memory/rectangular_block.hpp>

#endif
