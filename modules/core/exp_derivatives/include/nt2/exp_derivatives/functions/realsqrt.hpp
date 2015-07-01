//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_EXP2_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_EXP2_HPP_INCLUDED
#include <nt2/exponential/include/functions/realsqrt.hpp>
#include <nt2/include/functions/simd/realsqrt.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of realsqrt at x
    by realsqrt<N>(x)
    @see @funcref{realsqrt}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::realsqrt_, realsqrt, 2)


  template < long N, class T> BOOST_FORCEINLINE T realsqrt(const T & x)
  {
    return realsqrt(boost::mpl::long_<N>(), x);
  }

}

#endif

