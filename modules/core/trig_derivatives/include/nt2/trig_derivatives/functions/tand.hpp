//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_TAND_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_TAND_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/tand.hpp>
#include <nt2/include/functions/simd/tand.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of tand at x
    by tand<N>(x)
    @see @funcref{tand}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::tand_, tand, 2)


  template < long N, class T> BOOST_FORCEINLINE T tand(const T & x)
  {
    return tand(boost::mpl::long_<N>(), x);
  }

}

#endif

