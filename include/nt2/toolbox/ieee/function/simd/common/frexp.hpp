//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_FREXP_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_FREXP_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/bitwise_notand.hpp>
#include <nt2/include/functions/shri.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <boost/fusion/include/vector.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::frexp_, tag::cpu_,
                        (A0)(X),
                        ((simd_<arithmetic_<A0>,X>))
                       );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::frexp_(tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename meta::strip<A0>::type                     A00;
      typedef typename meta::as_integer<A00, signed>::type  exponent;
      typedef boost::fusion::vector<A00,exponent>                type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      typename NT2_RETURN_TYPE(1)::type res;
      eval( a0
          , boost::fusion::at_c<0>(res)
          , boost::fusion::at_c<1>(res)
          );
      return res;
    }
  private:
    template<class A0,class R0,class R1> inline void
    eval(A0 const& a0,R0& r0, R1& r1)const
    {
      typedef typename meta::as_integer<A0, signed>::type      int_type;
      typedef typename meta::scalar_of<int_type>::type        sint_type;
      typedef typename meta::scalar_of<A0>::type                 s_type;
      const sint_type me = Maxexponent<s_type>()-1;
      const sint_type nmb= Nbmantissabits<s_type>();
      const sint_type n1 = ((2*me+3)<<nmb);
      const sint_type n2 = me<<nmb;
      const  int_type vme = splat<int_type>(me);
      A0 ci_exp=simd::native_cast<A0>(splat< int_type>(n1));
      r1 = simd::native_cast<int_type>(b_and(ci_exp, a0));// extract exponent
      A0 x = b_notand(ci_exp, a0);                        // clear exponent in a0
      r1 = sub(shri(r1,nmb), vme);                        // compute exponent
      r0 = b_or(x,splat<int_type>(n2));                   // insert exponent+1 in x
      A0 test0 = is_nez(a0);
      int_type test1 = gt(r1,vme);
      r1 = b_and(r1, b_notand(test1, test0));
      //      r1 = seladd((b_notand(test1, test0)), Zero<int_type>(), r1);
      //      r0 = seladd(test0,Zero<A0>(),seladd(test1,r0,a0));
      r0 = b_and(seladd(test1,r0,a0), test0);
    }
  };
} }

#endif
// modified by jt the 04/01/2011