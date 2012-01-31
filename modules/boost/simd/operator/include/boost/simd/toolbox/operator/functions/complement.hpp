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
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_COMPLEMENT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_COMPLEMENT_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

#include <boost/simd/toolbox/operator/specific/common.hpp>

#include <boost/proto/tags.hpp>

/*!
 * \ingroup boost_simd_operator
 * \defgroup boost_simd_operator_complement complement
 *
 * \par Description
 * return the bitwise complement of the entry
 * Infix notation can be used with operator '~'
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/complement.hpp>
 * \endcode
 * 
 * \par Aliases 
 * \arg bitwise_not
 * \arg b_not
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::complement_(A0)>::type
 *     complement(const A0 & a0);
 * }
 * \endcode
 *
 * \param a0 the unique parameter of complement
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
     * \brief Define the tag complement_ of functor complement 
     *        in namespace boost::simd::tag for toolbox boost.simd.operator
    **/
    struct complement_ : ext::elementwise_<complement_>{};
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::complement_ , complement  , 1 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::complement_ , bitwise_not , 1 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::complement_ , b_not       , 1 )
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::complement>
  {
    typedef boost::simd::tag::complement_ type;
  };
} } }

#endif
