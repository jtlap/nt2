//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_LOOKUP_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_SSE_SSE2_LOOKUP_HPP_INCLUDED
#include <nt2/sdk/meta/as_real.hpp>
#include <nt2/sdk/meta/size.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::lookup_, tag::cpu_
                            , (A0)(A1)
                            , ((simd_<arithmetic_<A0>,tag::sse_>))((simd_<integer_<A1>,tag::sse_>))
                            )
  {

    typedef typename meta::strip<A0>::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::scalar_of<A0>::type sA0;
      NT2_ALIGNED_TYPE(sA0) tmp[meta::cardinal_of<A0>::value];
      NT2_ALIGNED_TYPE(sA0) tmp1[meta::cardinal_of<A0>::value];
      nt2::store<A0>(a0, &tmp[0], 0);

      for(int i=0; i < meta::cardinal_of<A0>::value; i++) { tmp1[i] = tmp[a1[i]]; }// TODO unroll
      return nt2::load<A0>(&tmp1[0], 0);
    }
  };
} }



#endif
