//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_ATAN_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_ATAN_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/atan.hpp>
#include <nt2/include/functions/simd/atan.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of atan at x
    by atan<N>(x)
    @see @funcref{atan}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::atan_, atan, 2)


  template < long N, class T> BOOST_FORCEINLINE T atan(const T & x)
  {
    return atan(boost::mpl::long_<N>(), x);
  }

}

#endif

