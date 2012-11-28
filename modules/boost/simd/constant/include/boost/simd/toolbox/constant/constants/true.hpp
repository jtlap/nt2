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
#ifndef BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_TRUE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_CONSTANT_CONSTANTS_TRUE_HPP_INCLUDED

#include <boost/simd/include/simd.hpp>
#include <boost/simd/sdk/constant/register.hpp>
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/simd/logical.hpp>

/*!
 * \ingroup boost_simd_constant
 * \defgroup boost_simd_constant_true True
 *
 * \par Description
 * Constant True is quite system specific as
 * this value is type dependant at the SIMD level.
 * \par
 * \arg For scalar it is the standard bool value \c true,
 * \arg for ssex and avx system it is a all bits set to one value in the type T,
 * \arg for larrabee system it is an 32 integer mask with all bits set to one,
 * \arg etc.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/true.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::true_(A0)>::type
 *     True();
 * }
 * \endcode
 *
 *
 * \param T template parameter of True
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
     * \brief Define the tag True of functor True
     *        in namespace boost::simd::tag for toolbox boost.simd.constant
    **/
    struct True : ext::constant_<True>
    {
      typedef logical<double> default_type;
      typedef ext::constant_<True> parent;
    };
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(boost::simd::tag::True, True)
} }

#include <boost/simd/sdk/constant/common.hpp>

#endif
