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
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_MODULO_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_MODULO_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

#include <boost/simd/toolbox/operator/specific/common.hpp>

#include <boost/proto/tags.hpp>

/*!
 * \ingroup boost_simd_operator
 * \defgroup boost_simd_operator_modulo modulo
 *
 * \par Description
 * return the elementwise modulo of the two parameters
 * Infix notation can be used with operator '%'
 * Does not work for floating point entries.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/modulo.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::modulo_(A0,A0)>::type
 *     modulo(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of modulo
 * \param a1 the second parameter of modulo
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
     * \brief Define the tag modulo_ of functor modulo 
     *        in namespace boost::simd::tag for toolbox boost.simd.operator
    **/
    struct modulo_ : ext::elementwise_<modulo_>{};
  }

  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::modulo_             , modulo      , 2 )
} }

namespace boost { namespace dispatch { namespace meta
{
  template<>
  struct hierarchy_of<boost::proto::tag::modulus>
  {
    typedef boost::simd::tag::modulo_ type;
  };
  template<>
  struct proto_tag<boost::simd::tag::modulo_>
  {
    typedef boost::proto::tag::modulus type;
  };
} } }

#endif
