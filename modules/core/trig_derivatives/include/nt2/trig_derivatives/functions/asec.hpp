//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_ASEC_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_ASEC_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/asec.hpp>
#include <nt2/include/functions/simd/asec.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of asec at x
    by asec<N>(x)
    @see @funcref{asec}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::asec_, asec, 2)


  template < long N, class T> BOOST_FORCEINLINE T asec(const T & x)
  {
    return asec(boost::mpl::long_<N>(), x);
  }

}

#endif

