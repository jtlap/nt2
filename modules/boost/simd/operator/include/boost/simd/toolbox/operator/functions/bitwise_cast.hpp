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
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_BITWISE_CAST_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_BITWISE_CAST_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \ingroup boost_simd_operator
 * \defgroup boost_simd_operator_bitwise_cast bitwise_cast
 *
 * \par Description
 * TODO Put description here
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/bitwise_cast.hpp>
 * \endcode
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template<class T, class A0>
 *     meta::call<tag::bitwise_cast_(A0, as_<T>)>::type
 *     bitwise_cast(const A0 & a0);
 * }
 * \endcode
 *
 * \param T the type to cast to
 * \param a0 the value to cast
 * 
 * \return a T with the same bitwise layout as \c a0
 *  
 * \par Notes
 * sizeof(A0) must be equal to sizeof(T)
 * \par
 * 
 *
 * \par Example Usage:
 *
 * \include bitwise_cast.cpp
 *
 * The expected out put is :
 *
 * \c bf800000
 *  
**/

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
     * \brief Define the tag bitwise_cast_ of functor bitwise_cast
     *        in namespace boost::simd::tag for toolbox boost.simd.operator
    **/
    struct bitwise_cast_ {};
  }

  template<class T, class A0>
  BOOST_FORCEINLINE
  typename dispatch::meta::call<tag::bitwise_cast_(A0, dispatch::meta::as_<T>)>::type
  bitwise_cast(const A0& a0)
  {
    return typename dispatch::
           make_functor<tag::bitwise_cast_, A0>::type()(a0, dispatch::meta::as_<T>());
  }
} }

#endif
