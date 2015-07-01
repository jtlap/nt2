//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_LOG_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_LOG_HPP_INCLUDED
#include <nt2/exponential/include/functions/log.hpp>
#include <nt2/include/functions/simd/log.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of log at x
    by log<N>(x)
    @see @funcref{log}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::log_, log, 2)


  template < long N, class T> BOOST_FORCEINLINE T log(const T & x)
  {
    return log(boost::mpl::long_<N>(), x);
  }

}

#endif

