//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_COMMON_MAKE_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_COMMON_MAKE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// make for SIMD types
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/include/functions/load.hpp>

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::make_, tag::cpu_, (A0)(X)
                            , ((target_< simd_< arithmetic_<A0>, X > >))
                            )
  {
    typedef simd::native<A0, X> result_type;
    #define M0(z,n,t)                                                 \
    NT2_FUNCTOR_CALL_REPEAT(n)                                        \
    {                                                                 \
      NT2_ALIGNED_TYPE(A0) tmp[n] = {  BOOST_PP_ENUM_PARAMS(n, a)  }; \
      return load<simd::native<A0, X> >(&tmp[0], 0);                  \
    }
    
    NT2_PP_REPEAT_POWER_OF_2(M0, ~)
    #undef M0
  };
} }

#endif
