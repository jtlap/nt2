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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_MINDENORMAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_MINDENORMAL_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/meta/float.hpp>
#include <boost/simd/sdk/meta/int_c.hpp>
#include <boost/simd/sdk/meta/double.hpp>
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/toolbox/constant/constants/smallestposval.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_mindenormal Mindenormal
 *
 * \par Description
 * Constant Mindenormal : the least non zero positive value of floating point numbers,
 * i.e. 4.940656458412465e-324 for double and 1.4012985e-45 for float
 * \par
 * The value of this constant is type dependant. This means that for different
 * types it does not represent the same mathematical number.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/mindenormal.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::mindenormal_(A0)>::type
 *     Mindenormal();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Mindenormal
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
     * \brief Define the tag Mindenormal of functor Mindenormal
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/

    struct Mindenormal : ext::pure_constant_<Mindenormal>
    {
      template<class Target, class Dummy=void>
      struct apply : meta::int_c<typename Target::type,1> {};
    };

    template<class T, class Dummy>
    struct  Mindenormal::apply<boost::dispatch::meta::single_<T>,Dummy>
          : meta::single_<1> {};

    template<class T, class Dummy>
    struct  Mindenormal::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::double_<1> {};
  }

#ifdef BOOST_SIMD_NO_DENORMALS
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Smallestposval, Mindenormal)
#else
  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Mindenormal, Mindenormal)
#endif

} }

#include <boost/simd/sdk/constant/common.hpp>

#endif
