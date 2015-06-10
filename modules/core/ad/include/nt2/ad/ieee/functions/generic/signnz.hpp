//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_PREDICATES_FUNCTIONS_GENERIC_SIGNNZ_HPP_INCLUDED
#define NT2_AD_PREDICATES_FUNCTIONS_GENERIC_SIGNNZ_HPP_INCLUDED

#include <nt2/include/functions/signnz.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class L> BOOST_FORCEINLINE
    valder<L> signnz(const valder<L> & l)
    {
      typedef typename valder<L>::elem_t elem_t;
      return valder<L>(nt2::signnz(l.val())
                      , Zero<elem_t>());
    }
  }
}

#endif
