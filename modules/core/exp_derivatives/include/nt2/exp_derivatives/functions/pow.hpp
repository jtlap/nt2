//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_POW_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_POW_HPP_INCLUDED
#include <nt2/exponential/include/functions/pow.hpp>
#include <nt2/include/functions/simd/pow.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Ith derivative of pow at x, Jth at yy
    by pow<I, J>(x, y)
    @see @funcref{pow}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::pow_, pow, 4)


  template < long P, long Q, class T, class U>
  BOOST_FORCEINLINE T pow(const T & x, const U & y)
  {
    return pow(boost::mpl::long_<P>(),boost::mpl::long_<Q>(), x, y);
  }

}

#endif

