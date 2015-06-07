//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_OPERATOR_FUNCTIONS_GENERIC_MINMOD_HPP_INCLUDED
#define NT2_AD_OPERATOR_FUNCTIONS_GENERIC_MINMOD_HPP_INCLUDED

#include <nt2/include/functions/minmod.hpp>
#include <nt2/include/functions/is_nltz.hpp>
#include <nt2/include/functions/if_else_zero.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T1, class T2> BOOST_FORCEINLINE
    valder<T1> minmod(const valder<T1>&u, const valder<T2>&v)
    {
      return if_else_zero(is_nltz(u.val()*v.val()), min(u, v));
    };
    template < class T1, class T2 > BOOST_FORCEINLINE
    valder<T2> minmod(const T1&u, const valder<T2>&v)
    {
         return if_else_zero(is_nltz(u*v.val()), min(u, v));
    };
    template < class T1, class T2 > BOOST_FORCEINLINE
    valder<T1> minmod(const valder<T1>&u, const T2&v)
    {
      return if_else_zero(is_nltz(u.val()*v), min(u, v));
    };
  }
}

#endif
