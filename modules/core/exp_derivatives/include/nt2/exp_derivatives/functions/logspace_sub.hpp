//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_LOGSPACE_SUB_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_LOGSPACE_SUB_HPP_INCLUDED
#include <nt2/exponential/include/functions/logspace_sub.hpp>
#include <nt2/include/functions/simd/logspace_sub.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Ith derivative  at x, Jth at yy of logspace_sub
    by pow<I, J>(x, y) with I+J less or equal to 2
    @see @funcref{logspace_sub}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::logspace_sub_, logspace_sub, 4)


  template < long P, long Q, class T, class U>
  BOOST_FORCEINLINE T logspace_sub(const T & x, const U & y)
  {
    return logspace_sub(boost::mpl::long_<P>(),boost::mpl::long_<Q>(), x, y);
  }

}

#endif

