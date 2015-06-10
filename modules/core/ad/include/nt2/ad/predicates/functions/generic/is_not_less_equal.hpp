//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_PREDICATES_FUNCTIONS_GENERIC_IS_NOT_LESS_EQUAL_HPP_INCLUDED
#define NT2_AD_PREDICATES_FUNCTIONS_GENERIC_IS_NOT_LESS_EQUAL_HPP_INCLUDED

#include <nt2/include/functions/is_not_less_equal.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class A1, class A2> BOOST_FORCEINLINE
    typename meta::as_logical<A1>::type
    is_not_less_equal(const valder<A1> & a1, const valder<A2> & a2)
    {
      return nt2::is_not_less_equal(a1.val(), a2.val());
    }
    template < class A1, class A2> BOOST_FORCEINLINE
    typename meta::as_logical<A1>::type
    is_not_less_equal(const A1 & a1, const valder<A2> & a2)
    {
      return nt2::is_not_less_equal(a1, a2.val());
    }
    template < class A1, class A2> BOOST_FORCEINLINE
    typename meta::as_logical<A1>::type
    is_not_less_equal(const valder<A1> & a1, const A2 & a2)
    {
      return nt2::is_not_less_equal(a1.val(), a2);
    }
  }
}

#endif
