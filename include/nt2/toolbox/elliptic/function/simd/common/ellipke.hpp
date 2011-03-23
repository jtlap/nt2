//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ELLIPTIC_FUNCTION_SIMD_COMMON_ELLIPKE_HPP_INCLUDED
#define NT2_TOOLBOX_ELLIPTIC_FUNCTION_SIMD_COMMON_ELLIPKE_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/any.hpp>
#include <nt2/include/functions/maximum.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/constant/eps_related.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ellipke_, tag::cpu_,
                       (A0)(X),
                       ((simd_<arithmetic_<A0>,X>))
                      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::ellipke_(tag::simd_<tag::arithmetic_, X >),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      {
	typedef typename meta::as_real<A0>::type      etype;
	typedef boost::fusion::tuple<etype, etype>     type;
      };

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_real<A0>::type       etype;
      typedef typename meta::scalar_of<etype>::type setype; 
      return ellipke(tofloat(a0), Eps<setype>()); 
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
//Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ellipke_, tag::cpu_,
		      (A0)(A1)(X),
                       ((simd_<arithmetic_<A0>,X>))
                       ((real_<A1>))
                      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::ellipke_(tag::simd_ < tag::arithmetic_, X >,
			    tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)>
      {
	typedef typename meta::as_real<A0>::type      etype;
	typedef boost::fusion::tuple<etype, etype>     type;
      };

    NT2_FUNCTOR_CALL(2)
    {
      return ellipke(tofloat(a0), a1); 
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ellipke_, tag::cpu_,
		      (A0)(A1)(X),
                       ((simd_<real_<A0>,X>))
                       ((real_<A1>))
                      );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::ellipke_(tag::simd_<tag::real_, X>,
			    tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)>
      {
	typedef typename meta::strip<A0>::type       etype;
	typedef boost::fusion::tuple<etype, etype>    type;
      };

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type; 
      typedef typename meta::as_integer<A0>::type iA0;
      typedef typename meta::scalar_of<A0>::type sA0;
      A0 nan =  b_or(is_ltz(a0), gt(a0, One<A0>()));
      A0 m = b_andnot(a0, nan); 
      A0 aa0 = One<A0>();
      A0 bb0 = sqrt(oneminus(m));
      A0 s0 = m;
      int32_t i1 = 0;
      sA0 mm = One<sA0>();
      A0 aa1; 
      while (gt(mm, a1))
	{
	  aa1 = average(aa0, bb0);
	  A0 bb1 = sqrt(aa0*bb0);
	  A0 cc1 = average(aa0, -bb0);
	  ++i1; 
	  A0 w1 = ldexp(sqr(cc1), splat<iA0>(i1));
	  mm =  maximum(w1); 
	  s0 += w1;
	  aa0 = aa1;
	  bb0 = bb1;
	};
      type res;
      A0 isneqm1 = eq(m, One<A0>());
      boost::fusion::at_c<0>(res) = b_or(nan, sel(isneqm1,One<A0>(), nt2::Pio_2<A0>()/aa1));
      boost::fusion::at_c<1>(res) = b_or(nan, sel(isneqm1,Inf<A0>(),
				    boost::fusion::at_c<0>(res)*(One<A0>()-s0*Half<A0>()))); 
      return res; 
    }
  };
} }

#endif
