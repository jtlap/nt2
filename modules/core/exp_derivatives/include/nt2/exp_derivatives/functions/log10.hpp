//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_LOG10_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_LOG10_HPP_INCLUDED
#include <nt2/exponential/include/functions/log10.hpp>
#include <nt2/include/functions/simd/log10.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of log10 at x
    by log10<N>(x)
    @see @funcref{log10}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::log10_, log10, 2)


  template < long N, class T> BOOST_FORCEINLINE T log10(const T & x)
  {
    return log10(boost::mpl::long_<N>(), x);
  }

}

#endif

