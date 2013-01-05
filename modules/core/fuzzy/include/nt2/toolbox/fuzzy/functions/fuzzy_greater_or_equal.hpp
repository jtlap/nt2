//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
/*!
 * \file
**/
#ifndef NT2_TOOLBOX_FUZZY_FUNCTIONS_FUZZY_GREATER_OR_EQUAL_HPP_INCLUDED
#define NT2_TOOLBOX_FUZZY_FUNCTIONS_FUZZY_GREATER_OR_EQUAL_HPP_INCLUDED
#include <nt2/include/functor.hpp>
#include <nt2/include/functor.hpp>

/*!
 * \ingroup fuzzy
 * \defgroup fuzzy_fuzzy_greater_or_equal fuzzy_greater_or_equal
 *
 * \par Description
 * \f$a_0 \ge a_1-a_2*\max(|a_0|,|a1|)\f$
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/fuzzy_greater_or_equal.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::fuzzy_greater_or_equal_(A0,A0,A0)>::type
 *     fuzzy_greater_or_equal(const A0 & a0,const A0 & a1,const A0 & a2);
 * }
 * \endcode
 *
 * \param a0 the first parameter of fuzzy_greater_or_equal
 * \param a1 the second parameter of fuzzy_greater_or_equal
 * \param a2 the third parameter of fuzzy_greater_or_equal
 *
 * \return a value of the common type of the parameters
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 * This is a predicate operation. Such operations return bool in scalar mode,
 * but not in SIMD mode.
 * \par
 * The return type in SIMD mode is the common type of the parameters and is
 * a 'signed boolean' type. This means that in this case True has all its bits
 * sets to one. This is to facilitate masking operations. You are invited to
 * consult the rationale.
 *
**/

namespace nt2 { namespace tag
  {
    /*!
     * \brief Define the tag fuzzy_greater_or_equal_ of functor fuzzy_greater_or_equal
     *        in namespace nt2::tag for toolbox fuzzy
    **/
    struct fuzzy_greater_or_equal_ : ext::elementwise_<fuzzy_greater_or_equal_> { typedef ext::elementwise_<fuzzy_greater_or_equal_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::fuzzy_greater_or_equal_, fuzzy_greater_or_equal, 3)
}

#endif

// modified by jt the 25/12/2010
