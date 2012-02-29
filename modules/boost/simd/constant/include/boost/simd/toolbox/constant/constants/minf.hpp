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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_MINF_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_MINF_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/meta/float.hpp>
#include <boost/simd/sdk/meta/int_c.hpp>
#include <boost/simd/sdk/meta/double.hpp>
#include <boost/simd/sdk/constant/common.hpp>
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/toolbox/constant/include/constants/valmin.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_minf Minf
 *
 * \par Description
 * Constant Minf
 * \par
 * The value of this constant is type dependant. This means that for different
 * types it does not represent the same mathematical number.
 *
 * \par Header file
 * 
 * \code
 * #include <nt2/include/functions/minf.hpp>
 * \endcode
 * 
 * 
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::minf_(A0)>::type
 *     Minf();
 * }
 * \endcode
 *
 * 
 * \param T template parameter of Minf
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
     * \brief Define the tag Minf of functor Minf 
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    struct Minf : ext::constant_<Minf>
    { 
      typedef double default_type;
      template<class Target, class Dummy=void> 
      struct apply : Valmin::apply<Target,Dummy> {};  
    };

    template<class Dummy>
    struct  Minf::apply<float,Dummy> 
          : meta::single_<0xFF800000> {};

    template<class Dummy>
    struct  Minf::apply<double,Dummy> 
          : meta::double_<0xFFF0000000000000ULL> {};
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::Minf, Minf)
} }

#endif
