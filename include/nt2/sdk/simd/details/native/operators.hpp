/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_NATIVE_OPERATORS_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_NATIVE_OPERATORS_HPP_INCLUDED

#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/functor/operators.hpp>

#define NT2_MAKE_NATIVE_OP(TAG,OP)                                \
template<class T1, class T2,class X> inline                       \
typename meta::enable_call<TAG(native<T1,X>,native<T2,X>)>::type  \
OP(native<T1,X> const& a0, native<T2,X> const& a1)                \
{                                                                 \
  functors::functor<TAG> callee;                                  \
  return callee(a0,a1);                                           \
}                                                                 \
/**/

namespace nt2 { namespace simd
{
  NT2_MAKE_NATIVE_OP( functors::bitwise_and_     , operator&  )
  NT2_MAKE_NATIVE_OP( functors::bitwise_or_      , operator|  )
  NT2_MAKE_NATIVE_OP( functors::bitwise_xor_     , operator^  )
  NT2_MAKE_NATIVE_OP( functors::logical_and_     , operator&& )
  NT2_MAKE_NATIVE_OP( functors::logical_or_      , operator|| )
  NT2_MAKE_NATIVE_OP( functors::plus_            , operator+  )
  NT2_MAKE_NATIVE_OP( functors::minus_           , operator-  )
  NT2_MAKE_NATIVE_OP( functors::divides_         , operator/  )
  NT2_MAKE_NATIVE_OP( functors::multiplies_      , operator*  )
  NT2_MAKE_NATIVE_OP( functors::modulo_          , operator%  )
  NT2_MAKE_NATIVE_OP( functors::shift_left_      , operator<< )
  NT2_MAKE_NATIVE_OP( functors::shift_right_     , operator>> )
} }

#include <nt2/sdk/simd/details/impl/operators.hpp>

#undef NT2_MAKE_NATIVE_OP
#endif
