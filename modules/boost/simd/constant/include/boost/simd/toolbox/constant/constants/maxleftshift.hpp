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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_MAXLEFTSHIFT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_MAXLEFTSHIFT_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/meta/int_c.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/simd/sdk/constant/common.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_maxleftshift Maxleftshift
 *
 * \par Description
 * Constant Maxleftshift
 * It is senseless to shift a value of more bits than the number of bits - 1
 * of the value type: this is that number.
 * \par
 * The value of this constant is type dependant. This means that for different
 * types it does not represent the same mathematical number.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/maxleftshift.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::maxleftshift_(A0)>::type
 *     Maxleftshift();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Maxleftshift
 *
 * \return type T value
 *
 *
**/

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
     * \brief Define the tag Maxleftshift of functor Maxleftshift
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    struct Maxleftshift : ext::constant_<Maxleftshift>
    {
      template<class Target, class Dummy=void>
      struct  apply
            : meta::int_c < typename dispatch::meta::
                                     as_integer < typename Target::type
                                                , signed
                                                >::type
                          , sizeof(typename Target::type)*CHAR_BIT-1
                          > {};
    };
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Maxleftshift, Maxleftshift)
} }

#endif
