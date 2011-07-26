//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTION_IS_NOT_LESS_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTION_IS_NOT_LESS_EQUAL_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>
#include <boost/simd/toolbox/predicates/include.hpp>

namespace boost { namespace dispatch { namespace tag
  {         
    struct is_not_less_equal_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_not_less_equal_, is_not_less_equal, 2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::is_not_less_equal_, is_nle, 2)
} }
 
#include <boost/simd/toolbox/operator.hpp>
#include <boost/simd/toolbox/predicates/function/scalar/is_not_less_equal.hpp>
#include <boost/simd/toolbox/predicates/function/simd/all/is_not_less_equal.hpp> 

#include <boost/simd/toolbox/predicates/recognition/is_not_less_equal.hpp>

#endif
