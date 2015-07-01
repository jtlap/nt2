//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_EXP_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_EXP_HPP_INCLUDED
#include <nt2/exponential/include/functions/exp.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of exp at x
    by exp<N>(x)
    @see @funcref{exp}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::exp_, exp, 2)


  template < long N, class T> BOOST_FORCEINLINE T exp(const T & x)
  {
    return exp(boost::mpl::long_<N>(), x);
  }

}

#endif

