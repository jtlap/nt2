//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
  @file
  @brief Definition of rem_pio2_medium function
**/

#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_REM_PIO2_MEDIUM_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_REM_PIO2_MEDIUM_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
    /// @brief Hierarchy tag for rem_pio2_medium function
    struct rem_pio2_medium_ : ext::elementwise_<rem_pio2_medium_>
    {
      typedef ext::elementwise_<rem_pio2_medium_> parent;
    };
  }
  /*!
    @brief rem_pio2_medium

    @c rem_pio2_medium compute the remainder modulo \f$\pi/2\f$ with medium algorithm,
    and return the angle quadrant between 0 and 3.
    This function is mainly for internal reduction purposes
    This is a medium_ version version accurate if the input is in:
    \arg \f$[-2^6\pi,2^6\pi\f$ for float,
    \arg \f$[-2^18\pi,2^18\pi\f$ for double.
    \par
    The reduction of the argument modulo \f$pi/2\f$ is generally
    the most difficult part of trigonometric evaluations.
    The accurate algorithm is over costly and implies the knowledge
    of a few hundred \f$pi\f$ decimals
    some simpler algorithms as this one
    can be used, but the precision is only insured on smaller intervals.

    @param a0 angle in radian

    @return the integer value of the quadrant
  **/

   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::rem_pio2_medium_, rem_pio2_medium,(A0 const&),1)

  /*!
    @brief  rem_pio2_medium

    @c rem_pio2_medium compute the remainder modulo \f$\pi/2\f$ with medium algorithm,
    and the angle quadrant between 0 and 3.
    This is a medium_ version version accurate if the input is in:
    \arg \f$[-2^6\pi,2^6\pi\f$ for float,
    \arg \f$[-2^18\pi,2^18\pi\f$ for double.
    \par
    The reduction of the argument modulo \f$pi/2\f$ is generally
    the most difficult part of trigonometric evaluations.
    The accurate algorithm is over costly and implies the knowledge
    of a few hundred \f$pi\f$ decimals
    some simpler algorithms as this one
    can be used, but the precision is only insured on smaller intervals.

    @param a0 angle in radian
    @param a1 L-Value that will receive the remainder modulo \f$\pi/2\f$ off @c a0

    @return A pair containing the remainder and quadrant  of @c a0
  **/
   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::rem_pio2_medium_, rem_pio2_medium,(A0 const&)(A0&),1)

  /*!
    @brief  rem_pio2_medium

    @c rem_pio2_medium compute the remainder modulo \f$\pi/2\f$ with medium algorithm,
    and the angle quadrant between 0 and 3.
    This is a medium_ version version accurate if the input is in:
    \arg \f$[-2^6\pi,2^6\pi\f$ for float,
    \arg \f$[-2^18\pi,2^18\pi\f$ for double.
    \par
    The reduction of the argument modulo \f$pi/2\f$ is generally
    the most difficult part of trigonometric evaluations.
    The accurate algorithm is over costly and implies the knowledge
    of a few hundred \f$pi\f$ decimals
    some simpler algorithms as this one
    can be used, but the precision is only insured on smaller intervals.

    @param a0 angle in radian
    @param a1 L-Value that will receive the quadrant off @c a0
    @param a2 L-Value that will receive the remainder modulo \f$\pi/2\f$ off @c a0

  **/
   NT2_FUNCTION_IMPLEMENTATION_TPL(tag::rem_pio2_medium_, rem_pio2_medium,(A0 const&)(A1&)(A0&),2)

    }

#endif

