//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_EXPONENTIAL_FUNCTIONS_GENERIC_NTHROOT_HPP_INCLUDED
#define NT2_AD_EXPONENTIAL_FUNCTIONS_GENERIC_NTHROOT_HPP_INCLUDED

#include <nt2/exponential/include/functions/simd/nthroot.hpp>
#include <nt2/include/functions/simd/d_nthroot.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T, class N> BOOST_FORCEINLINE
    valder<T> nthroot(const valder<T>&u, const N& n)
    {
      return valder<T>(nt2::nthroot(u.val(), n), d_nthroot(u.val(), n)*u.der());
    };
  }
}

#endif
