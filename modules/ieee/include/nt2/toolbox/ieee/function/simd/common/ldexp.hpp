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
#include <nt2/include/functions/rshl.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH_IF(tag::ldexp_, tag::cpu_,
			 (A0)(A1)(X),
			 (boost::mpl::equal_to<boost::mpl::sizeof_<A0>,boost::mpl::sizeof_<A1> >),
			 (tag::ldexp_(tag::simd_<tag::arithmetic_,X>, tag::simd_<tag::integer_,X>)), 
                         ((simd_<arithmetic_<A0>,X>))
			 ((simd_<integer_<A1>,X>))
			 );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::ldexp_(tag::simd_<tag::arithmetic_, X> ,
                          tag::simd_<tag::integer_, X> ),
              tag::cpu_, Dummy> : callable
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

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_ and A1 scalar
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ldexp_, tag::cpu_,
		      (A0)(A1)(X),
		      ((simd_<arithmetic_<A0>,X>))
		      ((integer_<A1>))
		      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::ldexp_(tag::simd_<tag::arithmetic_, X> ,
                          tag::integer_ ),
              tag::cpu_, Dummy> : callable
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

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH_IF(tag::ldexp_, tag::cpu_,
			 (A0)(A1)(X),
			 (boost::mpl::equal_to<boost::mpl::sizeof_<A0>,boost::mpl::sizeof_<A1> >),
			 (tag::ldexp_(tag::simd_<tag::real_,X>, tag::simd_<tag::integer_,X>)), 
			 ((simd_<real_<A0>,X>))
			 ((simd_<integer_<A1>,X>))
			 );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::ldexp_(tag::simd_<tag::real_, X> ,
                          tag::simd_<tag::integer_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      // No denormal provision
      typedef typename NT2_RETURN_TYPE(2)::type                  result_type;
      typedef typename meta::scalar_of<result_type>::type             s_type;
      typedef typename meta::as_integer<result_type, signed>::type  int_type;
      typedef typename meta::scalar_of<int_type>::type             sint_type;

      // clear exponent in x
      result_type const x = {b_andnot(a0, Ldexpmask<A0>())};

      // extract exponent and compute the new one
      int_type e    = b_and(Ldexpmask<A0>(), a0);
      e += shli(a1, Nbmantissabits<s_type>());
      return select( b_and(is_nez(a0),is_finite(a0))
                     , b_or(x, e)
                     , a0
                     );
    }
  };
} }
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_ and A1 is scalar
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ldexp_, tag::cpu_,
                        (A0)(A1)(X),
                        ((simd_<real_<A0>,X>))
                        ((integer_<A1>))
                       );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::ldexp_(tag::simd_<tag::real_, X> ,
                          tag::integer_ ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::as_integer<A0>::type iA0; 
      return ldexp(a0, splat<iA0>(a1)); 
    }
  };
} }

#endif
// modified by jt the 04/01/2011
