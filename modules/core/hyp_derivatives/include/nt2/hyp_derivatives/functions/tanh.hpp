//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYP_DERIVATIVES_FUNCTIONS_TANH_HPP_INCLUDED
#define NT2_HYP_DERIVATIVES_FUNCTIONS_TANH_HPP_INCLUDED
#include <nt2/hyperbolic/include/functions/tanh.hpp>
#include <nt2/include/functions/simd/tanh.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of tanh at x
    by tanh<N>(x)
    @see @funcref{tanh}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::tanh_, tanh, 2)


  template < long N, class T> BOOST_FORCEINLINE T tanh(const T & x)
  {
    return tanh(boost::mpl::long_<N>(), x);
  }

}

#endif

