//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_PREDICATES_FUNCTIONS_GENERIC_MAJORITY_HPP_INCLUDED
#define NT2_AD_PREDICATES_FUNCTIONS_GENERIC_MAJORITY_HPP_INCLUDED

#include <nt2/include/functions/majority.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class L1, class L2, class L3> BOOST_FORCEINLINE
    typename meta::as_logical<L1>::type
    majority(const valder<L1> & l1, const valder<L2> & l2, const valder<L3> & l3)
    {
      return nt2::majority(l1.val(), l2.val(), l3.val());
    }
  }
}

#endif
