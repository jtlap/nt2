//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_OPERATOR_FUNCTIONS_GENERIC_MINNUMMAG_HPP_INCLUDED
#define NT2_AD_OPERATOR_FUNCTIONS_GENERIC_MINNUMMAG_HPP_INCLUDED

#include <nt2/include/functions/minnummag.hpp>
#include <nt2/include/functions/is_less.hpp>
#include <nt2/include/functions/if_else_zero.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T1, class T2> BOOST_FORCEINLINE
    valder<T1> minnummag(const valder<T1>&u, const valder<T2>&v)
    {
      return valder<T1>(nt2::minnummag(u.val(), v.val())
                       , nt2::if_else(is_less(nt2::abs(u.val()), nt2::abs(v.val()))
                                     , u.der(), v.der())
                       );
    };
    template < class T1, class T2 > BOOST_FORCEINLINE
    valder<T2> minnummag(const T1&u, const valder<T2>&v)
    {
      return valder<T2>(nt2::minnummag(u, v.val())
                       , nt2::if_zero_else(is_less(nt2::abs(u), nt2::abs(v.val()))
                                          , v.der())
                       );
    };
    template < class T1, class T2 > BOOST_FORCEINLINE
    valder<T1> minnummag(const valder<T1>&u, const T2&v)
    {
      return valder<T1>(nt2::minnummag(u.val(), v)
                       , nt2::if_else_zero(is_less(nt2::abs(u.val()), nt2::abs(v))
                                          , u.der())
                       );
    };
  }
}

#endif
