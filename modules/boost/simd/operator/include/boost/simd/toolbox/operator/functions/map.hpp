//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
/*!
 * \file
**/
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_MAP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_MAP_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
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
namespace boost { namespace dispatch { namespace meta
{
  template<class T>
  struct elementwise_ : unspecified_<T>
  {
    typedef unspecified_<T> parent;
  };
} } }

namespace boost { namespace simd { namespace ext
{
  using boost::dispatch::meta::elementwise_;
} } }

namespace boost { namespace simd { namespace tag { struct map_ : ext::elementwise_<map_> {}; } } }
  /*!
   * \brief Define the tag map_ of functor map 
   *        in namespace boost::simd::tag for toolbox boost.simd.operator
  **/

namespace boost { namespace simd
{
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::map_,map,2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::map_,map,3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::map_,map,4)
} }

#endif
