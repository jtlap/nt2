//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_SINPI_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_SINPI_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/sinpi.hpp>
#include <nt2/include/functions/simd/sinpi.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of sinpi at x
    by sinpi<N>(x)
    @see @funcref{sinpi}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::sinpi_, sinpi, 2)


  template < long N, class T> BOOST_FORCEINLINE T sinpi(const T & x)
  {
    return sinpi(boost::mpl::long_<N>(), x);
  }

}

#endif

