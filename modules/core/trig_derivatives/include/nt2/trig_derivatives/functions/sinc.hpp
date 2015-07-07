//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_SINC_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_SINC_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/sinc.hpp>
#include <nt2/include/functions/simd/sinc.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of sinc at x
    by sinc<N>(x)
    @see @funcref{sinc}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::sinc_, sinc, 2)


  template < long N, class T> BOOST_FORCEINLINE T sinc(const T & x)
  {
    return sinc(boost::mpl::long_<N>(), x);
  }

}

#endif

