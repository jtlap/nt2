//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_TRIGONOMETRIC_FUNCTIONS_GENERIC_SINCOS_HPP_INCLUDED
#define NT2_AD_TRIGONOMETRIC_FUNCTIONS_GENERIC_SINCOS_HPP_INCLUDED

#include <nt2/trigonometric/include/functions/simd/sincos.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/ad/functions/ad.hpp>
#include <boost/fusion/include/std_pair.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T> BOOST_FORCEINLINE
    void sincos(const valder<T>&u,  valder<T>&vs,  valder<T>&vc)
    {
      T s, c;
      nt2::sincos(u.val(), s, c);
      vs = valder<T>(s, c*u.der());
      vc = valder<T>(c, -s*u.der());
    };


    template < class T> BOOST_FORCEINLINE
    valder<T> sincos(const valder<T>&u,  valder<T>&vc)
    {
      T s, c;
      nt2::sincos(u.val(), s, c);
      vc = valder<T>(c, -s*u.der());
      return valder<T>(s, c*u.der());
    }

    template < class T> BOOST_FORCEINLINE
    std::pair<valder<T>, valder<T>>
    sincos(const valder<T>&u)
    {
      T s, c;
      nt2::sincos(u.val(), s, c);
      return result_type(valder<T>(s, c*u.der())
                        , valder<T>(c, -s*u.der()));
    }
  }
}


#endif
