//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_ASECD_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_ASECD_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/asecd.hpp>
#include <nt2/include/functions/simd/asecd.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of asecd at x
    by asecd<N>(x)
    @see @funcref{asecd}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::asecd_, asecd, 2)


  template < long N, class T> BOOST_FORCEINLINE T asecd(const T & x)
  {
    return asecd(boost::mpl::long_<N>(), x);
  }

}

#endif

