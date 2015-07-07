//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_CSC_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_CSC_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/csc.hpp>
#include <nt2/include/functions/simd/csc.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of csc at x
    by csc<N>(x)
    @see @funcref{csc}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::csc_, csc, 2)


  template < long N, class T> BOOST_FORCEINLINE T csc(const T & x)
  {
    return csc(boost::mpl::long_<N>(), x);
  }

}

#endif

