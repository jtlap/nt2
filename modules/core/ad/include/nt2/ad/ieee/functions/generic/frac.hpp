//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_PREDICATES_FUNCTIONS_GENERIC_FRAC_HPP_INCLUDED
#define NT2_AD_PREDICATES_FUNCTIONS_GENERIC_FRAC_HPP_INCLUDED

#include <nt2/include/functions/frac.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class L> BOOST_FORCEINLINE
    valder<L> frac(const valder<L> & l)
    {
      return valder<L>(nt2::frac(l.val()), l.der());
    }
  }
}

#endif
