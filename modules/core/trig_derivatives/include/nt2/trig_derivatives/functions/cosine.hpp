//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_COSINE_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_COSINE_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/cosine.hpp>
#include <nt2/include/functions/simd/cosine.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of cosine at x
    by cosine<mode, N>(x)
    @see @funcref{cosine}
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::cosine_<A0>, cosine,  (A1 const&)(A2 const&), 3)


  template < class mode,  long N, class T> BOOST_FORCEINLINE T cosine(const T & x)
  {
    return cosine<mode>(boost::mpl::long_<N>(), x);
  }

}

#endif

