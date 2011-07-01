//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_VMX_ALTIVEC_SPLAT_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_VMX_ALTIVEC_SPLAT_HPP_INCLUDED

#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::splat_, tag::cpu_, (A0)(A1)
                            , (scalar_< fundamental_<A0> >)
                              ((target_<simd_<arithmetic_<A1>,tag::altivec_> >))
                            )
  {
    typedef typename A1::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typename result_type::extraction_type v;
      v.s[0] = a0;
      result_type that = {vec_splat(v.v, 0)};
      return that;
    }
  };
} }

#endif
