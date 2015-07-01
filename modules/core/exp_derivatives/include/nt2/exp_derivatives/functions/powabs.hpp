//==============================================================================
//         Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_POWABS_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_POWABS_HPP_INCLUDED
#include <nt2/exponential/include/functions/powabs.hpp>
#include <nt2/include/functions/simd/powabs.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of powabs at x
    by powabs<N>(x)
    @see @funcref{powabs}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::powabs_, powabs, 4)


  template < long P, long Q, class T, class U>
  BOOST_FORCEINLINE T powabs(const T & x, const U & y)
  {
    return powabs(boost::mpl::long_<P>(),boost::mpl::long_<Q>(), x, y);
  }

}

#endif

