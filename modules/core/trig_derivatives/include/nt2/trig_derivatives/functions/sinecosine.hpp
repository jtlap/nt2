//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_SINECOSINE_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_SINECOSINE_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/sinecosine.hpp>
#include <nt2/include/functions/simd/sinecosine.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of sinecosine at x
    by sinecosine<N>(x)
    @see @funcref{sinecosine}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::sinecosine_, sinecosine, 2)


  template < long N, class T> BOOST_FORCEINLINE T sinecosine(const T & x)
  {
    return sinecosine(boost::mpl::long_<N>(), x);
  }

}

#endif

