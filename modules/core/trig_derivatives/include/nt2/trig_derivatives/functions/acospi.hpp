//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_ACOSPI_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_ACOSPI_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/acospi.hpp>
#include <nt2/include/functions/simd/acospi.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of acospi at x
    by acospi<N>(x)
    @see @funcref{acospi}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::acospi_, acospi, 2)


  template < long N, class T> BOOST_FORCEINLINE T acospi(const T & x)
  {
    return acospi(boost::mpl::long_<N>(), x);
  }

}

#endif

