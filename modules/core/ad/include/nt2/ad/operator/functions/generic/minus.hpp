//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef _NT2_AD_OPERATOR_FUNCTIONS_GENERIC_MINUS_HPP_INCLUDED
#define _NT2_AD_OPERATOR_FUNCTIONS_GENERIC_MINUS_HPP_INCLUDED

#include <nt2/include/functions/minus.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T1, class T2>
    valder<T1> operator-(const valder<T1>&u, const valder<T2>&v)
    {
      return valder<T1>(u.val()-v.val(), u.der()-v.der());
    };
    template < class T1, class T2 >
    valder<T2> operator-(const T1&u, const valder<T2>&v)
    {
      return valder<T2>(u-v.val(), -v.der());
    };
    template < class T1, class T2 >
    valder<T1> operator-(const valder<T1>&u, const T2&v)
    {
      return valder<T1>(u.val()-v, u.der());
    };

    template < class T1, class T2>
    valder<T1> minus(const valder<T1>&u, const valder<T2>&v)
    {
      return valder<T1>(u.val()-v.val(), u.der()-v.der());
    };
    template < class T1, class T2 >
    valder<T2> minus(const T1&u, const valder<T2>&v)
    {
      return valder<T2>(u-v.val(), -v.der());
    };
    template < class T1, class T2 >
    valder<T1> minus(const valder<T1>&u, const T2&v)
    {
      return valder<T1>(u.val()-v, u.der());
    };
  }
}

#endif
