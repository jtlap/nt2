//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYP_DERIVATIVES_FUNCTIONS_COSH_HPP_INCLUDED
#define NT2_HYP_DERIVATIVES_FUNCTIONS_COSH_HPP_INCLUDED
#include <nt2/hyperbolic/include/functions/cosh.hpp>
#include <nt2/include/functions/simd/cosh.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of cosh at x
    by cosh<N>(x)
    @see @funcref{cosh}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::cosh_, cosh, 2)


  template < long N, class T> BOOST_FORCEINLINE T cosh(const T & x)
  {
    return cosh(boost::mpl::long_<N>(), x);
  }

}

#endif

