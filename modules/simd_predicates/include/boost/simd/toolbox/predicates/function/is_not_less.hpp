//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTION_IS_NOT_LESS_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_PREDICATES_FUNCTION_IS_NOT_LESS_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/simd/include/functor.hpp>
#include <boost/simd/toolbox/predicates/include.hpp>

namespace boost { namespace simd { namespace tag
  {         
    struct is_not_less_ {};
  }
  BOOST_SIMD_FUNCTION_IMPLEMENTATION(tag::is_not_less_, is_not_less, 2)
  BOOST_SIMD_FUNCTION_IMPLEMENTATION(tag::is_not_less_, is_nlt, 2)
} }

#include <boost/simd/toolbox/operator.hpp>
#include <boost/simd/toolbox/predicates/function/scalar/is_not_less.hpp>
#include <boost/simd/toolbox/predicates/function/simd/all/is_not_less.hpp> 

#include <boost/simd/toolbox/predicates/recognition/is_not_less.hpp>

#endif
