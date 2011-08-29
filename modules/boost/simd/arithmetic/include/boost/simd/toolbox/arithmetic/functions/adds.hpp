//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_ADDS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_ADDS_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>

/*!
 * \file
 * \brief Defines the saturated addition functor: adds
 *
 * alias saturated_add
 *
 * This is generally equivalent to add except that in overflow cases
 * Valmin or Valmax for the input type is returned
 */

namespace boost { namespace simd {
  namespace tag
  {
    struct adds_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::adds_, adds, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::adds_, saturated_add, 2)
} }

#endif
