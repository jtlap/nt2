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
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_COMMA_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_COMMA_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>

/*!
 * \ingroup boost_simd_operator
 * \defgroup boost_simd_operator_comma comma
 *
 * \par Description
 * TODO Put description here
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/comma.hpp>
 * \endcode
 *
 * \par Alias
 * \arg then
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::comma_(A0,A0)>::type
 *     comma(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of comma
 * \param a1 the second parameter of comma
 *
 * \return a value of the common type of the parameters
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
     * \brief Define the tag comma_ of functor comma
     *        in namespace boost::simd::tag for toolbox boost.simd.operator
    **/
    struct comma_ : ext::elementwise_<comma_> { typedef ext::elementwise_<comma_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::comma_ , comma  , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::comma_ , then   , 2 )
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::comma>
  {
    typedef boost::simd::tag::comma_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::comma_>
  {
    typedef boost::proto::tag::comma type;
  };
} } }

#include <boost/simd/toolbox/operator/specific/common.hpp>

#endif
