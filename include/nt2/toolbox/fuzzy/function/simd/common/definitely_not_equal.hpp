//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_FUZZY_FUNCTION_SIMD_COMMON_DEFINITELY_NOT_EQUAL_HPP_INCLUDED
#define NT2_TOOLBOX_FUZZY_FUNCTION_SIMD_COMMON_DEFINITELY_NOT_EQUAL_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/is_ord.hpp>
#include <nt2/include/functions/successor.hpp>
#include <nt2/include/functions/dist.hpp>
#include <nt2/include/functions/is_finite.hpp>
#include <nt2/include/functions/predecessor.hpp>
#include <nt2/include/functions/abs.hpp>


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<definitely_not_equal_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A0,A1)> :
      meta::is_integral<A1>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute definitely_not_equal(const A0& a0, const A0& a1, const A0& a2)
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension,class Info>
  struct call<definitely_not_equal_,
              tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A0,A1)>
      : meta::strip<A0>{};//

    NT2_FUNCTOR_CALL_DISPATCH(
      3,
      typename nt2::meta::scalar_of<A0>::type,
      (2, (real_,arithmetic_))
    )
      
    NT2_FUNCTOR_CALL_EVAL_IF(3,       real_)
    {
      return b_and(
		   isord(a0, a1),
		   b_and(
			 b_and(
			       isfin(a0+a1),
			       b_or(
				    isgt(a0, successor(a1, a2)),
				    islt(a0, predecessor(a1,a2))
				    )
			       ),
			 isneq(a0, a1)
			 )
		   );
    }
    NT2_FUNCTOR_CALL_EVAL_IF(3,       arithmetic_)
    {
      return isgt(dist(a0, a1), abs(a2));
    }
  };
} }

      
#endif
