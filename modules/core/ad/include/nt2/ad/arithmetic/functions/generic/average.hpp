//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_OPERATOR_FUNCTIONS_GENERIC_AVERAGE_HPP_INCLUDED
#define NT2_AD_OPERATOR_FUNCTIONS_GENERIC_AVERAGE_HPP_INCLUDED

#include <nt2/include/functions/average.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T1, class T2> BOOST_FORCEINLINE
    valder<T1> average(const valder<T1>&u, const valder<T2>&v)
    {
      return valder<T1>(nt2::average(u.val(), v.val()), nt2::average(u.der(), v.der()));
    };
    template < class T1, class T2 > BOOST_FORCEINLINE
    valder<T2> average(const T1&u, const valder<T2>&v)
    {
      typedef typename valder<T2>::elem_t elem_t;
      return valder<T2>(nt2::average(u, v.val()), v.der()*Half<elem_t>());
    };
    template < class T1, class T2 > BOOST_FORCEINLINE
    valder<T1> average(const valder<T1>&u, const T2&v)
    {
      typedef typename valder<T2>::elem_t elem_t;
      return valder<T1>(nt2::average(u.val(), v), u.der()*Half<elem_t>());
    };
  }
}

#endif
