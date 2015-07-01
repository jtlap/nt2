//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_CBRT_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_CBRT_HPP_INCLUDED
#include <nt2/exponential/include/functions/cbrt.hpp>
#include <nt2/include/functions/simd/cbrt.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of cbrt at x
    by cbrt<N>(x)
    @see @funcref{cbrt}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::cbrt_, cbrt, 2)


  template < long N, class T> BOOST_FORCEINLINE T cbrt(const T & x)
  {
    return cbrt(boost::mpl::long_<N>(), x);
  }

}

#endif

