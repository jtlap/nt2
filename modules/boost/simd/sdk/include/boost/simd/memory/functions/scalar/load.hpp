//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SCALAR_LOAD_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SCALAR_LOAD_HPP_INCLUDED

#include <boost/simd/memory/functions/load.hpp>
#include <boost/simd/memory/functions/scalar/aligned_load.hpp>
#include <boost/simd/sdk/functor/preprocessor/dispatch.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - Scalar load and load are equivalent
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)
                                    , (iterator_< unspecified_<A0> >)
                                      (scalar_< integer_<A1> >)
                                      (target_< unspecified_<A2> >)
                                    )
  {
    BOOST_DISPATCH_RETURNS( 3
                          , (A0 a0, A1 a1, A2 const& a2)
                          , boost::simd::aligned_load<typename A2::type>(a0,a1)
                          );
  };

  /// INTERNAL ONLY - Scalar load and load are equivalent
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A2)
                                    , (iterator_< unspecified_<A0> >)
                                      (target_< unspecified_<A2> >)
                                    )
  {
    BOOST_DISPATCH_RETURNS( 2
                          , (A0 a0, A2 const& a2)
                          , boost::simd::aligned_load<typename A2::type>(a0)
                          );
  };

  /// INTERNAL ONLY - Scalar load and load are equivalent
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)
                                    , (fusion_sequence_<A0>)
                                      (generic_< integer_<A1> >)
                                      ((target_< fusion_sequence_<A2> >))
                                    )
  {
    BOOST_DISPATCH_RETURNS( 3
                          , (A0 const& a0, A1 const& a1, A2 const& a2)
                          , boost::simd::aligned_load<typename A2::type>(a0,a1)
                          );
  };

  /// INTERNAL ONLY - Scalar load and load are equivalent
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A2)
                                    , (fusion_sequence_<A0>)
                                      ((target_< fusion_sequence_<A2> >))
                                    )
  {
    BOOST_DISPATCH_RETURNS( 2
                          , (A0 const& a0, A2 const& a2)
                          , boost::simd::aligned_load<typename A2::type>(a0)
                          );
  };

  /// INTERNAL ONLY - Load through pointer of fusion sequence
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)
                                    , (iterator_< fusion_sequence_<A0> >)
                                      (scalar_< integer_<A1> >)
                                      (target_< fusion_sequence_<A2> >)
                                    )
  {
    typedef typename A2::type result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&) const
    {
      result_type that;

      static const int N = fusion::result_of::size<result_type>::type::value;
      meta::iterate<N>( details::inserter<A0,result_type,A1>(a0,that,a1) );

      return that;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A2)
                                    , (iterator_< fusion_sequence_<A0> >)
                                      (target_< fusion_sequence_<A2> >)
                                    )
  {
    typedef typename A2::type result_type;
    inline result_type operator()(const A0& a0, const A2&) const
    {
      result_type that;

      static const int N = fusion::result_of::size<result_type>::type::value;
      meta::iterate<N>( details::inserter<A0,result_type>(a0,that) );

      return that;
    }
  };
} } }

#endif
