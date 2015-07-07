//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_TANGENT_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_TANGENT_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/tangent.hpp>
#include <nt2/include/functions/simd/tangent.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of tangent at x
    by tangent<mode, N>(x)
    @see @funcref{tangent}
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::tangent_<A0>, tangent,  (A1 const&)(A2 const&), 3)


  template < class mode,  long N, class T> BOOST_FORCEINLINE T tangent(const T & x)
  {
    return tangent<mode>(boost::mpl::long_<N>(), x);
  }

}

#endif

