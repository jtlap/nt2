//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYP_DERIVATIVES_FUNCTIONS_COTH_HPP_INCLUDED
#define NT2_HYP_DERIVATIVES_FUNCTIONS_COTH_HPP_INCLUDED
#include <nt2/hyperbolic/include/functions/coth.hpp>
#include <nt2/include/functions/simd/coth.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of coth at x
    by coth<N>(x)
    @see @funcref{coth}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::coth_, coth, 2)


  template < long N, class T> BOOST_FORCEINLINE T coth(const T & x)
  {
    return coth(boost::mpl::long_<N>(), x);
  }

}

#endif

