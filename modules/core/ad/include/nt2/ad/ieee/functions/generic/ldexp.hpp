//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_PREDICATES_FUNCTIONS_GENERIC_LDEXP_HPP_INCLUDED
#define NT2_AD_PREDICATES_FUNCTIONS_GENERIC_LDEXP_HPP_INCLUDED

#include <nt2/include/functions/ldexp.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/include/functions/pow2.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class A1, class A2> BOOST_FORCEINLINE
    valder<A1> ldexp(const valder<A1> & a1
                    , const A2 & a2)
    {
      return valder<A1>(nt2::ldexp(a1.val(), a2),
                        a1.der()*nt2::pow2(a2));
    }
  }
}

#endif
