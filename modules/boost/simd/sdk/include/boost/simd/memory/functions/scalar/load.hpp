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
#include <boost/simd/sdk/functor/preprocessor/dispatch.hpp>
#include <boost/simd/memory/iterator_category.hpp>
#include <boost/simd/memory/functions/details/load.hpp>
#include <boost/simd/sdk/meta/iterate.hpp>
#include <boost/simd/sdk/simd/meta/is_native.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)
                                    , (iterator_< unspecified_<A0> >)
                                      (scalar_< integer_<A1> >)
                                      (target_< unspecified_<A2> >)
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, A1 a1, A2 const&) const { return *(a0+a1); }
  };

  /// INTERNAL ONLY
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A2)
                                    , (iterator_< unspecified_<A0> >)
                                      (target_< unspecified_<A2> >)
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, A2 const&) const { return *a0; }
  };

  /// INTERNAL ONLY
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A1)(A2)
                                    , (fusion_sequence_<A0>)
                                      (generic_< integer_<A1> >)
                                      ((target_< fusion_sequence_<A2> >))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 const& a1, A2 const&) const
    {
      result_type that;
      meta::iterate < fusion::result_of::size<A0>::type::value>
                    ( details::loader < boost::simd::
                                        tag::load_(A0, A1, result_type)
                                      >(a0, a1, that)
                    );
      return that;
    }
  };

  /// INTERNAL ONLY
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , tag::cpu_
                                    , (A0)(A2)
                                    , (fusion_sequence_<A0>)
                                      ((target_< fusion_sequence_<A2> >))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A2 const&) const
    {
      result_type that;
      meta::iterate < fusion::result_of::size<A0>::type::value>
                    ( details::loader < boost::simd::
                                        tag::load_(A0, result_type)
                                      >(a0, that)
                    );
      return that;
    }
  };

  /// INTERNAL ONLY - Load through pointer of fusion sequence
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::load_
                                      , tag::cpu_
                                      , (A0)(A1)(A2)
                                      , (mpl::not_< simd::meta::is_native<typename A2::type> >)
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

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::load_
                                      , tag::cpu_
                                      , (A0)(A2)
                                      , (mpl::not_< simd::meta::is_native<typename A2::type> >)
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
