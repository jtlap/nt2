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
#include <boost/simd/toolbox/operator/functions/simd/common/details/details_load_store.hpp>
#include <boost/simd/sdk/meta/iterate.hpp>
#include <boost/simd/include/functions/simd/insert.hpp>
#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/simd/include/functions/simd/sb2b.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost { namespace simd { namespace ext
{
  // scalar emulation
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_store_, tag::cpu_
                            , (A0)(A1)(A2)(X)
                            , ((simd_< fundamental_<A0>, X >))
                              (iterator_<scalar_< fundamental_<A1> > >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef A0 const& result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2& a2) const
    {
      for(std::size_t i=0; i!=meta::cardinal_of<result_type>::value; ++i)
         a1[a2+i] = a0[i];
      return a0;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_store_, tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_< fundamental_<A0>, X >))
                              (iterator_<scalar_< fundamental_<A1> > >)
                            )
  {
    typedef A0 const& result_type;
    inline result_type operator()(const A0& a0, const A1& a1) const
    {
      for(std::size_t i=0; i!=meta::cardinal_of<result_type>::value; ++i)
         a1[i] = a0[i];
      return a0;
    }
  };

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

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_store_ , tag::cpu_
                            , (A0)(A1)(X)
                            , ((simd_< arithmetic_<A0>, X >))
                              (iterator_< scalar_< arithmetic_<A1> > >)
                            )
  {
    typedef A0 const& result_type;
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return *reinterpret_cast<A0*>(a1) = a0;
    }
  };

  // logical
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_store_, tag::cpu_
                            , (A0)(A1)(A2)(X)
                            , ((simd_< logical_<A0>, X >))
                              (iterator_<scalar_< logical_<A1> > >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef A0 const& result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2& a2) const
    {
      unaligned_store(sb2b(a0), a1, a2);
      return a0;
    }
  };

  // scatter
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::unaligned_store_, tag::cpu_
                            , (A0)(A1)(A2)(X)(Y)
                            , (mpl::equal_to< boost::simd::meta::cardinal_of<A0>
                                            , boost::simd::meta::cardinal_of<A2>
                                            >
                              )
                            , ((simd_< fundamental_<A0>, X >))
                              (iterator_< scalar_< fundamental_<A1> > >)
                              ((simd_< integer_<A2>, Y >))
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
  
  // fusion sequence
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_store_, tag::cpu_
                                   , (A0)(A1)(A2)(X)
                                   , ((simd_< fusion_sequence_<A0>, X >))
                                     (fusion_sequence_<A1>)
                                     (scalar_< integer_<A2> >)
                                   )
  {
    typedef A0 result_type;

    inline result_type operator()(const A0& a0, const A1& a1, const A2& a2) const
    { 
      static const int N = fusion::result_of::size<A1>::type::value;
      meta::iterate<N>( details::storer< boost::simd::tag::unaligned_store_
                                       , A0
                                       , A1
                                       , A2
                                       >(a0, a1, a2)
                      );
      return a0;
    }
  };

} } }


#endif
