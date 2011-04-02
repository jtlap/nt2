//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_SUBS_HPP_INCLUDED
#define NT2_TOOLBOX_ARITHMETIC_FUNCTION_SCALAR_SUBS_HPP_INCLUDED
#include <nt2/include/functions/saturate.hpp>
#include <nt2/include/functions/adds.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is integer_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::subs_, tag::cpu_,
                      (A0)(A1),
                      (integer_<A0>)(integer_<A1>)
                     )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::subs_(tag::integer_,tag::integer_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::upgrade<A0>::type utype; 
      return nt2::saturate<A0>(utype(a0)-utype(a1)); 
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::subs_, tag::cpu_,
                      (A0)(A1),
                      (unsigned_<A0>)(unsigned_<A1>)
                     )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::subs_(tag::unsigned_,tag::unsigned_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      if (gt(a0, a1))
	return a0-a1;
      else
	return Zero<A0>(); 
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::subs_, tag::cpu_,
                      (A0)(A1),
                      (int64_<A0>)(int64_<A1>)
                     )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::subs_(tag::int64_,tag::int64_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0,A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
       if (eq(a1, Valmin<A0>()))
 	{
          if (a0 >= Mone<A0>()) return Valmax<A0>(); 
 	  return adds(adds(a0, Valmax<A0>()),One<A0>());
 	}
      return nt2::adds(a0, -a1);     
    }
  };
} }



#endif
