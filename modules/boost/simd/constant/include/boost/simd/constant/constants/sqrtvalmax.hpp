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
#ifndef BOOST_SIMD_CONSTANT_CONSTANTS_SQRTVALMAX_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_CONSTANTS_SQRTVALMAX_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/simd/sdk/constant/register.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_sqrtvalmax Sqrtvalmax
 *
 * \par Description
 * Constant Sqrtvalmax : the least non zero positive value of floating point numbers,
 * i.e. 2.225073858507201e-308 for double and  1.1754944e-38 for float
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/sqrtvalmax.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::sqrtvalmax_(A0)>::type
 *     Sqrtvalmax();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Sqrtvalmax
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
     * \brief Define the tag Sqrtvalmax of functor Sqrtvalmax
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    struct Sqrtvalmax : ext::pure_constant_<Sqrtvalmax>
    {
      typedef double default_type;
      template<class Target, class Dummy=void>
      struct  apply
            : meta::int_c < typename Target::type
                          , typename Target::
                            type( (typename Target::type(1)
                                  << (sizeof(typename Target::type)*CHAR_BIT/2))-1
                                )
                          >
      {};
    };

    template<class T, class Dummy>
    struct  Sqrtvalmax::apply< boost::dispatch::meta::single_<T>,Dummy>
          : meta::single_<0x5f800000> {};

    template<class T, class Dummy>
    struct  Sqrtvalmax::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::double_<0x5ff0000000000001ll> {};

    template<class T, class Dummy>
    struct  Sqrtvalmax::apply<boost::dispatch::meta::int8_<T>,Dummy>
          : meta::int_c<T, 11> {};

    template<class T, class Dummy>
    struct  Sqrtvalmax::apply<boost::dispatch::meta::int16_<T>,Dummy>
          : meta::int_c<T, 181> {};

    template<class T, class Dummy>
    struct  Sqrtvalmax::apply<boost::dispatch::meta::int32_<T>,Dummy>
          : meta::int_c<T, 46340> {};

    template<class T, class Dummy>
    struct  Sqrtvalmax::apply<boost::dispatch::meta::int64_<T>,Dummy>
          : meta::int_c<T, 3037000499> {};
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Sqrtvalmax, Sqrtvalmax)
} }

#include <boost/simd/sdk/constant/common.hpp>

#endif
