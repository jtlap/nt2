//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_BITWISE_ANY_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_REDUCTION_FUNCTIONS_BITWISE_ANY_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/simd/toolbox/reduction/include.hpp>

namespace boost { namespace simd { namespace tag
  {         
    struct bitwise_any_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitwise_any_, bitwise_any, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::bitwise_any_, any_negative, 1)  
} }
 
#endif
