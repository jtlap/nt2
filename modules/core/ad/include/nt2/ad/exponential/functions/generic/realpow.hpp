//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_EXPONENTIAL_FUNCTIONS_GENERIC_REALPOW_HPP_INCLUDED
#define NT2_AD_EXPONENTIAL_FUNCTIONS_GENERIC_REALPOW_HPP_INCLUDED

#include <nt2/exponential/include/functions/simd/realpow.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/realpow.hpp>
#include <nt2/ad/functions/ad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T1, class T2> BOOST_FORCEINLINE
    valder<T1> realpow(const valder<T1>&u, const valder<T2>&v)
    {
      T1  puv = nt2::realpow(u.val(), v.val());
      return valder<T1>(puv, puv*(v.val()/u.val())*u.der()+puv*nt2::log(u.val())*v.der());
    };

    template < class T1, class T2> BOOST_FORCEINLINE
    valder<T1> realpow(const valder<T1>&u, const T2&v)
    {
      T1  puv = nt2::realpow(u.val(), v);
      return valder<T1>(puv, puv*(v/u.val())*u.der());
    };

    template < class T1, class T2> BOOST_FORCEINLINE
    valder<T1> realpow(const T1&u, const valder<T2>&v)
    {
      T1  puv = nt2::realpow(u, v.val());
      return valder<T1>(puv, puv*nt2::log(u)*v.der());
    };
  }
}

#endif
