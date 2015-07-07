//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_CSCPI_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_CSCPI_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/cscpi.hpp>
#include <nt2/include/functions/simd/cscpi.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of cscpi at x
    by cscpi<N>(x)
    @see @funcref{cscpi}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::cscpi_, cscpi, 2)


  template < long N, class T> BOOST_FORCEINLINE T cscpi(const T & x)
  {
    return cscpi(boost::mpl::long_<N>(), x);
  }

}

#endif

