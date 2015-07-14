//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYP_DERIVATIVES_FUNCTIONS_CSCH_HPP_INCLUDED
#define NT2_HYP_DERIVATIVES_FUNCTIONS_CSCH_HPP_INCLUDED
#include <nt2/hyperbolic/include/functions/csch.hpp>
#include <nt2/include/functions/simd/csch.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of csch at x
    by csch<N>(x)
    @see @funcref{csch}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::csch_, csch, 2)


  template < long N, class T> BOOST_FORCEINLINE T csch(const T & x)
  {
    return csch(boost::mpl::long_<N>(), x);
  }

}

#endif

