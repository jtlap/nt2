//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_HYP_DERIVATIVES_FUNCTIONS_SINHC_HPP_INCLUDED
#define NT2_HYP_DERIVATIVES_FUNCTIONS_SINHC_HPP_INCLUDED
#include <nt2/hyperbolic/include/functions/sinhc.hpp>
#include <nt2/include/functions/simd/sinhc.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of sinhc at x
    by sinhc<N>(x)
    @see @funcref{sinhc}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::sinhc_, sinhc, 2)


  template < long N, class T> BOOST_FORCEINLINE T sinhc(const T & x)
  {
    return sinhc(boost::mpl::long_<N>(), x);
  }

}

#endif

