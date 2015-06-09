//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_PREDICATES_FUNCTIONS_GENERIC_IS_UNORD_HPP_INCLUDED
#define NT2_AD_PREDICATES_FUNCTIONS_GENERIC_IS_UNORD_HPP_INCLUDED

#include <nt2/include/functions/is_unord.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class L1, class L2> BOOST_FORCEINLINE
    typename meta::as_logical<L1>::type
    is_unord(const valder<L1> & l1, const valder<L2> & l2)
    {
      return nt2::is_unord(l1.val(), l2.val());
    }
  }
}

#endif
