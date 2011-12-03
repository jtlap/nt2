/*******************************************************************************
 *         Copyright 2003-2011 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_LOGICAL_NOTAND_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BOOLEAN_FUNCTIONS_LOGICAL_NOTAND_HPP_INCLUDED
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
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

#include <boost/simd/toolbox/operator/specific/common.hpp>

#include <boost/proto/tags.hpp>

/*!
 * \ingroup boost_simd_operator
 * \defgroup boost_simd_operator_logical_notand logical_notand
 *
 * \par Description
 * return the logical and of the negation of the first parameter and the second parameter
 * the result type is logical type associated to the first parameter
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/logical_notand.hpp>
 * \endcode
 * 
 * \par Alias 
 * \arg l_notand
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::logical_notand_(A0,A1)>::type
 *     logical_notand(const A0 & a0,const A1 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of logical_notand
 * \param a1 the second parameter of logical_notand
 * 
 * \return a value of the logical type associated to the first parameter
 *  
 * \par Notes
 * In SIMD mode, this function acts elementwise on the inputs vectors elements
 * \par
 * This is a logical operation. Such operations return logical types.
 * You are invited to consult the rationale.
 *  
**/

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
     * \brief Define the tag logical_notand_ of functor logical_notand 
     *        in namespace boost::simd::tag for toolbox boost.simd.operator
    **/
    typedef boost::proto::tag::logical_notand logical_notand_;
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::logical_notand_      , logical_notand     , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::logical_notand_      , l_notand           , 2 )
} }

#endif
