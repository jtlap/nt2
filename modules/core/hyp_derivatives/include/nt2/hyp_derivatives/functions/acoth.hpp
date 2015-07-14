//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYP_DERIVATIVES_FUNCTIONS_ACOTH_HPP_INCLUDED
#define NT2_HYP_DERIVATIVES_FUNCTIONS_ACOTH_HPP_INCLUDED
#include <nt2/hyperbolic/include/functions/acoth.hpp>
#include <nt2/include/functions/simd/acoth.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of acoth at x
    by acoth<N>(x)
    @see @funcref{acoth}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::acoth_, acoth, 2)


  template < long N, class T> BOOST_FORCEINLINE T acoth(const T & x)
  {
    return acoth(boost::mpl::long_<N>(), x);
  }

}

#endif

