//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_SECPI_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_SECPI_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/secpi.hpp>
#include <nt2/include/functions/simd/secpi.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of secpi at x
    by secpi<N>(x)
    @see @funcref{secpi}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::secpi_, secpi, 2)


  template < long N, class T> BOOST_FORCEINLINE T secpi(const T & x)
  {
    return secpi(boost::mpl::long_<N>(), x);
  }

}

#endif

