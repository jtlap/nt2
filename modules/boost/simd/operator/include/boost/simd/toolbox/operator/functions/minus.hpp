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
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_MINUS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_MINUS_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>

/*!
 * \ingroup boost_simd_operator
 * \defgroup boost_simd_operator_minus minus
 *
 * \par Description
 * return the elementwise difference of the two parameters
 * Infix notation can be used with operator '-'
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/minus.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg sub
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::minus_(A0,A0)>::type
 *     minus(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of minus
 * \param a1 the second parameter of minus
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
     * \brief Define the tag minus_ of functor minus 
     *        in namespace boost::simd::tag for toolbox boost.simd.operator
    **/
    struct minus_ : ext::elementwise_<minus_> { typedef ext::elementwise_<minus_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::minus_             , minus            , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::minus_             , sub              , 2 )
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::minus>
  {
    typedef boost::simd::tag::minus_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::minus_>
  {
    typedef boost::proto::tag::minus type;
  };
} } }

#include <boost/simd/toolbox/operator/specific/common.hpp>

#endif
