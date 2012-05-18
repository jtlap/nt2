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
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_LOGICAL_NOT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_LOGICAL_NOT_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>

/*!
 * \ingroup boost_simd_operator
 * \defgroup boost_simd_operator_logical_not logical_not
 *
 * \par Description
 * return the logical negation of the parameter,
 * i.e. True or False of the entry type according that 
 * the input is zero or non zero
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/logical_not.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg l_not
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::logical_not_(A0)>::type
 *     logical_not(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of logical_not
 * 
 * \return a value of the same type as the parameter
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
     * \brief Define the tag logical_not_ of functor logical_not 
     *        in namespace boost::simd::tag for toolbox boost.simd.operator
    **/
    struct logical_not_ : ext::elementwise_<logical_not_> { typedef ext::elementwise_<logical_not_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::logical_not_ , logical_not  , 1 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::logical_not_ , l_not        , 1 )
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::logical_not>
  {
    typedef boost::simd::tag::logical_not_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::logical_not_>
  {
    typedef boost::proto::tag::logical_not type;
  };
} } }

#include <boost/simd/toolbox/operator/specific/common.hpp>

#endif
