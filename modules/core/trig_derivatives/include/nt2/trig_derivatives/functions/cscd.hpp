//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_CSCD_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_CSCD_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/cscd.hpp>
#include <nt2/include/functions/simd/cscd.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of cscd at x
    by cscd<N>(x)
    @see @funcref{cscd}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::cscd_, cscd, 2)


  template < long N, class T> BOOST_FORCEINLINE T cscd(const T & x)
  {
    return cscd(boost::mpl::long_<N>(), x);
  }

}

#endif

