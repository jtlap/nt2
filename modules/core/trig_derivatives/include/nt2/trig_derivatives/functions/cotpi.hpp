//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_COTPI_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_COTPI_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/cotpi.hpp>
#include <nt2/include/functions/simd/cotpi.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of cotpi at x
    by cotpi<N>(x)
    @see @funcref{cotpi}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::cotpi_, cotpi, 2)


  template < long N, class T> BOOST_FORCEINLINE T cotpi(const T & x)
  {
    return cotpi(boost::mpl::long_<N>(), x);
  }

}

#endif

