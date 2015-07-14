//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYP_DERIVATIVES_FUNCTIONS_ASECH_HPP_INCLUDED
#define NT2_HYP_DERIVATIVES_FUNCTIONS_ASECH_HPP_INCLUDED
#include <nt2/hyperbolic/include/functions/asech.hpp>
#include <nt2/include/functions/simd/asech.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of asech at x
    by asech<N>(x)
    @see @funcref{asech}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::asech_, asech, 2)


  template < long N, class T> BOOST_FORCEINLINE T asech(const T & x)
  {
    return asech(boost::mpl::long_<N>(), x);
  }

}

#endif

