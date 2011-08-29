//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_ABSS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_ABSS_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \file
 * \brief Defines the saturated absolute value functor: abss
 *
 * alias saturated_abs
 *
 * This is generally equivalent to abs except for signed integer
 * type for which abss(Valmin) is Valmax-1
 */

namespace boost { namespace simd {
  namespace tag
  {
    struct abss_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::abss_, abss, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::abss_, sturated_abs, 1)
} }

#endif
