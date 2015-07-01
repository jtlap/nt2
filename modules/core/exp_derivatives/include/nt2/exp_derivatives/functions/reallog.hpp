//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_REALLOG_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_REALLOG_HPP_INCLUDED
#include <nt2/exponential/include/functions/reallog.hpp>
#include <nt2/include/functions/simd/reallog.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of reallog at x
    by reallog<N>()
    @see @funcref{reallog}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::reallog_, reallog, 2)


  template < long N, class T> BOOST_FORCEINLINE T reallog(const T & x)
  {
    return reallog(boost::mpl::long_<N>(), x);
  }

}

#endif

