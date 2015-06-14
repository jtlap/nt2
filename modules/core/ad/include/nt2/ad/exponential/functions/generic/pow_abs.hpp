//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_EXPONENTIAL_FUNCTIONS_GENERIC_POW_ABS_HPP_INCLUDED
#define NT2_AD_EXPONENTIAL_FUNCTIONS_GENERIC_POW_ABS_HPP_INCLUDED

#include <nt2/exponential/include/functions/simd/pow_abs.hpp>
#include <nt2/include/functions/simd/abs.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/pow_abs.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T1, class T2> BOOST_FORCEINLINE
    valder<T1> pow_abs(const valder<T1>&u, const valder<T2>&v)
    {
      T1 au =  nt2::abs(u.val());
      T1  puv = nt2::pow_abs(au, v.val());
      return valder<T1>(puv, puv*(v.val()/au)*u.der()+puv*nt2::log(au)*v.der());
    };

    template < class T1, class T2> BOOST_FORCEINLINE
    valder<T1> pow_abs(const valder<T1>&u, const T2&v)
    {
      T1 au =  nt2::abs(u.val());
      T1  puv = nt2::pow_abs(au, v);
      return valder<T1>(puv, puv*(v/au)*u.der());
    };

    template < class T1, class T2> BOOST_FORCEINLINE
    valder<T1> pow_abs(const T1&u, const valder<T2>&v)
    {
      T1 au =  nt2::abs(u);
      T1  puv = nt2::pow_abs(au, v.val());
      return valder<T1>(puv, puv*nt2::log(au)*v.der());
    };
  }
}

#endif
