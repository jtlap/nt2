/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONSTANT_DETAILS_IEEE_SPEC_HPP_INCLUDED
#define NT2_SDK_CONSTANT_DETAILS_IEEE_SPEC_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Base class for generating an integral constant
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/constant/splat.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

#define LOCAL_CALL(TAG, SEL, VAL)					\
  template<class Category,class Info>					\
  struct  call<constants::TAG,tag::constant_(Category),SEL,Info>	\
    : callable								\
  {									\
    template<class Sig> struct result;					\
    template<class This,class A0>					\
    struct result<This(A0)> :						\
      meta::as_integer<typename meta::strip<A0>::type::type,signed>{};  \
									\
     NT2_FUNCTOR_CALL(1)						\
     {									\
       typedef typename  NT2_CALL_RETURN_TYPE(1)::type type;		\
       return splat<type>(VAL);						\
     }									\
   }									\
  /**/

#define LOCAL_CONST(TAG, VD, VF)					\
  LOCAL_CALL(TAG, double, VD);						\
  LOCAL_CALL(TAG, float,  VF);						\
/**/

namespace nt2 { namespace functors
{
  LOCAL_CONST(nb_mantissa_bits_,                  52,         23); 
  LOCAL_CONST(nb_exponent_bits_,                  11,          8);
  LOCAL_CONST(max_exponent_    ,                1023,        127);
  LOCAL_CONST(min_exponent_    ,               -1022,       -126);
  LOCAL_CONST(nb_digits_       ,                  53,         24);
  LOCAL_CONST(ldexp_mask_      ,0x7FF0000000000000ll, 0x7F800000);
} }

#undef LOCAL_CONST
#undef LOCAL_CALL

#endif
