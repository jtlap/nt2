//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_TAN_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_TAN_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/tan.hpp>
#include <nt2/include/functions/simd/tan.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of tan at x
    by tan<N>(x)
    @see @funcref{tan}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::tan_, tan, 2)


  template < long N, class T> BOOST_FORCEINLINE T tan(const T & x)
  {
    return tan(boost::mpl::long_<N>(), x);
  }

}

#endif

