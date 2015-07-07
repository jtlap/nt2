//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_FAST_COSD_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_FAST_COSD_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/fast_cosd.hpp>
#include <nt2/include/functions/simd/fast_cosd.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of fast_cosd at x
    by fast_cosd<N>(x)
    @see @funcref{fast_cosd}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::fast_cosd_, fast_cosd, 2)


  template < long N, class T> BOOST_FORCEINLINE T fast_cosd(const T & x)
  {
    return fast_cosd(boost::mpl::long_<N>(), x);
  }

}

#endif

