//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_GLOBAL_SUM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_GLOBAL_SUM_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::global_sum function
 */

#include <nt2/include/functor.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/sdk/meta/reduction_hierarchy.hpp>

namespace nt2
{
  namespace tag
  {
    //==========================================================================
    // global_sum_ is plus_ all over the data, starting with Zero
    //==========================================================================
    struct  global_sum_
          : ext::global_reduction_<global_sum_, tag::plus_, tag::Zero>
    {
      typedef ext::global_reduction_<global_sum_, tag::plus_, tag::Zero> parent;
    };
  }

  //============================================================================
  /*!
   * Compute global sum of an expresion
   *
   * \param xpr Expression to compute the global sum
   * \return a scalar-like value corresponding of the global sum of \c xpr
   */
  //============================================================================
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::global_sum_, global_sum, 1)
}

#endif
