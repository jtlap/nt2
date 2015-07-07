//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_COT_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_COT_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/cot.hpp>
#include <nt2/include/functions/simd/cot.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of cot at x
    by cot<N>(x)
    @see @funcref{cot}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::cot_, cot, 2)


  template < long N, class T> BOOST_FORCEINLINE T cot(const T & x)
  {
    return cot(boost::mpl::long_<N>(), x);
  }

}

#endif

