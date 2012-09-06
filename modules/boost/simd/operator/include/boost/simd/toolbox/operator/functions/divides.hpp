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
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_DIVIDES_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_DIVIDES_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/proto/tags.hpp>

/*!
 * \ingroup boost_simd_operator
 * \defgroup boost_simd_operator_divides divides
 *
 * \par Description
 * return the elementwise division of the two parameters
 * Infix notation can be used with operator '/'
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/divides.hpp>
 * \endcode
 * 
 * \par Aliases 
 * \arg div
 * \arg rdiv
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::divides_(A0,A0)>::type
 *     divides(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of divides
 * \param a1 the second parameter of divides
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
     * \brief Define the tag divides_ of functor divides 
     *        in namespace boost::simd::tag for toolbox boost.simd.operator
    **/
    struct divides_ : ext::elementwise_<divides_> { typedef ext::elementwise_<divides_> parent; };
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::divides_             , divides         , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::divides_             , div             , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::divides_             , rdiv            , 2 )
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::divides>
  {
    typedef boost::simd::tag::divides_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::divides_>
  {
    typedef boost::proto::tag::divides type;
  };
} } }

#include <boost/simd/toolbox/operator/specific/common.hpp>

#endif
