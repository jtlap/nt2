//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_ACOTD_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_ACOTD_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/acotd.hpp>
#include <nt2/include/functions/simd/acotd.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of acotd at x
    by acotd<N>(x)
    @see @funcref{acotd}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::acotd_, acotd, 2)


  template < long N, class T> BOOST_FORCEINLINE T acotd(const T & x)
  {
    return acotd(boost::mpl::long_<N>(), x);
  }

}

#endif

