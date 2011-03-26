//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_MULS_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_MULS_HPP_INCLUDED
#include <nt2/include/functions/genmask.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::muls_, tag::cpu_,
                      (A0)(A1),
                      (unsigned_<A0>)(unsigned_<A1>)
                     )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::muls_(tag::unsigned_,tag::unsigned_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::upgrade<A0>::type utype; 
      utype res = utype(a0)*utype(a1);
      return A0(res) | genmask(A0(res >> sizeof(A0)*8)); 	
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is integer_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::muls_, tag::cpu_,
                      (A0)(A1),
                      (integer_<A0>)(integer_<A1>)
                     )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::muls_(tag::integer_,tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::upgrade<A0>::type utype; 
      utype res = utype(a0)*utype(a1);
      A0 res2= ((A0) (a0 ^ a1) >> sizeof(A0)*8) + Valmax<A0>();
      A0 hi = (res >> sizeof(A0)*8);
      if (hi != (A0(res) >> (sizeof(A0)*8-1))) res = res2;
      return A0(res); 
    }
  };
} }


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint64_t_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::muls_, tag::cpu_,
                      (A0)(A1),
                      (uint64_<A0>)(uint64_<A1>)
                     )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::muls_(tag::uint64_,tag::uint64_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      //      typedef __uint128_t utype;
      typedef int64_t utype; 
      utype res = utype(a0)*utype(a1);
      return A0(res) | genmask(A0(res >> 64)); 	
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is integer_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::muls_, tag::cpu_,
                      (A0)(A1),
                      (int64_<A0>)(int64_<A1>)
                     )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::muls_(tag::int64_,tag::int64_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef uint64_t utype; 
      //      typedef __int128_t utype; 
      utype res = utype(a0)*utype(a1);
      A0 res2= ((A0) (a0 ^ a1) >> 31) + Valmax<A0>();
      A0 hi = (res >> 32);
      if (hi != (A0(res) >> 31)) res = res2;
      return A0(res); 
    }
  };
} }


#endif
