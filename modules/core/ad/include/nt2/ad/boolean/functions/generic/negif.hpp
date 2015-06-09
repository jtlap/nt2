//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_OPERATOR_FUNCTIONS_GENERIC_NEGIF_HPP_INCLUDED
#define NT2_AD_OPERATOR_FUNCTIONS_GENERIC_NEGIF_HPP_INCLUDED

#include <nt2/include/functions/negif.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class L, class T> BOOST_FORCEINLINE
    valder<T> negif(const L & l, const valder<T>&u)
    {
      return valder<T>(nt2::negif(l, u.val())
                      , nt2::negif(l, u.der()));
    };
    template < class L, class T> BOOST_FORCEINLINE
    valder<T> negif(const valder<L> & l
                   , const T&u)
    {
      typedef typename valder<T>::elem_t elem_t;
      return valder<T>(nt2::negif(l.val(), u)
                      , Zero<elem_t>());
    };
    template < class L, class T> BOOST_FORCEINLINE
    valder<T> negif(const valder<L> & l
                   , const valder<T>&u)
    {
      return valder<T>(nt2::negif(l.val(), u.val())
                      , nt2::negif(l.val(), u.der()));
    };
  }
}

#endif
