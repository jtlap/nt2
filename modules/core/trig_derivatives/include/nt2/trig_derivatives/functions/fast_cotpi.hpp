//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_FAST_COTPI_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_FAST_COTPI_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/fast_cotpi.hpp>
#include <nt2/include/functions/simd/fast_cotpi.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of fast_cotpi at x
    by fast_cotpi<N>(x)
    @see @funcref{fast_cotpi}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::fast_cotpi_, fast_cotpi, 2)


  template < long N, class T> BOOST_FORCEINLINE T fast_cotpi(const T & x)
  {
    return fast_cotpi(boost::mpl::long_<N>(), x);
  }

}

#endif

