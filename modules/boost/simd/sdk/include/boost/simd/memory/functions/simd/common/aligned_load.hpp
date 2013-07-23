//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_COMMON_ALIGNED_LOAD_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_COMMON_ALIGNED_LOAD_HPP_INCLUDED

#include <boost/simd/memory/functions/aligned_load.hpp>
#include <boost/simd/include/functions/simd/load.hpp>
#include <boost/simd/memory/functions/details/load.hpp>
#include <boost/simd/memory/functions/details/check_ptr.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>
#include <boost/simd/meta/is_pointing_to.hpp>
#include <boost/dispatch/functor/preprocessor/dispatch.hpp>
#include <boost/simd/sdk/functor/hierarchy.hpp>
#include <boost/simd/sdk/meta/iterate.hpp>
#include <boost/simd/memory/iterator_category.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - Regular SIMD load with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::aligned_load_, tag::cpu_
                                      , (A0)(A1)(A2)(X)
                                      , ( simd::meta::is_pointing_to
                                          < A0
                                          , typename simd::meta::scalar_of<typename A2::type>::type
                                          >
                                        )
                                      , (iterator_<unspecified_<A0> >)
                                        (scalar_< integer_<A1> >)
                                        ((target_< simd_<unspecified_<A2>,X> >))
                                      )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0,A1 a1,const A2&) const
    {
      return aligned_load<result_type>(a0+a1);
    }
  };

  /// INTERNAL ONLY - Regular SIMD load without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::aligned_load_
                                      , tag::cpu_
                                      , (A0)(A2)(X)
                                      , ( simd::meta::is_pointing_to
                                          < A0
                                          , typename simd::meta::scalar_of<typename A2::type>::type
                                          >
                                        )
                                      , (iterator_< scalar_<arithmetic_<A0> > >)
                                        ((target_< simd_<arithmetic_<A2>,X> >))
                                      )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0,const A2&) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a0, sizeof(result_type));
      return load<result_type>(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::aligned_load_
                                      , tag::cpu_
                                      , (A0)(A2)(X)
                                      , ( simd::meta::is_pointing_to
                                          < A0
                                          , typename simd::meta::scalar_of<typename A2::type>::type
                                          >
                                        )
                                      , (iterator_<unspecified_<A0> >)
                                        ((target_< simd_<unspecified_<A2>,X> >))
                                      )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0,const A2&) const
    {
      return load<result_type>(a0);
    }
  };

  /// INTERNAL ONLY - SIMD load with misalignment without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::aligned_load_
                                      , tag::cpu_
                                      , (A0)(A2)(A3)(X)
                                      , ( simd::meta::is_pointing_to
                                          < A0
                                          , typename simd::meta::scalar_of<typename A2::type>::type
                                          >
                                        )
                                      , (iterator_<unspecified_<A0> >)
                                        ((target_<simd_< unspecified_<A2>, X > >))
                                        (mpl_integral_< scalar_< integer_<A3> > >)
                                      )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 a0, const A2&, const A3&) const
    {
      return load<result_type>(a0);
    }
  };

  /// INTERNAL ONLY - SIMD load with misalignment without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::aligned_load_
                                      , tag::cpu_
                                      , (A0)(A2)(A3)(X)
                                      , ( simd::meta::is_pointing_to
                                          < A0
                                          , typename simd::meta::scalar_of<typename A2::type>::type
                                          >
                                        )
                                      , (iterator_< scalar_< arithmetic_<A0> > >)
                                        ((target_<simd_< scalar_< arithmetic_<A2> >, X > >))
                                        (mpl_integral_< scalar_< integer_<A3> > >)
                                      )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 a0, const A2&, const A3&) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a0-A3::value, sizeof(result_type));
      return load<result_type>(a0);
    }
  };

  /// INTERNAL ONLY - SIMD load with gather - gather means SIMD offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::aligned_load_, tag::cpu_
                                      , (A0)(A1)(A2)(X)(Y)
                                      , ( mpl::equal_to
                                        < boost::simd::meta
                                               ::cardinal_of<A1>
                                        , boost::simd::meta
                                               ::cardinal_of<typename A2::type>
                                        >
                                        )
                                      , (iterator_< unspecified_<A0> >)
                                        ((simd_< fundamental_<A1>, X >))
                                        ((target_<simd_<unspecified_<A2>,Y> >))
                                      )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, const A1& a1, const A2&) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a0, sizeof(result_type));
      return load<result_type>(a0, a1);
    }
  };

  /// INTERNAL ONLY - SIMD fusion sequence load with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::aligned_load_, tag::cpu_
                                   , (A0)(A1)(A2)(X)
                                   , (fusion_sequence_<A0>)
                                     (generic_< integer_<A1> >)
                                     ((target_<simd_<fusion_sequence_<A2>,X> >))
                                   )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 a0, const A1& a1, const A2&) const
    {
      result_type that;
      meta::iterate < fusion::result_of::size<A0>::type::value>
                    ( details::loader < boost::simd::
                                        tag::aligned_load_(A0, A1, result_type)
                                      >(a0, a1, that)
                    );
      return that;
    }
  };

  /// INTERNAL ONLY - SIMD fusion sequence load without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::aligned_load_, tag::cpu_
                                   , (A0)(A2)(X)
                                   , (fusion_sequence_<A0>)
                                     ((target_<simd_<fusion_sequence_<A2>,X> >))
                                   )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 a0, const A2&) const
    {
      result_type that;
      meta::iterate < fusion::result_of::size<A0>::type::value>
                    ( details::loader < boost::simd::
                                        tag::aligned_load_(A0, result_type)
                                      >(a0, that)
                    );
      return that;
    }
  };

  /// INTERNAL ONLY - Misaligned load with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::aligned_load_, tag::cpu_
                                      , (A0)(A1)(A2)(A3)(X)
                                      , ( simd::meta::is_pointing_to
                                          < A0
                                          , typename A2::type::value_type
                                          >
                                        )
                                      , (iterator_<scalar_< unspecified_<A0> > >)
                                        (scalar_<integer_<A1> >)
                                        ((target_<simd_< unspecified_<A2>, X> >))
                                        (mpl_integral_<scalar_< integer_<A3> > >)
                                      )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, A1 a1, const A2&, const A3&) const
    {
      return boost::simd::aligned_load<result_type,A3::value>( a0+a1 );
    }
  };
} } }

#endif
