//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_COMMON_GROUP_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_COMMON_GROUP_HPP_INCLUDED
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/include/functions/load.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is downgradable
/////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION_IF( tag::group_, tag::cpu_,
                          (A0)(X),
                          (boost::mpl::not_< boost::is_same<A0, typename meta::downgrade<A0>::type> >),
                          (tag::group_(tag::simd_<tag::arithmetic_,X>
                                      ,tag::simd_<tag::arithmetic_,X>
                                      )
                          ), 
                          ((simd_<arithmetic_<A0>,X>))((simd_<arithmetic_<A0>,X>))
                        )
  {
    
    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      typedef result_type rtype;
      
      static const int size = meta::cardinal_of<A0>::value;
      NT2_ALIGNED_TYPE(typename meta::scalar_of<rtype>::type) tmp[size*2];
      
      for(int i = 0; i != size; ++i)
        tmp[i] = a0[i];
      for(int i = 0; i != size; ++i)
        tmp[i+size] = a1[i];
        
      return load<rtype>(&tmp[0], 0);
    }
  };
} }
#endif
