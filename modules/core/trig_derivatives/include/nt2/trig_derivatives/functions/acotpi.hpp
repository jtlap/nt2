//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_ACOTPI_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_ACOTPI_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/acotpi.hpp>
#include <nt2/include/functions/simd/acotpi.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of acotpi at x
    by acotpi<N>(x)
    @see @funcref{acotpi}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::acotpi_, acotpi, 2)


  template < long N, class T> BOOST_FORCEINLINE T acotpi(const T & x)
  {
    return acotpi(boost::mpl::long_<N>(), x);
  }

}

#endif

