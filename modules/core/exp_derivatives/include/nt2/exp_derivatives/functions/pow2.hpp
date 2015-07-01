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
#include <nt2/exponential/include/functions/pow2.hpp>
#include <nt2/include/functions/simd/pow2.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of pow2 at x
    by pow2<N>(x)
    @see @funcref{pow2}
  **/
//  NT2_FUNCTION_IMPLEMENTATION(tag::pow2_, pow2, 2)


  template < long N, class T> BOOST_FORCEINLINE T pow2(const T & x)
  {
    return pow2(boost::mpl::long_<N>(), x);
  }

}

#endif

