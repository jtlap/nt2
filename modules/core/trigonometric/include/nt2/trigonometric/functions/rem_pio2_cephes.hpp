//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TRIGONOMETRIC_FUNCTIONS_REM_PIO2_CEPHES_HPP_INCLUDED
#define NT2_TRIGONOMETRIC_FUNCTIONS_REM_PIO2_CEPHES_HPP_INCLUDED

/*!
  @file
  @brief Definition of rem_pio2_cephes function
**/

#include <nt2/include/functor.hpp>

namespace nt2
{
  namespace tag
  {
    /// @brief Hierarchy tag for rem_pio2_cephes function
    struct rem_pio2_cephes_ : ext::elementwise_<rem_pio2_cephes_>
    {
      typedef ext::elementwise_<rem_pio2_cephes_> parent;
    };
  }
  /*!
    @brief rem_pio2_cephes

    @c rem_pio2_cephes compute the remainder modulo \f$\pi/2\f$ with cephes algorthm,
    and return the angle quadrant between 0 and 3.
    This is a quick version accurate if the input is in \f$[-20\pi,20\pi\f$.

    @param a0 angle in radian

    @return the integer value of the quadrant
  **/

  NT2_FUNCTION_IMPLEMENTATION_TPL ( tag::rem_pio2_cephes_
                                  , rem_pio2_cephes,(A0 const&)
                                  , 1
                                  )

  /*!
    @brief  rem_pio2_cephes

    @c rem_pio2_cephes compute the remainder modulo \f$\pi/2\f$ with cephes algorthm,
    and the angle quadrant between 0 and 3.
    This is a quick version accurate if the input is in \f$[-20\pi,20\pi\f$.

    @param a0 angle in radian
    @param a1 L-Value that will receive the remainder modulo \f$\pi/2\f$ off @c a0

    @return A pair containing the remainder and quadrant  of @c a0
  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL ( tag::rem_pio2_cephes_
                                  , rem_pio2_cephes
                                  , (A0 const&)(A0&)
                                  , 1
                                  )

  /*!
    @brief  rem_pio2_cephes

    @c rem_pio2_cephes compute the remainder modulo \f$\pi/2\f$ with cephes algorthm,
    and the angle quadrant between 0 and 3.
    This is a quick version accurate if the input is in \f$[-20\pi,20\pi\f$.

    @param a0 angle in radian
    @param a1 L-Value that will receive the quadrant off @c a0
    @param a2 L-Value that will receive the remainder modulo \f$\pi/2\f$ off @c a0

  **/
  NT2_FUNCTION_IMPLEMENTATION_TPL ( tag::rem_pio2_cephes_
                                  , rem_pio2_cephes
                                  , (A0 const&)(A1&)(A0&)
                                  , 2
                                  )
}

#endif
