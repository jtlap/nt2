//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_AD_ARITHMETIC_FUNCTIONS_GENERIC_ABS_HPP_INCLUDED
#define NT2_AD_ARITHMETIC_FUNCTIONS_GENERIC_ABS_HPP_INCLUDED
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/sign.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/ad/functions/ad.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>
#include <boost/assert.hpp>


namespace nt2
{
  namespace ad
  {
    template < class T>
    valder<T> abs(const valder<T>&u)
    {
      typedef typename etype<valder<T>>::type elem_t;
      BOOST_ASSERT_MSG(!nt2::meta::is_complex<elem_t>::value, "ad abs is only defined for floating");
      return valder<T>(nt2::abs(u.val()), nt2::sign(u.val())*u.der());
    };
  }
}

#endif
