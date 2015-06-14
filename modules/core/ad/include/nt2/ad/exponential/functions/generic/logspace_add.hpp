//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_EXPONENTIAL_FUNCTIONS_GENERIC_LOGSPACE_ADD_HPP_INCLUDED
#define NT2_AD_EXPONENTIAL_FUNCTIONS_GENERIC_LOGSPACE_ADD_HPP_INCLUDED

#include <nt2/exponential/include/functions/simd/logspace_add.hpp>
#include <nt2/include/functions/simd/d1_logspace_add.hpp>
#include <nt2/include/functions/simd/d2_logspace_add.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/logspace_add.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T1, class T2> BOOST_FORCEINLINE
    valder<T1> logspace_add(const valder<T1>&u, const valder<T2>&v)
    {
      return valder<T1>( nt2::logspace_add(u.val(), v.val())
                       , d1_logspace_add(u.val(), v.val())*u.der()+
                         d2_logspace_add(u.val(), v.val())*v.der());
    };

    template < class T1, class T2> BOOST_FORCEINLINE
    valder<T1> logspace_add(const valder<T1>&u, const T2&v)
    {
      return valder<T1>( nt2::logspace_add(u.val(), v)
                       , d1_logspace_add(u.val(), v.val())*u.der());
    };

    template < class T1, class T2> BOOST_FORCEINLINE
    valder<T1> logspace_add(const T1&u, const valder<T2>&v)
    {
      return valder<T1>( nt2::logspace_add(u.val(), v)
                       , d2_logspace_add(u.val(), v)*v.der());
    };
  }
}

#endif
