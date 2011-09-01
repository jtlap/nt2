//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_FMA_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_FMA_HPP_INCLUDED
#include <boost/simd/include/simd.hpp>
#include <boost/dispatch/include/functor.hpp>


namespace boost { namespace simd { namespace tag
  {         
    struct fma_ {};
  }
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::fma_, fma, 3)
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::fma_, madd, 3)
  
  BOOST_DISPATCH_FUNCTION_INTERFACE(tag::fma_, fam, 3)
  {
    typename boost::dispatch::make_functor<tag::fma_, A0>::type callee;
    return callee(a1, a2, a0);
  }
  
  BOOST_DISPATCH_FUNCTION_INTERFACE(tag::fma_, amul, 3)
  {
    typename boost::dispatch::make_functor<tag::fma_, A0>::type callee;
    return callee(a1, a2, a0);
  }
  
} }
 
#endif
