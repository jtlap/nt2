//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_OPERATOR_FUNCTIONS_GENERIC_REC_HPP_INCLUDED
#define NT2_AD_OPERATOR_FUNCTIONS_GENERIC_REC_HPP_INCLUDED

#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/unary_minus.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T> BOOST_FORCEINLINE
    valder<T> rec(const valder<T>&u)
    {
      typedef typename valder<T>::elem_t elem_t;
      auto tmp = nt2::rec(u.val());
      return valder<T>(tmp, -nt2::sqr(tmp)*u.der());
    };
  }
}

#endif
