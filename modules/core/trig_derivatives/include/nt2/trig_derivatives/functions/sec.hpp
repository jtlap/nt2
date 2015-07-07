//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_SEC_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_SEC_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/sec.hpp>
#include <nt2/include/functions/simd/sec.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of sec at x
    by sec<N>(x)
    @see @funcref{sec}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::sec_, sec, 2)


  template < long N, class T> BOOST_FORCEINLINE T sec(const T & x)
  {
    return sec(boost::mpl::long_<N>(), x);
  }

}

#endif

