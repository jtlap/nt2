/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_NATIVE_COMPARISONS_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_NATIVE_COMPARISONS_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Setup SIMD extension specific boolean operations
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/functor/operators.hpp>

#define NT2_MAKE_NATIVE_OP(TAG,OP)                                  \
template<class T,class X> inline                                    \
typename nt2::meta::enable_call<TAG(native<T,X>,native<T,X>)>::type \
OP(native<T,X> const& a0, native<T,X> const& a1)                    \
{                                                                   \
  nt2::functor<TAG> callee;                                         \
  return callee(a0,a1);                                             \
}                                                                   \
/**/

namespace nt2 { namespace tag
{
  struct compare_equal_         {};
  struct compare_not_equal_     {};
  struct compare_less_          {};
  struct compare_greater_       {};
  struct compare_less_equal_    {};
  struct compare_greater_equal_ {};
} }

namespace nt2 { namespace simd
{
  NT2_MAKE_NATIVE_OP( tag::compare_equal_        , operator== )
  NT2_MAKE_NATIVE_OP( tag::compare_not_equal_    , operator!= )
  NT2_MAKE_NATIVE_OP( tag::compare_less_         , operator<  )
  NT2_MAKE_NATIVE_OP( tag::compare_greater_      , operator>  )
  NT2_MAKE_NATIVE_OP( tag::compare_less_equal_   , operator<= )
  NT2_MAKE_NATIVE_OP( tag::compare_greater_equal_, operator>= )
} }

#include <nt2/sdk/simd/details/impl/comparisons.hpp>

#undef NT2_MAKE_NATIVE_OP

#endif
