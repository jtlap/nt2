//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_GREATER_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTIONS_IS_GREATER_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/simd/toolbox/predicates/include.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    struct is_greater_ {};
  }
  
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_greater_, is_greater , 2 )
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_greater_, gt         , 2 )
} }

#endif
