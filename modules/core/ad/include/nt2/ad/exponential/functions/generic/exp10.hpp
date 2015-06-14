//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_EXPONENTIAL_FUNCTIONS_GENERIC_EXP10_HPP_INCLUDED
#define NT2_AD_EXPONENTIAL_FUNCTIONS_GENERIC_EXP10_HPP_INCLUDED

#include <nt2/exponential/include/functions/simd/exp10.hpp>
#include <nt2/include/functions/simd/d_exp10.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T> BOOST_FORCEINLINE
    valder<T> exp10(const valder<T>&u)
    {
      return valder<T>(nt2::exp10(u.val()), d_exp10(u.val())*u.der());
    };
  }
}

#endif
