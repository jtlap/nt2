/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_NATIVE_CONSTANTS_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_NATIVE_CONSTANTS_HPP_INCLUDED

#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/constant/boolean.hpp>
#include <nt2/sdk/simd/details/impl/splat.hpp>

////////////////////////////////////////////////////////////////////////////////
// in SIMD, True is not !0 but ~0 whatever the type
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace functors
{
  template<class C, class X,class Info>
  struct  call<constants::true_,tag::simd_(C,X),Info>
  {
    template<class Sig> struct result;
    template<class This,class Target>
    struct result<This(nt2::meta::as_<Target>)>
    {
      typedef Target type;
    };

    NT2_FUNCTOR_CALL_DISPATCH ( 1
                              , typename meta::scalar_of<typename A0::type>::type
                              , (3, (double,float,integer_))
                              )


    NT2_FUNCTOR_CALL_EVAL_IF(1,double)
    {
      typedef union { uint64_t bits; double val; } type;
      type const that = { ~0 };
      return splat<typename A0::type>(that.val);
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1,float)
    {
      typedef union { uint32_t bits; float val; } type;
      type const that = { ~0 };
      return splat<typename A0::type>(that.val);
    }

    NT2_FUNCTOR_CALL_EVAL_IF(1,integer_)
    {
      typedef typename meta::scalar_of<typename A0::type>::type type;
      type const that = ~base(0);
      return splat<typename A0::type>(that);
    }
  };
} }
#endif
