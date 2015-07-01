//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_LOG2_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_LOG2_HPP_INCLUDED
#include <nt2/exponential/include/functions/log2.hpp>
#include <nt2/include/functions/simd/log2.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of log2 at x
    by log2<N>(x)
    @see @funcref{log2}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::log2_, log2, 2)


  template < long N, class T> BOOST_FORCEINLINE T log2(const T & x)
  {
    return log2(boost::mpl::long_<N>(), x);
  }

}

#endif

