//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_UNALIGNED_STORE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_UNALIGNED_STORE_HPP_INCLUDED

#include <boost/simd/toolbox/operator/functions/unaligned_store.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>

namespace boost { namespace simd { namespace ext
{
  // regular store
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_store_ , tag::cpu_
                            , (A0)(A1)(A2)(X)
                            , ((simd_< arithmetic_<A0>, X >))
                              (iterator_< scalar_< arithmetic_<A1> > >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef A0 const& result_type;
    BOOST_SIMD_FUNCTOR_CALL(3)
    {
      return *reinterpret_cast<A0*>(a1+a2) = a0;
    }
  };
  
  // scatter
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::unaligned_store_, tag::cpu_
                            , (A0)(A1)(A2)(X)
                            , (mpl::equal_to< boost::simd::meta::cardinal_of<A0>
                                            , boost::simd::meta::cardinal_of<A2>
                                            >
                              )
                            , ((simd_< arithmetic_<A0>, X >))
                              (iterator_< scalar_< arithmetic_<A1> > >)
                              ((simd_< integer_<A2>, X >))
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(3)
    {
      for(std::size_t i=0; i<meta::cardinal_of<result_type>::value; ++i)
        a1[a2[i]] = a0[i];
      
      return a0;
    }
  };
  
} } }


#endif
