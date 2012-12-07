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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_FALSE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_FALSE_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/constant/register.hpp>
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_false False
 *
 * \par Description
 * Constant False
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/false.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::false_(A0)>::type
 *     False();
 * }
 * \endcode
 *
 *
 * \param T template parameter of False
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
     * \brief Define the tag False of functor False
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    struct False : ext::pure_constant_<False>
    {
      typedef logical<double> default_type;
      typedef ext::pure_constant_<False> parent;
    };
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::False, False)
} }

#include <boost/simd/sdk/constant/common.hpp>

#endif
