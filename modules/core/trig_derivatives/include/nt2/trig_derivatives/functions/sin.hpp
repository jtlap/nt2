//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_SIN_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_SIN_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/sin.hpp>
#include <nt2/include/functions/simd/sin.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of sin at x
    by sin<N>(x)
    @see @funcref{sin}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::sin_, sin, 2)


  template < long N, class T> BOOST_FORCEINLINE T sin(const T & x)
  {
    return sin(boost::mpl::long_<N>(), x);
  }

}

#endif

