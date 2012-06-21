//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_MULTIPLIES_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_MULTIPLIES_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

#include <boost/simd/toolbox/operator/functions/multiplies.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/dispatch/meta/upgrade.hpp>
#include <boost/simd/include/constants/digits.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::multiplies_, boost::simd::tag::altivec_, (A0)
                            , ((simd_<single_<A0>,boost::simd::tag::altivec_>))
                              ((simd_<single_<A0>,boost::simd::tag::altivec_>))
                            )
  {
    typedef A0 result_type;

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = vec_madd(a0(),a1(),Zero<A0>()());
      return that;
    }
  };


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::multiplies_, boost::simd::tag::altivec_, (A0)
                            , ((simd_<type16_<A0>,boost::simd::tag::altivec_>))
                              ((simd_<type16_<A0>,boost::simd::tag::altivec_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      A0 that = vec_mladd(a0(),a1(),Zero<A0>()());
      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::multiplies_, boost::simd::tag::altivec_, (A0)
                            , ((simd_<type8_<A0>,boost::simd::tag::altivec_>))
                              ((simd_<type8_<A0>,boost::simd::tag::altivec_>))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::upgrade<A0>::type uptype;
      uptype l = vec_mule(a0(),a1());
      uptype r = vec_mulo(a0(),a1());
      A0 that  = vec_mergel(vec_pack(l(),l()),vec_pack(r(),r()));
      return that;
    }
  };

/*
 * TODO : FINISH THIS
    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2,int32_t )
    {
      static inline type_t Multiply( const type_t& a, const type_t& b, const ttt::boxed<2>&, const true_t&  )
      {
        typedef __vu32_4 cast_t;
        type_t r  = type_t( av_multiply<__vu32_4>::Multiply(cast_t(a),cast_t(b), ttt::boxed<2>(), false_t()) );
        return vec_sel(r,vec_sub(vec_splat_u32(0), r),vec_cmpgt(vec_splat_u32(0), vec_xor(a, b)));
      }
    }

    BOOST_SIMD_FUNCTOR_CALL_REPEAT(2,uint32_t )
    {

      static inline type_t Multiply( const type_t& a, const type_t& b, const ttt::boxed<2>&, const false_t&  )
      {
        typedef __vu16_8 short_t;
        type_t sixteen = type_t(vec_vspltisw (-16));
        type_t low = vec_mulo (short_t(a),short_t(b));
        type_t high = vec_msum (short_t(a),short_t(vec_rl(b, sixteen)),vec_splat_u32(0));
        return vec_add(vec_sl(high, sixteen),low);
      }

*/
} } }

#endif
#endif
