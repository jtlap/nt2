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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_INF_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_INF_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/meta/int_c.hpp>
#include <boost/simd/sdk/meta/float.hpp>
#include <boost/simd/sdk/meta/double.hpp>
#include <boost/simd/sdk/meta/make_dependent.hpp>
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/config.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_inf Inf
 *
 * \par Description
 * Constant Inf
 * \arg Maximum value of the type for integer types
 * \arg \f$= \infty \f$ for floating points
 * \par
 * The value of this constant is type dependant. This means that for different
 * types it does not represent the same mathematical number.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/inf.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::inf_(A0)>::type
 *     Inf();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Inf
 *
 * \return type T value
 *
 *
**/

namespace boost { namespace simd
{
  namespace tag
  {
    struct Valmax;

    /*!
     * \brief Define the tag Inf of functor Inf
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    #ifdef BOOST_SIMD_NO_INFINITIES
    typedef Valmax Inf;
    #else
    struct Inf : ext::pure_constant_<Inf>
    {
      typedef ext::pure_constant_<Inf> parent;
      typedef double default_type;
      template<class Target, class Dummy=void>
      struct apply : meta::make_dependent<Valmax, Dummy>::type::template apply<Target,Dummy> {};
    };

    template<class T, class Dummy>
    struct  Inf::apply<boost::dispatch::meta::single_<T>,Dummy>
          : meta::single_<0x7F800000> {};

    template<class T, class Dummy>
    struct  Inf::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::double_<0x7FF0000000000000ULL> {};
    #endif
  }
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Inf, Inf)

} }

#include <boost/simd/toolbox/constant/include/constants/valmax.hpp>
#include <boost/simd/sdk/constant/common.hpp>

#endif
