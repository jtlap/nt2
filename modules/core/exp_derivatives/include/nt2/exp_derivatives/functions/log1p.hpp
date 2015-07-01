//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_LOG1P_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_LOG1P_HPP_INCLUDED
#include <nt2/exponential/include/functions/log1p.hpp>
#include <nt2/include/functions/simd/log1p.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of log1p at x
    by log1p<N>(x)
    @see @funcref{log1p}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::log1p_, log1p, 2)


  template < long N, class T> BOOST_FORCEINLINE T log1p(const T & x)
  {
    return log1p(boost::mpl::long_<N>(), x);
  }

}

#endif

