//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_FAST_LDEXP_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_FAST_LDEXP_HPP_INCLUDED
#include <nt2/sdk/meta/size.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/bitwise_andnot.hpp>
#include <nt2/include/functions/shli.hpp>
//


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<fast_ldexp_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      boost::mpl::and_<meta::is_integral<A1>
                      ,meta::is_floating_point<A0>
		      ,meta::has_same_size<A0, A1, meta::scalar_of < boost::mpl::_> >
                      > {};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute fast_ldexp(const A0& a0, const A0& a1)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension, class Info>
  struct call<fast_ldexp_,tag::simd_(tag::arithmetic_,Extension),real_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL(2)
    {
      // No denormal provision
      typedef typename NT2_CALL_RETURN_TYPE(2)::type             result_type;
      typedef typename meta::scalar_of<result_type>::type             s_type;
      typedef typename meta::as_integer<result_type, signed>::type  int_type;
      
//       const sint_type  nmb = Nbmantissabits<s_type>();
//       const sint_type  mexp= Maxexponent<s_type>(); 
//       const int_type   vn1 = splat<int_type > ((2*(mexp-1)+3) << nmb) ;
      
      // clear exponent in x
      result_type const x = {b_andnot(a0, Ldexpmask<A0>())};
      // extract exponent and compute the new one
      int_type e = b_and(Ldexpmask<A0>(), a0);
      e += shli(a1, Nbmantissabits<s_type>());
      return b_or(x, e);
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension, class Info>
  struct call<fast_ldexp_,tag::simd_(tag::arithmetic_,Extension),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)>
      : meta::strip<A0>{};//


  };

} }

#endif
/// Revised by jt the 15/11/2010
