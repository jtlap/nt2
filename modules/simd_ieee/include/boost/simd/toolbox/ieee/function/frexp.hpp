//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTION_FREXP_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTION_FREXP_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/simd/include/functor.hpp>
#include <boost/simd/toolbox/ieee/include.hpp>

namespace boost { namespace simd { namespace tag
  {         
    struct frexp_ {};
  }
  BOOST_SIMD_FUNCTION_IMPLEMENTATION(tag::frexp_, frexp, 1)
  BOOST_SIMD_FUNCTION_IMPLEMENTATION_TPL(tag::frexp_, frexp,(A0 const&)(A1&)(A2&),3)
  BOOST_SIMD_FUNCTION_IMPLEMENTATION_TPL(tag::frexp_, frexp,(A0 const&)(A1&),2) 
} }
 
#include <boost/simd/toolbox/operator.hpp>
#include <boost/simd/toolbox/ieee/function/scalar/frexp.hpp>
#include <boost/simd/toolbox/ieee/function/simd/all/frexp.hpp> 

 
#endif

// modified by jt the 25/12/2010
