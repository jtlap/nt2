//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_OPERATOR_FUNCTIONS_GENERIC_MAX_HPP_INCLUDED
#define NT2_AD_OPERATOR_FUNCTIONS_GENERIC_MAX_HPP_INCLUDED

#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/if_else_zero.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T1, class T2> BOOST_FORCEINLINE
    valder<T1> max(const valder<T1>&u, const valder<T2>&v)
    {
      return valder<T1>(nt2::max(u.val(), v.val())
                       , nt2::if_else(is_greater(u.val(), v.val()), u.der(), v.der())
                       );
    };
    template < class T1, class T2 > BOOST_FORCEINLINE
    valder<T2> max(const T1&u, const valder<T2>&v)
    {
      return valder<T2>(nt2::max(u, v.val())
                       , nt2::if_zero_else(is_greater(u, v.val()), v.der())
                       );
    };
    template < class T1, class T2 > BOOST_FORCEINLINE
    valder<T1> max(const valder<T1>&u, const T2&v)
    {
      return valder<T1>(nt2::max(u.val(), v)
                       , nt2::if_else_zero(is_greater(u.val(), v), u.der())
                       );

    };
  }
}

#endif
