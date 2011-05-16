//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_SWAR_FUNCTION_SIMD_COMMON_SPLIT_HPP_INCLUDED
#define NT2_TOOLBOX_SWAR_FUNCTION_SIMD_COMMON_SPLIT_HPP_INCLUDED

#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/memory/load.hpp>
#include <nt2/sdk/memory/aligned_type.hpp>
#include <boost/fusion/tuple.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is upgradeable
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH_IF( tag::split_, tag::cpu_,
                          (A0)(X),
                          (boost::mpl::not_< boost::is_same<A0, typename meta::upgrade<A0>::type> >),
                          (tag::split_(tag::simd_<tag::arithmetic_,X>)), 
                          ((simd_<arithmetic_<A0>,X>))
                        );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::split_(tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename meta::upgrade<A0>::type rtype;
      typedef boost::fusion::tuple<rtype, rtype> type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::upgrade<A0>::type rtype;
      
      static const int size = meta::cardinal_of<A0>::value;
      NT2_ALIGNED_TYPE(typename meta::scalar_of<rtype>::type) tmp1[size/2];
      NT2_ALIGNED_TYPE(typename meta::scalar_of<rtype>::type) tmp2[size/2];
      
      for(int i = 0; i != size/2; ++i)
        tmp1[i] = a0[i];
      for(int i = 0; i != size/2; ++i)
        tmp2[i] = a0[i+size/2];
        
      return boost::fusion::make_tuple(
        load<rtype>(&tmp1[0], 0),
        load<rtype>(&tmp2[0], 0)
      );
    }
  };
} }

#endif
