//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BOOST_MATH_FUNCTION_FACTORIAL_HPP_INCLUDED
#define NT2_TOOLBOX_BOOST_MATH_FUNCTION_FACTORIAL_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
#include <boost/math/special_functions/factorials.hpp>
#include <nt2/toolbox/boost_math/specific/interface.hpp>

namespace nt2 { namespace boost_math { namespace tag
  {         
    template < class T> struct factorial_ {};
  }
  NT2_BOOST_MATH_FUNCTION_IMPLEMENTATION_TPL(factorial,1)
  } }
 
#include <nt2/toolbox/boost_math/function/scalar/factorial.hpp>
// #include NT2_BOOST_MATH_INCLUDE(factorial.hpp) 

 
#endif

// modified by jt the 29/12/2010
