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
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_IF_ELSE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_IF_ELSE_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>

/*!
 * \ingroup boost_simd_operator
 * \defgroup boost_simd_operator_if_else if_else
 *
 * \par Description
 * return the elementwise selected element from the second and third operand
 * according to the non nullity of the first operand.
 * parameters 2 and 3 must share the same type and also the same element size
 * as parameter 1
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/if_else.hpp>
 * \endcode
 *
 * \par Alias
 * \arg where
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0,class A1,class A2>
 *     meta::call<tag::if_else_(A0,A1,A2)>::type
 *     if_else(const A0 & a0,const A1 & a1,const A2 & a2);
 * }
 * \endcode
 *
 * \param a0 the first parameter of if_else
 * \param a1 the second parameter of if_else
 * \param a2 the third parameter of if_else
 *
 * \return a value of the common type of the second and third  parameter
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
     * \brief Define the tag if_else_ of functor if_else
     *        in namespace boost::simd::tag for toolbox boost.simd.operator
    **/
    struct if_else_ : ext::elementwise_<if_else_> { typedef ext::elementwise_<if_else_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_          , if_else         , 3 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_          , where           , 3 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_          , select          , 3 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::if_else_          , sel             , 3 )

} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::if_else_>
  {
    typedef boost::simd::tag::if_else_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::if_else_>
  {
    typedef boost::proto::tag::if_else_ type;
  };
} } }

#include <boost/simd/toolbox/operator/specific/common.hpp>

#endif
