//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_ACOT_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_ACOT_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/acot.hpp>
#include <nt2/include/functions/simd/acot.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of acot at x
    by acot<N>(x)
    @see @funcref{acot}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::acot_, acot, 2)


  template < long N, class T> BOOST_FORCEINLINE T acot(const T & x)
  {
    return acot(boost::mpl::long_<N>(), x);
  }

}

#endif

