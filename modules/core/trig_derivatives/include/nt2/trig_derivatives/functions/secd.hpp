//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_SECD_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_SECD_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/secd.hpp>
#include <nt2/include/functions/simd/secd.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of secd at x
    by secd<N>(x)
    @see @funcref{secd}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::secd_, secd, 2)


  template < long N, class T> BOOST_FORCEINLINE T secd(const T & x)
  {
    return secd(boost::mpl::long_<N>(), x);
  }

}

#endif

