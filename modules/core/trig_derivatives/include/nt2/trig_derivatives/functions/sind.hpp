//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_SIND_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_SIND_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/sind.hpp>
#include <nt2/include/functions/simd/sind.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of sind at x
    by sind<N>(x)
    @see @funcref{sind}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::sind_, sind, 2)


  template < long N, class T> BOOST_FORCEINLINE T sind(const T & x)
  {
    return sind(boost::mpl::long_<N>(), x);
  }

}

#endif

