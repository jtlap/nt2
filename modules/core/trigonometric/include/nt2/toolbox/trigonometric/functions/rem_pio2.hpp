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
  @brief Definition of rem_pio2 function
**/

#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_REM_PIO2_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTIONS_REM_PIO2_HPP_INCLUDED
#include <nt2/include/functor.hpp>

namespace nt2 { namespace tag
  {
    /// @brief Hierarchy tag for rem_pio2 function
    struct rem_pio2_ : ext::elementwise_<rem_pio2_>
    {
      typedef ext::elementwise_<rem_pio2_> parent;
    };
  }
  /*!
    @brief rem_pio2

    @c rem_pio2 compute the remainder modulo \f$\pi/2\f$ with cephes algorthm,
    and return the angle quadrant between 0 and 3.
    This is the always accurate super costly version.
    This function is mainly for internal purposes
    \par
    The reduction of the argument modulo \f$pi/2\f$ is generally
    the most difficult part of trigonometric evaluations.
    The accurate algorithm is over costly and implies the knowledge
    of a few hundred \f$pi\f$ decimals
    some simpler algorithms
    can be used, but the precision is only insured on smaller intervals.

    @param a0 angle in radian

    @return the fusion vector : integer value of the quadrant,
     reduced angle and eventual coorection
  **/

  NT2_FUNCTION_IMPLEMENTATION_TPL(tag::rem_pio2_, rem_pio2,(A0 const&),1)

  /*!
    @brief  rem_pio2

    @c rem_pio2 compute the remainder modulo \f$\pi/2\f$ with cephes algorthm,
    and the angle quadrant between 0 and 3.
    This is the always accurate super costly version.
    This function is mainly for internal purposes
    \par
    The reduction of the argument modulo \f$pi/2\f$ is generally
    the most difficult part of trigonometric evaluations.
    The accurate algorithm is over costly and implies the knowledge
    of a few hundred \f$pi\f$ decimals
    some simpler algorithms
    can be used, but the precision is only insured on smaller intervals.

    @param a0 angle in radian
    @param a1 L-Value that will receive the remainder modulo \f$\pi/2\f$ of @c a0

    @return A pair containing the remainder and quadrant  of @c a0
  **/
    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::rem_pio2_, rem_pio2,(A0 const&)(A0&),1)

  /*!
    @brief  rem_pio2

    @c rem_pio2 compute the remainder modulo \f$\pi/2\f$ with cephes algorthm,
    and the angle quadrant between 0 and 3.
    This is the always accurate super costly version.
    This function is mainly for internal purposes
    \par
    The reduction of the argument modulo \f$pi/2\f$ is generally
    the most difficult part of trigonometric evaluations.
    The accurate algorithm is over costly and implies the knowledge
    of a few hundred \f$pi\f$ decimals
    some simpler algorithms
    can be used, but the precision is only insured on smaller intervals.

    @param a0 angle in radian
    @param a1 L-Value that will receive the quadrant off @c a0
    @param a2 L-Value that will receive the remainder modulo \f$\pi/2\f$ of @c a0

  **/
    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::rem_pio2_, rem_pio2,(A0 const&)(A1&)(A0&),2)


  /*!
    @brief  rem_pio2

    @c rem_pio2 compute the remainder modulo \f$\pi/2\f$ with cephes algorthm,
    and the angle quadrant between 0 and 3.
    This is the always accurate super costly version.
    This function is mainly for internal purposes
    \par
    The reduction of the argument modulo \f$pi/2\f$ is generally
    the most difficult part of trigonometric evaluations.
    The accurate algorithm is over costly and implies the knowledge
    of a few hundred \f$pi\f$ decimals
    some simpler algorithms
    can be used, but the precision is only insured on smaller intervals.

    @param a0 angle in radian
    @param a1 L-Value that will receive the quadrant off @c a0
    @param a2 L-Value that will receive the remainder modulo \f$\pi/2\f$ of @c a0
    @param a3 L-Value that will receive the remainder correction

  **/

    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::rem_pio2_, rem_pio2,(A0 const&)(A1&)(A0&)(A0&),2)

  /*!
    @brief  rem_pio2

    @c rem_pio2 compute the remainder modulo \f$\pi/2\f$ with cephes algorthm,
    and the angle quadrant between 0 and 3.
    This is the always accurate super costly version.
    This function is mainly for internal purposes
    \par
    The reduction of the argument modulo \f$pi/2\f$ is generally
    the most difficult part of trigonometric evaluations.
    The accurate algorithm is over costly and implies the knowledge
    of a few hundred \f$pi\f$ decimals
    some simpler algorithms
    can be used, but the precision is only insured on smaller intervals.

    @param a0 angle in radian
    @param a1 L-Value that will receive the quadrant off @c a0
    @param a2 L-Value that will receive the remainder modulo \f$\pi/2\f$ of @c a0
    @param a3 Computation target indicating statically if the angles passed are
    very_small_, small_, medium_, big_, information that allow to choose
    among rem_pio2_straight,  rem_pio2_cephes,  rem_pio2_medium, and full rem_pio2
    routines of computation

  **/

    NT2_FUNCTION_IMPLEMENTATION_TPL(tag::rem_pio2_, rem_pio2,(A0 const&)(A0&)(const A1&),2)

 }

#endif



