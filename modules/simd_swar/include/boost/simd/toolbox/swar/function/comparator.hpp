//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTION_COMPARATOR_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTION_COMPARATOR_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/simd/include/functor.hpp>
#include <boost/simd/toolbox/swar/include.hpp>

namespace boost { namespace simd {
  struct ascending_ {};
  struct descending_{};
  namespace tag
  {         
    struct comparator_ {};
  }
  BOOST_SIMD_FUNCTION_IMPLEMENTATION(tag::comparator_, comparator, 3)
  BOOST_SIMD_FUNCTION_IMPLEMENTATION_TPL(tag::comparator_, comparator, (A0 const&)(A0 const&)(A1 const&)(A0&)(A0&), 2)
} }
 
#include <boost/simd/toolbox/operator.hpp>
#include <boost/simd/toolbox/swar/function/scalar/comparator.hpp>
#include <boost/simd/toolbox/swar/function/simd/all/comparator.hpp> 

 
#endif

// modified by jt the 25/12/2010
