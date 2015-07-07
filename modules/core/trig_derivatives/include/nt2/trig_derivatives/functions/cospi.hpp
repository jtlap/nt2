//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_COSPI_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_COSPI_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/cospi.hpp>
#include <nt2/include/functions/simd/cospi.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of cospi at x
    by cospi<N>(x)
    @see @funcref{cospi}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::cospi_, cospi, 2)


  template < long N, class T> BOOST_FORCEINLINE T cospi(const T & x)
  {
    return cospi(boost::mpl::long_<N>(), x);
  }

}

#endif

