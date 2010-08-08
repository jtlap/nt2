/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_COMMON_BITWISE_XOR_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_COMMON_BITWISE_XOR_HPP_INCLUDED

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // Bitwise operators requires same bits size
  //////////////////////////////////////////////////////////////////////////////
  template<class C,class X,class Info>
  struct validate<bitwise_xor_,tag::simd_(C,X),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct  result<This(A0,A1)>
          : boost::mpl::bool_< sizeof(A0) == sizeof(A1) > {};
  };

  template<class C, class X,class Info>
  struct call<bitwise_xor_,tag::simd_(C,X),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> { typedef A0 type; };

    NT2_FUNCTOR_CALL(2)
    {
      A0 that = map(functor<bitwise_xor_>(), a0, a1);
      return that;
    }
  };
} }

#endif
