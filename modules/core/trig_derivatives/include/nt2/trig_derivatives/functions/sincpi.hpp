//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_SINCPI_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_SINCPI_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/sincpi.hpp>
#include <nt2/include/functions/simd/sincpi.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of sincpi at x
    by sincpi<N>(x)
    @see @funcref{sincpi}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::sincpi_, sincpi, 2)


  template < long N, class T> BOOST_FORCEINLINE T sincpi(const T & x)
  {
    return sincpi(boost::mpl::long_<N>(), x);
  }

}

#endif

