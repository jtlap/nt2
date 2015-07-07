//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_COTD_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_COTD_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/cotd.hpp>
#include <nt2/include/functions/simd/cotd.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of cotd at x
    by cotd<N>(x)
    @see @funcref{cotd}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::cotd_, cotd, 2)


  template < long N, class T> BOOST_FORCEINLINE T cotd(const T & x)
  {
    return cotd(boost::mpl::long_<N>(), x);
  }

}

#endif

