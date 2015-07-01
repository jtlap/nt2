//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_SQRT1PM1_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_SQRT1PM1_HPP_INCLUDED
#include <nt2/exponential/include/functions/sqrt1pm1.hpp>
#include <nt2/include/functions/simd/sqrt1pm1.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of sqrt1pm1 at x
    by sqrt1pm1<N>(x)
    @see @funcref{sqrt1pm1}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::sqrt1pm1_, sqrt1pm1, 2)


  template < long N, class T> BOOST_FORCEINLINE T sqrt1pm1(const T & x)
  {
    return sqrt1pm1(boost::mpl::long_<N>(), x);
  }

}

#endif

