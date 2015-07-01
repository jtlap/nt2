//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_EXP10_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_EXP10_HPP_INCLUDED
#include <nt2/exponential/include/functions/exp10.hpp>
#include <nt2/include/functions/simd/exp10.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of exp10 at x
    by exp10<N>(x)
    @see @funcref{exp10}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::exp10_, exp10, 2)


  template < long N, class T> BOOST_FORCEINLINE T exp10(const T & x)
  {
    return exp10(boost::mpl::long_<N>(), x);
  }

}

#endif

