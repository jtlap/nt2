//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_COSECANT_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_COSECANT_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/cosecant.hpp>
#include <nt2/include/functions/simd/cosecant.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of cosecant at x
    by cosecant<mode, N>(x)
    @see @funcref{cosecant}
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::cosecant_<A0>, cosecant,  (A1 const&)(A2 const&), 3)


  template < class mode, long N, class T> BOOST_FORCEINLINE T cosecant(const T & x)
  {
    return cosecant<mode>(boost::mpl::long_<N>(), x);
  }

}

#endif

