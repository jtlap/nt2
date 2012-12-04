//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_LOGICAL_OR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_LOGICAL_OR_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>

/*!
 * \ingroup boost_simd_operator
 * \defgroup boost_simd_operator_logical_or logical_or
 *
 * \par Description
 * return the logical or of the two parameters
 * the operands must of the same type
 * the result type is the common one or bool in scalar case
 * Infix notation can be used with operator '||'
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/logical_or.hpp>
 * \endcode
 *
 * \par Alias
 * \arg l_or
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::logical_or_(A0,A0)>::type
 *     logical_or(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of logical_or
 * \param a1 the second parameter of logical_or
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

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
     * \brief Define the tag logical_or_ of functor logical_or
     *        in namespace boost::simd::tag for toolbox boost.simd.operator
    **/
    struct logical_or_ : ext::elementwise_<logical_or_> { typedef ext::elementwise_<logical_or_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::logical_or_      , logical_or     , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::logical_or_      , l_or           , 2 )
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::logical_or>
  {
    typedef boost::simd::tag::logical_or_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::logical_or_>
  {
    typedef boost::proto::tag::logical_or type;
  };
} } }

#include <boost/simd/toolbox/operator/specific/common.hpp>

#endif
