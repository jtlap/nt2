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
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_NOT_GREATER_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_NOT_GREATER_EQUAL_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_predicates
 * \defgroup boost_simd_predicates_is_not_greater_equal is_not_greater_equal
 *
 * \par Description
 * Returns True<A0>() if a0 is not greater or equal to a1 else returns False<A0>().
 * \par
 * Due to existence of nan, this is not equivalent to \c not(is_greater_equal(a0,a1))
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/is_not_greater_equal.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg is_nge
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::is_not_greater_equal_(A0,A0)>::type
 *     is_not_greater_equal(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of is_not_greater_equal
 * \param a1 the second parameter of is_not_greater_equal
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

namespace boost { namespace simd
{
  namespace tag
  {         
    /*!
     * \brief Define the tag is_not_greater_equal_ of functor is_not_greater_equal 
     *        in namespace boost::simd::tag for toolbox boost.simd.predicates
    **/
    struct is_not_greater_equal_ : ext::elementwise_<is_not_greater_equal_> { typedef ext::elementwise_<is_not_greater_equal_> parent; };
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_not_greater_equal_, is_not_greater_equal, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_not_greater_equal_, is_nge, 2)
} }

#endif
