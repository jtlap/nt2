//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_OPERATOR_FUNCTIONS_GENERIC_UNARY_PLUS_HPP_INCLUDED
#define NT2_AD_OPERATOR_FUNCTIONS_GENERIC_UNARY_PLUS_HPP_INCLUDED

#include <nt2/include/functions/unary_plus.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T> BOOST_FORCEINLINE
    valder<T> operator+(const valder<T>&u)
    {
      return u;
    };

    template < class T> BOOST_FORCEINLINE
    valder<T> unary_plus(const valder<T>&u)
    {
      return u;
    };
  }
}

#endif
