//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_MAP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_MAP_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_operator
 * \defgroup boost_simd_operator_map map
 *
 * \par Description
 * TODO Put description here
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/map.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class A0>
 *     meta::call<tag::map_(A0,A0)>::type
 *     map(const A0 & a0,const A0 & a1);
 * }
 * \endcode
 *
 * \param a0 the first parameter of map
 * \param a1 the second parameter of map
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
  /*!
   * \brief Define the tag map_ of functor map
   *        in namespace boost::simd::tag for toolbox boost.simd.operator
  **/
  namespace tag
  {
    struct map_ : dispatch::tag::formal_ { typedef dispatch::tag::formal_ parent; };
  }
} }

namespace boost { namespace simd
{
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::map_,map,2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::map_,map,(A0 const&)(A1&),2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::map_,map,3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::map_,map,(A0 const&)(A1 const&)(A2&),3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::map_,map,(A0 const&)(A1&)(A2&),3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::map_,map,4)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::map_,map,(A0 const&)(A1 const&)(A2 const&)(A3&),4)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::map_,map,(A0 const&)(A1 const&)(A2&)(A3&),4)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::map_,map,(A0 const&)(A1&)(A2&)(A3&),4)
} }

#endif
