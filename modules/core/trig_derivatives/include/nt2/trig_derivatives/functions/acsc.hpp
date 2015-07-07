//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_ACSC_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_ACSC_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/acsc.hpp>
#include <nt2/include/functions/simd/acsc.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of acsc at x
    by acsc<N>(x)
    @see @funcref{acsc}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::acsc_, acsc, 2)


  template < long N, class T> BOOST_FORCEINLINE T acsc(const T & x)
  {
    return acsc(boost::mpl::long_<N>(), x);
  }

}

#endif

