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
#ifndef NT2_TOOLBOX_FUZZY_FUNCTIONS_FUZZY_DEFINITELY_LESS_HPP_INCLUDED
#define NT2_TOOLBOX_FUZZY_FUNCTIONS_FUZZY_DEFINITELY_LESS_HPP_INCLUDED
#include <nt2/include/functor.hpp>

/*!
 * \ingroup fuzzy
 * \defgroup fuzzy_fuzzy_definitely_less fuzzy_definitely_less
 *
 * \par Description
 * a_0 \lt a_1-a_2*\max(|a_0|,|a1|)
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/fuzzy_definitely_less.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace nt2
 * {
 *   template <class A0>
 *     meta::call<tag::fuzzy_definitely_less_(A0,A0,A0)>::type
 *     fuzzy_definitely_less(const A0 & a0,const A0 & a1,const A0 & a2);
 * }
 * \endcode
 *
 * \param a0 the first parameter of fuzzy_definitely_less
 * \param a1 the second parameter of fuzzy_definitely_less
 * \param a2 the third parameter of fuzzy_definitely_less
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
     * \brief Define the tag fuzzy_definitely_less_ of functor fuzzy_definitely_less
     *        in namespace nt2::tag for toolbox fuzzy
    **/
    struct fuzzy_definitely_less_ : ext::elementwise_<fuzzy_definitely_less_> { typedef ext::elementwise_<fuzzy_definitely_less_> parent; };
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::fuzzy_definitely_less_, fuzzy_definitely_less, 3)
}

#endif

// modified by jt the 25/12/2010
