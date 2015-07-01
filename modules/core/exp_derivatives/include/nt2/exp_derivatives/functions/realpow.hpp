//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_REALPOW_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_REALPOW_HPP_INCLUDED
#include <nt2/exponential/include/functions/realpow.hpp>
#include <nt2/include/functions/simd/realpow.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of realpow at x
    by realpow<N>(x)
    @see @funcref{realpow}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::realpow_, realpow, 4)


  template < long P, long Q, class T, class U>
  BOOST_FORCEINLINE T realpow(const T & x, const U & y)
  {
    return realpow(boost::mpl::long_<P>(),boost::mpl::long_<Q>(), x, y);
  }

}

#endif

