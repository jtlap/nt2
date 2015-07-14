//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYP_DERIVATIVES_FUNCTIONS_ACSCH_HPP_INCLUDED
#define NT2_HYP_DERIVATIVES_FUNCTIONS_ACSCH_HPP_INCLUDED
#include <nt2/hyperbolic/include/functions/acsch.hpp>
#include <nt2/include/functions/simd/acsch.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of acsch at x
    by acsch<N>(x)
    @see @funcref{acsch}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::acsch_, acsch, 2)


  template < long N, class T> BOOST_FORCEINLINE T acsch(const T & x)
  {
    return acsch(boost::mpl::long_<N>(), x);
  }

}

#endif

