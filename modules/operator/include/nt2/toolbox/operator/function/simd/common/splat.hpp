//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_COMMON_SPLAT_HPP_INCLUDED
#define NT2_TOOLBOX_OPERATOR_FUNCTION_SIMD_COMMON_SPLAT_HPP_INCLUDED

#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/simd/category.hpp>
#include <nt2/sdk/functor/preprocessor/call.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <nt2/include/functions/load.hpp>

namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( tag::splat_, tag::cpu_
                            , (A0)(A1)(X)
                            , (unspecified_<A0>)
                              ((target_< simd_< unspecified_<A1>, X > >))
                            )
  {
    typedef typename A1::type result_type;

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename meta::scalar_of<result_type>::type sA1;
      
      NT2_ALIGNED_TYPE(sA1) tmp[meta::cardinal_of<result_type>::value];
      for(int i = 0; i != meta::cardinal_of<result_type>::value; ++i)
        tmp[i] = a0;
      
      return load<result_type>(&tmp[0], 0);
    }
  };
} }


#endif
