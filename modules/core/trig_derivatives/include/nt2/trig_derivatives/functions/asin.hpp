//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_ASIN_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_ASIN_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/asin.hpp>
#include <nt2/include/functions/simd/asin.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of asin at x
    by asin<N>(x)
    @see @funcref{asin}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::asin_, asin, 2)


  template < long N, class T> BOOST_FORCEINLINE T asin(const T & x)
  {
    return asin(boost::mpl::long_<N>(), x);
  }

}

#endif

