//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYP_DERIVATIVES_FUNCTIONS_SINH_HPP_INCLUDED
#define NT2_HYP_DERIVATIVES_FUNCTIONS_SINH_HPP_INCLUDED
#include <nt2/hyperbolic/include/functions/sinh.hpp>
#include <nt2/include/functions/simd/sinh.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of sinh at x
    by sinh<N>(x)
    @see @funcref{sinh}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::sinh_, sinh, 2)


  template < long N, class T> BOOST_FORCEINLINE T sinh(const T & x)
  {
    return sinh(boost::mpl::long_<N>(), x);
  }

}

#endif

