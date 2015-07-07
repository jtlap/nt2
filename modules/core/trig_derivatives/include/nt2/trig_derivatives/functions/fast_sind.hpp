//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_FAST_SIND_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_FAST_SIND_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/fast_sind.hpp>
#include <nt2/include/functions/simd/fast_sind.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of fast_sind at x
    by fast_sind<N>(x)
    @see @funcref{fast_sind}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::fast_sind_, fast_sind, 2)


  template < long N, class T> BOOST_FORCEINLINE T fast_sind(const T & x)
  {
    return fast_sind(boost::mpl::long_<N>(), x);
  }

}

#endif

