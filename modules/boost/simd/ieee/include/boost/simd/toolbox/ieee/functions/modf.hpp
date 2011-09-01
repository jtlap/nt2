//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_MODF_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_IEEE_FUNCTIONS_MODF_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {         
    struct modf_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::modf_, modf, 1)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::modf_, modf,(A0 const&)(A1&)(A1&),2)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION_TPL(tag::modf_, modf,(A0 const&)(A1&),2) 

} }
 
#endif

// modified by jt the 25/12/2010
