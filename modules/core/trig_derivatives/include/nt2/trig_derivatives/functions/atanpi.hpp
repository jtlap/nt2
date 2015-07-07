//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_ATANPI_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_ATANPI_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/atanpi.hpp>
#include <nt2/include/functions/simd/atanpi.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of atanpi at x
    by atanpi<N>(x)
    @see @funcref{atanpi}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::atanpi_, atanpi, 2)


  template < long N, class T> BOOST_FORCEINLINE T atanpi(const T & x)
  {
    return atanpi(boost::mpl::long_<N>(), x);
  }

}

#endif

