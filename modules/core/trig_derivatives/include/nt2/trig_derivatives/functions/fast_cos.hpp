//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_FAST_COS_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_FAST_COS_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/fast_cos.hpp>
#include <nt2/include/functions/simd/fast_cos.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of fast_cos at x
    by fast_cos<N>(x)
    @see @funcref{fast_cos}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::fast_cos_, fast_cos, 2)


  template < long N, class T> BOOST_FORCEINLINE T fast_cos(const T & x)
  {
    return fast_cos(boost::mpl::long_<N>(), x);
  }

}

#endif

