//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_COMMON_GROUP_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_COMMON_GROUP_HPP_INCLUDED

#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/memory/load.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is downgradable
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH_IF( tag::group_, tag::cpu_,
                          (A0)(X),
                          (boost::mpl::not_< boost::is_same<A0, typename meta::downgrade<A0>::type> >),
                          (tag::group_(tag::simd_<tag::arithmetic_,X>
                                      ,tag::simd_<tag::arithmetic_,X>
                                      )
                          ), 
                          ((simd_<arithmetic_<A0>,X>))((simd_<arithmetic_<A0>,X>))
                        );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::group_(tag::simd_<tag::arithmetic_, X> ,
                          tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0, A0)> : meta::downgrade<A0>
    {
    };

    NT2_FUNCTOR_CALL(2)
    {
      typedef typename NT2_RETURN_TYPE(2)::type rtype;
      
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
