//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_VMX_ALTIVEC_LOAD_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_VMX_ALTIVEC_LOAD_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Register dispatch over load_ on simd integers
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::load_, tag::cpu_
                            , (A0)(A1)(T)
                            , (iterator_<fundamental_<A0> >)(scalar_< fundamental_<A1> >)((target_< simd_< arithmetic_<T>, tag::altivec_ > >))
                            )
  {

    typedef typename meta::strip<A2>::type::type result_type;

    NT2_FUNCTOR_CALL(3)
    {
      typedef typename NT2_RETURN_TYPE(3)::type type;
      type that = { vec_ld(a1*16,a0) };
      return that;
    }
  };
} }


#include <nt2/toolbox/operator/function/simd/vmx/altivec/load_offset.hpp>

#endif
