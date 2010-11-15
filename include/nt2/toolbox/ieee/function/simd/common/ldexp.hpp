//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_LDEXP_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_LDEXP_HPP_INCLUDED
#include <nt2/sdk/meta/size.hpp>
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <nt2/sdk/constant/properties.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/shli.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/is_finite.hpp>
//
#include <nt2/include/functions/select.hpp>


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<ldexp_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      boost::mpl::and_<meta::is_integral<A1>, 
		       meta::is_floating_point<A0>, 
		       meta::has_same_size<A0, A1, meta::scalar_of < boost::mpl::_> >
                      > {};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute ldexp(const A0& a0, const A0& a1)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is real_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<ldexp_,tag::simd_(tag::arithmetic_),real_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      // No denormal provision
      typedef typename NT2_CALL_RETURN_TYPE(2)::type result_type;
      typedef typename meta::scalar_of<result_type>::type             s_type;
      typedef typename meta::as_integer<result_type, signed>::type          int_type;
      typedef typename meta::scalar_of<int_type>::type             sint_type;
      
//       sint_type const nmb = Nbmantissabits<s_type>();
//       sint_type const n1  = ((2*(Maxexponent<s_type>()-1)+3) << nmb);
//       const int_type  vn1 = splat<int_type>(n1);
      
      // clear exponent in x
      result_type const x(b_andnot(a0, Ldexpmask<A0>()));
      
      // extract exponent and compute the new one
      int_type e    = b_and(Ldexpmask<A0>(), a0);
      e += shli(a1, Nbmantissabits<s_type>()); 
      return select( b_and(is_nez(a0),is_finite(a0))
                     , b_or(x, e)
                     , a0
                     );
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is arithmetic_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<ldexp_,tag::simd_(tag::arithmetic_),arithmetic_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
        return rshl(a0, a1);
    }
  };

} }

#endif
/// Revised by jt the 15/11/2010
