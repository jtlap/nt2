//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_EXP2_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_EXP2_HPP_INCLUDED
#include <nt2/exponential/include/functions/expx2.hpp>
#include <nt2/include/functions/simd/expx2.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of expx2 at x
    by expx2<N>(x)
    @see @funcref{expx2}
  **/
//  NT2_FUNCTION_IMPLEMENTATION(tag::expx2_, expx2, 2)


  template < long N, class T> BOOST_FORCEINLINE T expx2(const T & x)
  {
    return expx2(boost::mpl::long_<N>(), x);
  }

}

#endif

