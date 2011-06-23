//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_SSE4_1_SELECT_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_SSE_SSE4_1_SELECT_HPP_INCLUDED
#include <nt2/sdk/meta/strip.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type  is arithmetic_
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::select_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                              ((simd_<arithmetic_<A1>,X>))
                              ((simd_<arithmetic_<A1>,X>))
                            )
  {
    typedef A1 result_type;

    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      return simd::native_cast<A1>(_mm_blendv_epi8( a2, a1
                                                  , simd::native_cast<A1>(a0)
                                                  )
                                  );
    }
  };
} }


namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::select_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                              ((simd_<float_<A1>,X>))
                              ((simd_<float_<A1>,X>))
                            )
  {
    typedef A1 result_type;

    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      return simd::native_cast<A1>(_mm_blendv_ps(a2, a1, simd::native_cast<A1>(a0))); 
    }
  };
} }

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::select_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_<arithmetic_<A0>,X>))
                              ((simd_<double_<A1>,X>))
                              ((simd_<double_<A1>,X>))
                            )
  {
    typedef A1 result_type;

    inline result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      return simd::native_cast<A1>(_mm_blendv_pd(a2, a1, simd::native_cast<A1>(a0))); 
    }
  };
} }

#endif
