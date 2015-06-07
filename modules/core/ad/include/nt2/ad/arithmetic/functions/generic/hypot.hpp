//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_OPERATOR_FUNCTIONS_GENERIC_HYPOT_HPP_INCLUDED
#define NT2_AD_OPERATOR_FUNCTIONS_GENERIC_HYPOT_HPP_INCLUDED

#include <nt2/include/functions/hypot.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T1, class T2> BOOST_FORCEINLINE
    valder<T1> hypot(const valder<T1>&u, const valder<T2>&v)
    {
      typedef typename valder<T2>::elem_t elem_t;
      auto tmp = nt2::hypot(u.val(), v.val());
      return valder<T1>(tmp, nt2::rec(tmp)*nt2::fma(u.val(), u.der(), v.val()*v.der()));
    };
    template < class T1, class T2 > BOOST_FORCEINLINE
    valder<T2> hypot(const T1&u, const valder<T2>&v)
    {
      typedef typename valder<T2>::elem_t elem_t;
      auto tmp = nt2::hypot(u, v.val());
      return valder<T2>(nt2::hypot(u, v.val()), nt2::rec(tmp)*v.val()*v.der());
    };
    template < class T1, class T2 > BOOST_FORCEINLINE
    valder<T1> hypot(const valder<T1>&u, const T2&v)
    {
      typedef typename valder<T2>::elem_t elem_t;
      auto tmp = nt2::hypot(u.val(), v);
      return valder<T1>(nt2::hypot(u.val(), v),  nt2::rec(tmp)*u.val()*u.der());
    };
  }
}

#endif
