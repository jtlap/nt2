//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_EXPONENTIAL_CONSTANTS_LOG_2OLOG_10_HPP_INCLUDED
#define NT2_TOOLBOX_EXPONENTIAL_CONSTANTS_LOG_2OLOG_10_HPP_INCLUDED
/*!
 * \file
**/
#include <boost/simd/sdk/constant/constant.hpp>
#include <boost/simd/sdk/constant/register.hpp>

/*!
 * \ingroup expon_constant
 * \defgroup expon_constant_log_2olog_10 log_2olog_10
 *
 * \par Description
 * Constant log_2olog_10 : \f$\frac{\log(2)}{\log(10)}\f$ constant.
 * \par
 * The value of this constant is type dependant. This means that for different
 * types it does not represent the same mathematical number.
 *
 * \par Header file
 *
 * \code
 * #include <nt2/include/functions/log_2olog_10.hpp>
 * \endcode
 *
 *
 * \synopsis
 *
 * \code
 * namespace boost::simd
 * {
 *   template <class T,class A0>
 *     meta::call<tag::log_2olog_10_(A0)>::type
 *     log_2olog_10();
 * }
 * \endcode
 *
 *
 * \param T template parameter of log_2olog_10
 *
 * \return type T value
 *
 *
**/

namespace nt2
{
  namespace tag
  {
    BOOST_SIMD_CONSTANT_REGISTER( Log_2olog_10, double
                                , 0, 0x3e9a209b
                                , 0x3fd34413509f79ffLL
                                );
  }

  BOOST_SIMD_CONSTANT_IMPLEMENTATION(tag::Log_2olog_10, Log_2olog_10);
}

#endif
