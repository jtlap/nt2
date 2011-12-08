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
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_NATIVE_CAST_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_NATIVE_CAST_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_operator
 * \defgroup boost_simd_operator_native_cast native_cast
 *
 * \par Description
 * TODO Put description here
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/native_cast.hpp>
 * \endcode
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template<class T, class A0>
 *     meta::call<tag::native_cast_(A0, as_<T>)>::type
 *     native_cast(const A0 & a0);
 * }
 * \endcode
 *
 * \param T the native type to cast to
 * \param a0 the native to cast
 * 
 * \return \c a0 reinterpreted as a T
 *  
**/

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
     * \brief Define the tag native_cast_ of functor native_cast
     *        in namespace boost::simd::tag for toolbox boost.simd.operator
    **/
    struct native_cast_ {};
  }

  template<class T, class A0>
  BOOST_FORCEINLINE
  typename dispatch::meta::call<tag::native_cast_(A0, dispatch::meta::as_<T>)>::type
  native_cast(const A0& a0)
  {
    return typename dispatch::
           make_functor<tag::native_cast_, A0>::type()(a0, dispatch::meta::as_<T>());
  }
} }

#endif
