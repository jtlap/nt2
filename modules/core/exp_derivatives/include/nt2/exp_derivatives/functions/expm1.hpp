//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_EXPM1_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_EXPM1_HPP_INCLUDED
#include <nt2/exponential/include/functions/expm1.hpp>
#include <nt2/include/functions/simd/expm1.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of expm1 at x
    by expm1<N>(x)
    @see @funcref{expm1}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::expm1_, expm1, 2)


  template < long N, class T> BOOST_FORCEINLINE T expm1(const T & x)
  {
    return expm1(boost::mpl::long_<N>(), x);
  }

}

#endif

