//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_IS_INCLUDED_C_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_IS_INCLUDED_C_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/simd/toolbox/bitwise/include.hpp>

namespace boost { namespace simd { namespace tag
  {         
    struct is_included_c_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_included_c_, is_included_c, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_included_c_, testz, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_included_c_, are_disjoint, 2) 
} }

#endif


