//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_ASIND_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_ASIND_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/asind.hpp>
#include <nt2/include/functions/simd/asind.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of asind at x
    by asind<N>(x)
    @see @funcref{asind}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::asind_, asind, 2)


  template < long N, class T> BOOST_FORCEINLINE T asind(const T & x)
  {
    return asind(boost::mpl::long_<N>(), x);
  }

}

#endif

