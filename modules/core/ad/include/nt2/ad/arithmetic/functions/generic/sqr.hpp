//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_ARITHMETIC_FUNCTIONS_GENERIC_SQR_HPP_INCLUDED
#define NT2_AD_ARITHMETIC_FUNCTIONS_GENERIC_SQR_HPP_INCLUDED
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/ad/functions/ad.hpp>


namespace nt2
{
  namespace ad
  {
    template < class T>
    valder<T> sqr(const valder<T>&u)
    {
      typedef typename etype<valder<T>>::type etype_t;
      return valder<T>(nt2::sqr(u.val()), nt2::Two<etype_t>()*u.val()*u.der());
    };
  }
}

#endif
