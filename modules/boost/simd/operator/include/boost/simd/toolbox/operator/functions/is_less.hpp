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
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_IS_LESS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_IS_LESS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_operator
 * \defgroup boost_simd_operator_is_less is_less
 *
 * \par Description
 * Returns True<result_type>() or False<result_type>() according a0 is less than a1 or not.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/is_less.hpp>
 * \endcode
 *
 * \par Alias
 * \arg lt
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::is_less_(A0,A0)>::type
 *     is_less(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of is_less
 * \param a1 the second parameter of is_less
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
     * \brief Define the tag is_less_ of functor is_less
     *        in namespace boost::simd::tag for toolbox boost.simd.operator
    **/
    struct is_less_ : ext::elementwise_<is_less_> { typedef ext::elementwise_<is_less_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_less_, is_less , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_less_, lt      , 2 )
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::less>
  {
    typedef boost::simd::tag::is_less_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::is_less_>
  {
    typedef boost::proto::tag::less type;
  };
} } }

#include <boost/simd/toolbox/operator/specific/common.hpp>

#endif
