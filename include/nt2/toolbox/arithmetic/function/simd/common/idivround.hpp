//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_IDIVROUND_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SIMD_COMMON_IDIVROUND_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/round2even.hpp>
#include <nt2/include/functions/iround.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/group.hpp>
#include <nt2/include/functions/split.hpp>
#include <nt2/include/functions/tofloat.hpp>


namespace nt2 { namespace functors
{

  /////////////////////////////////////////////////////////////////////////////
  // Compute idivround(const A0& a0, const A0& a1)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<idivround_,tag::simd_(tag::arithmetic_),real_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>  : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2){ return round2even(a0/a1); }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is unsigned_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<idivround_,tag::simd_(tag::arithmetic_),unsigned_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>  : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2){ return rdivide(a0+a1/Two<A0>(), a1); }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int8_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<idivround_,tag::simd_(tag::arithmetic_),int8_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>  : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::scalar_of<A0>::type           stype;
      typedef typename meta::upgrade<stype>::type itype;
      typedef typename simd::native<itype, Extension>                 ivtype;
      ivtype a0l, a0h, a1l, a1h;
      boost::fusion::tie(a0l, a0h) = split(a0);
      boost::fusion::tie(a1l, a1h) = split(a1);
      return simd::native_cast<A0>(group(idivround(a0l, a1l),
					 idivround(a0h, a1h) ));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is int16_t
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<idivround_,tag::simd_(tag::arithmetic_),int16_t,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>  : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::scalar_of<A0>::type           stype;
      typedef typename meta::upgrade<stype>::type itype;
      typedef typename simd::native<itype,Extension>                 ivtype;
      ivtype a0l, a0h, a1l, a1h;
      boost::fusion::tie(a0l, a0h) = split(a0);
      boost::fusion::tie(a1l, a1h) = split(a1);
      return simd::native_cast<A0>(group(idivround(a0l, a1l),
					 idivround(a0h, a1h)));
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<idivround_,tag::simd_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)>  : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2){ return iround(tofloat(a0)/tofloat(a1)); }
  };

} }

#endif
/// Revised by jt the 15/11/2010
