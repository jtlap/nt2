//==============================================================================
//        Copyright 2015   J.T. Lapreste
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIG_DERIVATIVES_FUNCTIONS_ACOS_HPP_INCLUDED
#define NT2_TRIG_DERIVATIVES_FUNCTIONS_ACOS_HPP_INCLUDED
#include <nt2/trigonometric/include/functions/acos.hpp>
#include <nt2/include/functions/simd/acos.hpp>
#include <nt2/include/functor.hpp>


namespace nt2
{
  /*!
    Compute the Nth derivative of acos at x
    by acos<N>(x)
    @see @funcref{acos}
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::acos_, acos, 2)


  template < long N, class T> BOOST_FORCEINLINE T acos(const T & x)
  {
    return acos(boost::mpl::long_<N>(), x);
  }

}

#endif

