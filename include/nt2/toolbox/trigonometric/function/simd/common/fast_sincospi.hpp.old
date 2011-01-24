//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_FAST_SINCOSPI_HPP_INCLUDED
#define NT2_TOOLBOX_TRIGONOMETRIC_FUNCTION_SIMD_COMMON_FAST_SINCOSPI_HPP_INCLUDED
#include <nt2/sdk/meta/adapted_traits.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/toolbox/trigonometric/function/simd/common/impl/trigo.hpp>


namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<fast_sincospi_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      meta::is_real_convertible<A0>{};
  };
  /////////////////////////////////////////////////////////////////////////////
  // Compute fast_sincospi(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type  is fundamental_
  /////////////////////////////////////////////////////////////////////////////
  template<class Extension, class Info>
  struct call<fast_sincospi_,tag::simd_(tag::arithmetic_,Extension),fundamental_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
      {
	typedef typename meta::as_real<A0>::type  rtype; 
	typedef boost::fusion::tuple<rtype, rtype> type;
      };

      NT2_FUNCTOR_CALL(1)
      {
	typedef typename NT2_CALL_RETURN_TYPE(1)::type rtype;
	rtype res;
	typedef typename  boost::fusion::result_of::value_at_c<rtype,0>::type type; 
	impl::trig_base < type,pi_tag
	  , fast_tag, tag::simd_type
	  >::sincosa( a0
		      , boost::fusion::at_c<0>(res)
		      , boost::fusion::at_c<1>(res)
		      );
      return res;
    }

  };
} }

#endif
/// Revised by jt the 15/11/2010
