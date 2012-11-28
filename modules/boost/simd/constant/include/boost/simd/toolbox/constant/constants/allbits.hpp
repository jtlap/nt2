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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_ALLBITS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_ALLBITS_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/meta/int_c.hpp>
#include <boost/simd/sdk/meta/float.hpp>
#include <boost/simd/sdk/meta/double.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_allbits Allbits
 *
 * \par Description
 * Constant Allbits : all bits set to 1.
 * \par
 * The value of this constant is type dependant. This means that for different
 * types it does not represent the same mathematical number.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/allbits.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::allbits_(A0)>::type
 *     Allbits();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Allbits
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
     * \brief Define the tag Allbits of functor Allbits
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    struct Allbits : ext::pure_constant_<Allbits>
    {
      typedef double default_type;
      template<class Target, class Dummy=void>
      struct  apply
            : meta::int_c<typename Target::type, -1>
      {};
    };

    template<class T, class Dummy>
    struct  Allbits::apply<boost::dispatch::meta::single_<T>,Dummy>
          : meta::single_ < apply < boost::dispatch::meta::uint32_<uint32_t>
                                  , Dummy
                                  >::value
                          > {};

    template<class T, class Dummy>
    struct  Allbits::apply<boost::dispatch::meta::double_<T>,Dummy>
          : meta::double_ < apply < boost::dispatch::meta::uint64_<uint64_t>
                                  , Dummy
                                  >::value
                          > {};

    template<class T, class Dummy>
    struct  Allbits::apply<boost::dispatch::meta::uint8_<T>,Dummy>
          : meta::int_c<boost::simd::uint8_t,0xFF> {};

    template<class T, class Dummy>
    struct  Allbits::apply<boost::dispatch::meta::uint16_<T>,Dummy>
          : meta::int_c<boost::simd::uint16_t,0xFFFFU> {};

    template<class T, class Dummy>
    struct  Allbits::apply<boost::dispatch::meta::uint32_<T>,Dummy>
          : meta::int_c<boost::simd::uint32_t,0xFFFFFFFFUL> {};

    template<class T, class Dummy>
    struct  Allbits::apply<boost::dispatch::meta::uint64_<T>,Dummy>
          : meta::int_c<boost::simd::uint64_t,0xFFFFFFFFFFFFFFFFULL> {};

  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Allbits, Allbits)
} }

#include <boost/simd/sdk/constant/common.hpp>

#endif
