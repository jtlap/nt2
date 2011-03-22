//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_ELLIPTIC_FUNCTION_SCALAR_ELLIPKE_HPP_INCLUDED
#define NT2_TOOLBOX_ELLIPTIC_FUNCTION_SCALAR_ELLIPKE_HPP_INCLUDED
#include <boost/fusion/tuple.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/ldexp.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/toolbox/trigonometric/include/constants.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <nt2/sdk/constant/infinites.hpp>
#include <nt2/sdk/constant/eps_related.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ellipke_, tag::cpu_,
                      (A0),
                      (arithmetic_<A0>)
                     )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::ellipke_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      {
	typedef typename std::tr1::result_of<meta::floating(A0)>::type etype;
	typedef boost::fusion::tuple<etype, etype>                   type;
      };


    NT2_FUNCTOR_CALL(1)
    {
      typedef typename std::tr1::result_of<meta::floating(A0)>::type type;
      return ellipke(type(a0), Eps<type>()); 
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ellipke_, tag::cpu_,
                      (A0)(A1),
                      (arithmetic_<A0>)
                      (arithmetic_<A1>)
                     )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::ellipke_(tag::arithmetic_,
			    tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> 
    {
      typedef typename meta::strip<A0>::type          etype;
      typedef boost::fusion::tuple<etype, etype>       type;
    };


    NT2_FUNCTOR_CALL(2)
    {
      typedef typename std::tr1::result_of<meta::floating(A0)>::type type;
      return ellipke(type(a0), type(a1)); 
    }
  };
} }
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ellipke_, tag::cpu_,
                      (A0)(A1),
                      (real_<A0>)
                      (real_<A1>)
                     )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::ellipke_(tag::real_,
			    tag::real_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0, class A1>
    struct result<This(A0, A1)> 
    {
      typedef typename meta::strip<A0>::type          etype;
      typedef boost::fusion::tuple<etype, etype>       type;
    };

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type type;
      type res; 
      if (is_ltz(a0) || gt(a0, One<A0>()))
      {
	boost::fusion::at_c<0>(res) = Nan<A0>();
	boost::fusion::at_c<1>(res) = Nan<A0>();
	return res; 
      }
      A0 m = a0; 
      A0 aa0 = One<A0>();;
      A0 bb0 = sqrt(oneminus(m));
      A0 s0 = m;
      int32_t i1 = 0;
      A0 mm = 1;
      A0 aa1; 
      while (mm > a1) {
	aa1 = average(aa0, bb0);
	A0 bb1 = sqrt(aa0*bb0);
	A0 cc1 = average(aa0, -bb0);
	i1++; 
	mm = ldexp(sqr(cc1), i1); 
	s0 += mm;
	aa0 = aa1;
	bb0 = bb1;
      };
      if (is_equal(m, One<A0>()))
	{
	  boost::fusion::at_c<0>(res) = One<A0>();
	  boost::fusion::at_c<0>(res) = Inf<A0>();
	}
      else
	{
	  boost::fusion::at_c<0>(res) = nt2::Pio_2<A0>()/aa1;
	  boost::fusion::at_c<1>(res) = boost::fusion::at_c<0>(res)*(One<A0>()-s0*Half<A0>());
	}
      return res; 
    }
  };
} }

#endif
