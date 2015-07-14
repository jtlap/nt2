//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYP_DERIVATIVES_FUNCTIONS_ACOSH_HPP_INCLUDED
#define NT2_HYP_DERIVATIVES_FUNCTIONS_ACOSH_HPP_INCLUDED
#include <nt2/hyperbolic/include/functions/acosh.hpp>
#include <nt2/include/functions/simd/acosh.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of acosh at x
    by acosh<N>(x)
    @see @funcref{acosh}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::acosh_, acosh, 2)


  template < long N, class T> BOOST_FORCEINLINE T acosh(const T & x)
  {
    return acosh(boost::mpl::long_<N>(), x);
  }

}

#endif

