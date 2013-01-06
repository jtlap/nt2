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
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_UNARY_PLUS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_UNARY_PLUS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>

/*!
 * \ingroup boost_simd_operator
 * \defgroup boost_simd_operator_unary_plus unary_plus
 *
 * \par Description
 * return the elementwise unary plus of the parameter
 * Infix notation can be used with operator '+'
 * This is in fact identity.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/unary_plus.hpp>
 * \endcode
 *
 * \par Aliases
 * \arg identity
 * \arg id
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::unary_plus_(A0)>::type
 *     unary_plus(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of unary_plus
 *
 * \return a value of the same type as the parameter
 *
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 *
**/

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
     * \brief Define the tag unary_plus_ of functor unary_plus
     *        in namespace boost::simd::tag for toolbox boost.simd.operator
    **/
    struct unary_plus_ : ext::elementwise_<unary_plus_> { typedef ext::elementwise_<unary_plus_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::unary_plus_ , unary_plus  , 1 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::unary_plus_ , identity    , 1 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::unary_plus_ , id          , 1 )
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::unary_plus>
  {
    typedef boost::simd::tag::unary_plus_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::unary_plus_>
  {
    typedef boost::proto::tag::unary_plus type;
  };
} } }

#include <boost/simd/toolbox/operator/specific/common.hpp>

#endif
