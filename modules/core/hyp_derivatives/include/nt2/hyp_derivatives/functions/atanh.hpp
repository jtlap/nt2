//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYP_DERIVATIVES_FUNCTIONS_ATANH_HPP_INCLUDED
#define NT2_HYP_DERIVATIVES_FUNCTIONS_ATANH_HPP_INCLUDED
#include <nt2/hyperbolic/include/functions/atanh.hpp>
#include <nt2/include/functions/simd/atanh.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of atanh at x
    by atanh<N>(x)
    @see @funcref{atanh}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::atanh_, atanh, 2)


  template < long N, class T> BOOST_FORCEINLINE T atanh(const T & x)
  {
    return atanh(boost::mpl::long_<N>(), x);
  }

}

#endif

