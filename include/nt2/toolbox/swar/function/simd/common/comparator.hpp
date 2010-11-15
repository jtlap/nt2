//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_COMMON_COMPARATOR_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_COMMON_COMPARATOR_HPP_INCLUDED
#include <boost/mpl/vector.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/any.hpp>


namespace nt2 { namespace functors
{
//   template<class Extension,class Info>
//   struct validate<comparator_,tag::simd_(tag::arithmetic_,Extension),Info>
//   {
//     template<class Sig> struct result;
//     template<class This,class A0,class A1,class A2>
//     struct result<This(A0,A1,A2)> :
//       boost::mpl::and_<meta::is_scalar<A2>,
// 		       meta::is_integral<A2>
//                       > {};
//  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute comparator(const A0& a0, const A0& a1, const A0& a2)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is fundamental_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<comparator_,tag::simd_(tag::arithmetic_),fundamental_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A2>
    struct result<This(A0,A0,A2)>
    {
      typedef typename meta::strip<A0>::type                       nA0;
      typedef typename meta::strip<A2>::type                       nA2;
      typedef boost::fusion::tuple<nA0,nA0,nA2>                   type;
    };

    NT2_FUNCTOR_CALL(3)
    {
      //      typedef boost::mpl::vector<ascending_, descending_> tags;
      typedef typename NT2_CALL_RETURN_TYPE(3)::type r_t;
      r_t res;
      eval( a0, a1, a2 
	    , boost::fusion::at_c<0>(res)
	    , boost::fusion::at_c<1>(res)
	    , boost::fusion::at_c<2>(res)
	    );
      return res;
    }
  private:
    template<class A0,class A2,class R0,class R1> inline void
    eval(A0 const& a0, A0 const& a1, A2 const& a2, R0& r0, R1& r1, A2& modified)const
    {
      r0 =  nt2::min(a0, a1);
      r1 =  nt2::max(a0, a1);
      if (a2) {
	A0 t =  r1;
	r1 = r0;
	r0 = t;
      }
      modified = nt2::any(a0-r0); 
    }

  };
} }

#endif
/// Revised by jt the 15/11/2010
