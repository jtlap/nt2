//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_ABS_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_ABS_HPP_INCLUDED
#include <nt2/include/simd.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/toolbox/arithmetic/include.hpp>
/*!
 * \file
 * \brief Defines the absolute value functor: abs
 *
 * alias modulus
 *
 * the functor returns a value of the same type than the entry.
 * take care that for signed integers the absolute
 * value of Valmin is Valmin (thus negative !)
 * This is a side effect of the 2-complement representation
 * of integers.
 * To avoid this,  you can use the "abss" saturated functor
 * or convert the input parameter to a larger type before
 * taking the abs value.
 */


namespace nt2 { namespace tag
  {         
    struct abs_ {};
  }
  NT2_FUNCTION_IMPLEMENTATION(tag::abs_, abs, 1)
  NT2_FUNCTION_IMPLEMENTATION(tag::abs_, modulus, 1)
}
 
#include <nt2/toolbox/operator.hpp>
#include <nt2/toolbox/arithmetic/function/scalar/abs.hpp>
#include <nt2/toolbox/arithmetic/function/simd/all/abs.hpp> 

 
#endif

// modified by jt the 25/12/2010
