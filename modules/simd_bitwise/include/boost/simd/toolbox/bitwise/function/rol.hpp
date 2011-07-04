//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTION_ROL_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTION_ROL_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/simd/include/functor.hpp>
#include <boost/simd/toolbox/bitwise/include.hpp>

namespace boost { namespace simd { namespace tag
  {         
    struct rol_ {};
  }
  BOOST_SIMD_FUNCTION_IMPLEMENTATION(tag::rol_, rol, 2)
} }
 
#include <boost/simd/toolbox/operator.hpp>
#include <boost/simd/toolbox/bitwise/function/scalar/rol.hpp>
#include <boost/simd/toolbox/bitwise/function/simd/all/rol.hpp> 

 
#endif

// modified by jt the 25/12/2010
