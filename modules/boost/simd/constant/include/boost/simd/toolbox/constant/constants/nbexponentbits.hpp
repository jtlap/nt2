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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_NBEXPONENTBITS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_NBEXPONENTBITS_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/meta/int_c.hpp>
#include <boost/simd/sdk/constant/common.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_nbexponentbits Nbexponentbits
 *
 * \par Description
 * Constant Nbexponentbits, The number of exponent bits of a floating point number,
 * i.e. 11 for double and 8 for float.
 * \par
 * The value of this constant is type dependant. This means that for different
 * types it does not represent the same mathematical number.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/nbexponentbits.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::nbexponentbits_(A0)>::type
 *     Nbexponentbits();
 * }
 * \endcode
 *
 * 
 * \param T template parameter of Nbexponentbits
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
     * \brief Define the tag Nbexponentbits of functor Nbexponentbits 
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    struct Nbexponentbits : ext::constant_<Nbexponentbits>
    { 
      template<class Target, class Dummy=void> 
      struct  apply : meta::int_c<Target,0> {}; 
    };

    template<class Dummy>
    struct  Nbexponentbits::apply<float,Dummy> 
          : meta::int_c<boost::simd::int32_t,8> {};

    template<class Dummy>
    struct  Nbexponentbits::apply<double,Dummy> 
          : meta::int_c<boost::simd::int64_t,11> {};
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Nbexponentbits, Nbexponentbits)
} }

#endif
