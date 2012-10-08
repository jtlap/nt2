//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_CONSTANTS_LOG_2_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_CONSTANTS_LOG_2_HPP_INCLUDED
/*!
 * \file
**/
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/constant/register.hpp>

/*!
 * \ingroup expon_constant
 * \defgroup expon_constant_log_2 Log_2
 *
 * \par Description
 * Constant log_2 : \f$\log(2)\f$ constant.
 * \par
 * The value of this constant is type dependant. This means that for different
 * types it does not represent the same mathematical number.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/log_2.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::log_2_(A0)>::type
 *     log_2();
 * }
 * \endcode
 *
 *
 * \param T template parameter of Log_2
 *
 * \return type T value
 *
 *
**/

namespace nt2
{
  namespace tag
  {
    BOOST_SIMD_CONSTANT_REGISTER( Log_2, double
                                , 0, 0x3f317218
                                , 0x3fe62e42fefa39efLL
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Log_2, Log_2);
}

#endif
