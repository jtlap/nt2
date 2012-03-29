//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SIMD_TRANSFORM_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SIMD_TRANSFORM_HPP_INCLUDED

#include <nt2/core/functions/transform.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/core/container/table/table.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/fusion/include/vector_tie.hpp>
#include <boost/fusion/include/pop_front.hpp>
#include <nt2/core/utility/position/alignment.hpp>

namespace nt2 { namespace ext
{
  // nD element-wise operation
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::transform_, boost::simd::tag::simd_
                            , (A0)(A1)(S1)(T1)(N1)
                            , (ast_<A0>)
                              ((expr_< table_< unspecified_<A1>, S1 >
                                     , T1
                                     , N1
                                     >
                              ))
                            )
  {
    typedef void                                             result_type;

    typedef typename meta::
            strip< typename meta::
                   scalar_of<A0>::type
                 >::type                                    stype;

    typedef boost::simd::native<stype, BOOST_SIMD_DEFAULT_EXTENSION>
                                                            target_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1) const
    {
      typename A0::extent_type e = a0.extent();
      static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;

      std::size_t in_sz     = boost::fusion::at_c<0>(e);
      std::size_t in_sz_bnd = (in_sz/N)*N;
      std::size_t outer_sz  = nt2::numel(boost::fusion::pop_front(e));

      std::size_t  it = 0;

      for(std::size_t j=0; j < outer_sz; ++j)
      {
        for(std::size_t i=0; i < in_sz_bnd; i+=N, it+=N)
          nt2::run(a0, it, nt2::run(a1, it, meta::as_<target_type>()));

        for(std::size_t i=in_sz_bnd; i < in_sz; ++i, ++it)
          nt2::run(a0, it, nt2::run(a1, it, meta::as_<stype>()));
      }
    }
  };

  // 1D element-wise operation
  NT2_FUNCTOR_IMPLEMENTATION_TPL( nt2::tag::transform_, boost::simd::tag::simd_
                            , (class A0)(class A1)(class Shape)(class StorageKind)(std::ptrdiff_t Sz)(class T1)(class N1)
                            , (ast_<A0>)
                              ((expr_< table_< unspecified_<A1>, nt2::settings(nt2::of_size_<Sz>, Shape, StorageKind)>
                                     , T1
                                     , N1
                                     >
                              ))
                            )
  {
    typedef void                                            result_type;

    typedef typename meta::
            strip< typename meta::
                   scalar_of<A0>::type
                 >::type                                    stype;

    typedef boost::simd::native<stype, BOOST_SIMD_DEFAULT_EXTENSION>
                                                            target_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, A1& a1) const
    {
      static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;

      std::size_t bound          = boost::fusion::at_c<0>(a0.extent());
      std::size_t aligned_bound  = (bound/N)*N;
      std::size_t i;

      for(i=0;i < aligned_bound; i+=N)
        nt2::run(a0, i, nt2::run(a1, i, meta::as_<target_type>()));

      for(i; i<bound; ++i)
        nt2::run(a0, i, nt2::run(a1, i, meta::as_<stype>()));
    }
  };
} }

#endif
