//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_OPERATOR_FUNCTIONS_GENERIC_IF_ZERO_ELSE_ONE_HPP_INCLUDED
#define NT2_AD_OPERATOR_FUNCTIONS_GENERIC_IF_ZERO_ELSE_ONE_HPP_INCLUDED

#include <nt2/include/functions/if_zero_else_one.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class L> BOOST_FORCEINLINE
    valder<L> if_zero_else_one(const valder<L> & l)
    {
      typedef typename valder<L>::elem_t elem_t;
      return valder<L>(nt2::if_zero_else_one(l.val())
                      , Zero<elem_t>());
    }
  }
}

#endif
