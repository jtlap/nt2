//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_NOT_GREATER_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_NOT_GREATER_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_predicates
 * \defgroup boost_simd_predicates_is_not_greater is_not_greater
 *
 * \par Description
 * Returns True<result_type>() if a0 is not greater than a1 else returns False<result_type>().
 * \par
 * Due to existence of nan, this is not equivalent to \c not(is_greater(a0,a1))
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/is_not_greater.hpp>
 * \endcode
 *
 * \par Alias
 * \arg is_ngt
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::is_not_greater_(A0,A0)>::type
 *     is_not_greater(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of is_not_greater
 * \param a1 the second parameter of is_not_greater
 *
 * \return an integer value
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

namespace boost { namespace simd { namespace tag
  {
    /*!
     * \brief Define the tag is_not_greater_ of functor is_not_greater
     *        in namespace boost::simd::tag for toolbox boost.simd.predicates
    **/
    struct is_not_greater_ : ext::elementwise_<is_not_greater_> { typedef ext::elementwise_<is_not_greater_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_not_greater_, is_not_greater, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_not_greater_, is_ngt, 2)
} }

#endif
