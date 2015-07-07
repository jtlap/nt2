//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_ASINPI_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_ASINPI_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/asinpi.hpp>
#include <nt2/include/functions/simd/asinpi.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of asinpi at x
    by asinpi<N>(x)
    @see @funcref{asinpi}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::asinpi_, asinpi, 2)


  template < long N, class T> BOOST_FORCEINLINE T asinpi(const T & x)
  {
    return asinpi(boost::mpl::long_<N>(), x);
  }

}

#endif

