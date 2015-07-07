//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_ATAN2_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_ATAN2_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/atan2.hpp>
#include <nt2/include/functions/simd/atan2.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Ith derivative of atan2 at x, Jth at yy
    by atan2<I, J>(x, y)
    @see @funcref{atan2}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::atan2_, atan2, 4)


  template < long P, long Q, class T, class U>
  BOOST_FORCEINLINE T atan2(const T & x, const U & y)
  {
    return atan2(boost::mpl::long_<P>(),boost::mpl::long_<Q>(), x, y);
  }

}

#endif

