//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_UNALIGNED_STORE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_UNALIGNED_STORE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_VMX_SUPPORT

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_store_ , boost::simd::tag::altivec_
                            , (A0)(A1)(A2)
                            , ((simd_< fundamental_<A0>, boost::simd::tag::altivec_ >))
                              (iterator_< scalar_< fundamental_<A1> > >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef A0 result_type;
    typedef native<boost::simd::uint8_t, boost::simd::tag::altivec_> n_t;

    BOOST_SIMD_FUNCTOR_CALL(3)
    {
      result_type   MSQ = {vec_ld(a2*16, a1)};   
      result_type   LSQ = {vec_ld((a2*16)+15, a1)};   
      n_t     edgeAlign = {vec_lvsl(a2*16, a1)};
      result_type edges = {vec_perm(LSQ(), MSQ(), edgeAlign())};
      n_t         align = {vec_lvsr(a2*16, a1)};
      MSQ = vec_perm(edges(), a0(), align());
      LSQ = vec_perm(a0(), edges(), align());
      vec_st(LSQ(), (a2*16)+15, a1);
      vec_st(MSQ(), (a2*16)   , a1);
      return a0;
    }
  };
} } }

#endif
#endif /* BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_VMX_ALTIVEC_UNALIGNED_STORE_HPP_INCLUDED */

