//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_COS_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_COS_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/cos.hpp>
#include <nt2/include/functions/simd/cos.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of cos at x
    by cos<N>(x)
    @see @funcref{cos}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::cos_, cos, 2)


  template < long N, class T> BOOST_FORCEINLINE T cos(const T & x)
  {
    return cos(boost::mpl::long_<N>(), x);
  }

}

#endif

