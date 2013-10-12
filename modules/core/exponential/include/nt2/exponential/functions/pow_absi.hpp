//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_POW_ABSI_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_POW_ABSI_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief pow_absi generic tag

     Represents the pow_absi function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct pow_absi_ : ext::elementwise_<pow_absi_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<pow_absi_> parent;
    };
  }
  /*!
    Power function for scalar integer a1: \f${a_0}^{\|a_1\|}\f$. (\f$0^0\f$ returns 1)

    @par Semantic:

    For every parameters of floating types respectively T0, T1:

    @code
    T0 r = pow_absi(x,y);
    @endcode

    is similar to:

    @code
    T0 r =  pow_absi(x,abs(y));;
    @endcode

    @param a0

    @param a1

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::pow_absi_, pow_absi, 2)
}

#endif

