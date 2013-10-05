//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_ATAN2_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_ATAN2_HPP_INCLUDED
#include <nt2/include/functor.hpp>


namespace nt2 { namespace tag
  {
   /*!
     @brief atan2 generic tag

     Represents the atan2 function in generic contexts.

     @par Models:
        Hierarchy
   **/
    struct atan2_ : ext::elementwise_<atan2_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<atan2_> parent;
    };
  }
  /*!
    atan2 function.
    The two-argument function atan2 is a variation of the arctangent function.

    For any real arguments \f$a_0\f$ and \f$a_1\f$ not both equal to zero, atan2(a0, a1)
    is the angle in radians between the positive x-axis of a plane and the point
    given by the coordinates \f$(a_1, a_0)\f$ on it.

    It is the angle in \f$[-\pi,\pi[ \f$ such that
    \f$a1/\sqrt{a_0^2+a_1^2}\f$ and \f$a0/\sqrt{a_0^2+a_1^2}\f$
    are respectively the sine and the cosine.

    @par Semantic:

    For every parameters of floating types respectively T0, T1:

    @code
    T0 r = atan2(a0,a1);
    @endcode

    is similar but not fully defined by:

    @code
    T0 r =  atan(a1/a0);;
    @endcode

    as it is quadrant aware.

    @param a0

    @param a1

    @return a value of the same type as the parameters
  **/
  NT2_FUNCTION_IMPLEMENTATION(tag::atan2_, atan2, 2)
}

#endif

// modified by jt the 25/12/2010

///
