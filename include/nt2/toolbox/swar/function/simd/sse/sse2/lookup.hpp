//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_LOOKUP_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_LOOKUP_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/meta/size.hpp>
#include <nt2/sdk/meta/strip.hpp>

#include <nt2/include/functions/at.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/include/functions/store.hpp>

namespace nt2 { namespace functors
{
  template<class Extension,class Info>
  struct validate<lookup_,tag::simd_(tag::arithmetic_,Extension),Info>

    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> :
      boost::mpl::and_<meta::is_integral<A1>, 
		       meta::has_same_size<A0, A1, meta::scalar_of < boost::mpl::_> >
      > {}; 
  };    
  template<class Extension,class Info>
  struct call<lookup_,tag::simd_(tag::arithmetic_,Extension),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)>
      : meta::strip<A0>{};//
    
    NT2_FUNCTOR_CALL_DISPATCH(
      2,
      typename nt2::meta::scalar_of<A0>::type,
      (2, (               types64_, arithmetic_))   
    )
      
#define NT2_SH(a, b, c, d) (_MM_SHUFFLE(d, c, b, a))
#define NT2_SH2(a, b)(_MM_SHUFFLE2(b, a))     
    //     NT2_FUNCTOR_CALL_EVAL_IF(2,       float)
    //     {
    //       int i = NT2_SH(at<0>(a1),at<1>(a1),at<2>(a1),at<3>(a1));
    //       switch(i & 0xFF)
    // 	{
    // 	  NT2_CASE_256( A0, _mm_shuffle_ps, a0, a0);
    // 	}
    //     }
    //     NT2_FUNCTOR_CALL_EVAL_IF(2,       int32_)
    //     {
    //       typedef typename meta::as_integer < A0, signed>::type int_type; 
    //       const int32_t i = NT2_SH(at<0>(a1),at<1>(a1),at<2>(a1),at<3>(a1))&0xFF;
    //       switch(i)
    // 	{
    // 	  NT2_CASE_256( A0, _mm_shuffle_epi32, simd::native_cast<int_type>(a0));
    // 	}
    //     }
    NT2_FUNCTOR_CALL_EVAL_IF(2,       types64_)
    {
      typedef typename meta::as_real<A0>::type real_type; 
      const int32_t i =  NT2_SH2(at<0>(a1), at<1>(a1))&0x3;
      //            std::cout << "---- " << i << std::endl; 
      switch(i)
	{
	  NT2_CASE_4( A0, _mm_shuffle_pd, simd::native_cast<real_type>(a0), simd::native_cast<real_type>(a0));
	}
    }
#undef NT2_SH
#undef NT2_SH2

    NT2_FUNCTOR_CALL_EVAL_IF(2,       arithmetic_)
    {
      typedef typename meta::scalar_of<A0>::type sA0; 
      aligned::array < sA0,meta::cardinal_of<A0>::value,16/*NT2_SIMD_BYTE*/ > tmp, tmp1;
      nt2::store<A0>(a0, tmp.begin(), 0); 
      
      for(int i=0; i < meta::cardinal_of<A0>::value; i++) { tmp1[i] = tmp[a1[i]]; }// TODO unroll
      return nt2::load<A0>(tmp1.begin(), 0); 
    }
  };
} }

#endif