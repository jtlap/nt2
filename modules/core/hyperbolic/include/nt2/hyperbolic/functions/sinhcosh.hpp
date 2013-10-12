//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#ifndef NT2_HYPERBOLIC_FUNCTIONS_SINHCOSH_HPP_INCLUDED
#define NT2_HYPERBOLIC_FUNCTIONS_SINHCOSH_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
   /*!
     @brief sinhcosh generic tag

     Represents the sinhcosh function in generic contexts.

     @par Models:
        Hierarchy
   **/
    /// @brief Hierarchy tag for sinhcosh function
    struct sinhcosh_ : ext::elementwise_<sinhcosh_>
    {
      typedef ext::elementwise_<sinhcosh_> parent;
    };
  }
  }
  /*!

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 ch, sh
    tie(sh, ch)= sinhcosh(x);
    @endcode

    is similar to:

    @code
    T0 sh = sinh(x);
    T0 ch = cosh(x);
    @endcode

    @see @funcref{cosh}, @funcref{sinh}
    @param a0

    @return a value of the same type as the parameter
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::sinhcosh_, sinhcosh, 1)



   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sinhcosh_, sinhcosh,(A0 const&)(A1&),2)
  /*!

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 ch, sh
    sh = sinhcosh(x, sh, ch);
    @endcode

    is similar to:

    @code
    T0 sh = sinh(x);
    T0 ch = cosh(x);
    @endcode

    @see @funcref{cosh}, @funcref{sinh}
    @param a0

    @return a value of the same type as the parameter
  **/
   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::sinhcosh_, sinhcosh,(A0 const&)(A1&)(A2&),3)
  /*!
    Computes  simultaneously cosh ans sinh
    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 ch, sh
    sinhcosh(x, sh, ch);
    @endcode

    is similar to:

    @code
    T0 sh = sinh(x);
    T0 ch = cosh(x);
    @endcode

    @see @funcref{cosh}, @funcref{sinh}
    @param a0

    @return a value of the same type as the parameter
  **/
    }

#endif

///
