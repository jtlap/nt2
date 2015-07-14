//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYP_DERIVATIVES_FUNCTIONS_SECH_HPP_INCLUDED
#define NT2_HYP_DERIVATIVES_FUNCTIONS_SECH_HPP_INCLUDED
#include <nt2/hyperbolic/include/functions/sech.hpp>
#include <nt2/include/functions/simd/sech.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of sech at x
    by sech<N>(x)
    @see @funcref{sech}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::sech_, sech, 2)


  template < long N, class T> BOOST_FORCEINLINE T sech(const T & x)
  {
    return sech(boost::mpl::long_<N>(), x);
  }

}

#endif

