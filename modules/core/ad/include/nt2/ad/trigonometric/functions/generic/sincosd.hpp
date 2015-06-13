//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_TRIGONOMETRIC_FUNCTIONS_GENERIC_SINCOSD_HPP_INCLUDED
#define NT2_AD_TRIGONOMETRIC_FUNCTIONS_GENERIC_SINCOSD_HPP_INCLUDED

#include <nt2/trigonometric/include/functions/simd/sincosd.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/ad/functions/ad.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <nt2/include/constants/deginrad.hpp>

namespace nt2
{
  namespace ad
  {
    template < class T>
    void sincosd(const valder<T>&u,  valder<T>&vs,  valder<T>&vc)
    {
      typedef typename valder<T>::elem_t elem_t;
      T s, c;
      nt2::sincosd(u.val(), s, c);
      auto tmp = u.der()*Deginrad<elem_t>();
      vs = valder<T>(s, c*tmp);
      vc = valder<T>(c, -s*tmp);
    };


    template < class T>
    valder<T> sincosd(const valder<T>&u,  valder<T>&vc)
    {
      typedef typename valder<T>::elem_t elem_t;
      T s, c;
      nt2::sincosd(u.val(), s, c);
      auto tmp = u.der()*Deginrad<elem_t>();
      vc = valder<T>(c, -s*tmp);
      return valder<T>(s, c*tmp);
    }

    template < class T>
    std::pair<valder<T>, valder<T>>
    sincosd(const valder<T>&u)
    {
      typedef typename valder<T>::elem_t elem_t;
      T s, c;
      nt2::sincosd(u.val(), s, c);
      auto tmp = u.der()*Deginrad<elem_t>();
      return result_type(valder<T>(s, c*tmp)
                        , valder<T>(c, -s*tmp));
    }
  }
}


#endif
