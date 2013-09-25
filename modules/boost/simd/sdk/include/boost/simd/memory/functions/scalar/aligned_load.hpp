//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SCALAR_ALIGNED_LOAD_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SCALAR_ALIGNED_LOAD_HPP_INCLUDED

#include <boost/simd/memory/functions/aligned_load.hpp>
#include <boost/simd/memory/functions/scalar/load.hpp>
#include <boost/simd/sdk/functor/preprocessor/call.hpp>
#include <boost/simd/memory/iterator_category.hpp>
#include <boost/simd/sdk/functor/hierarchy.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/simd/meta/is_pointing_to.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - Regular scalar load with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::aligned_load_ , tag::cpu_
                                      , (A0)(A1)(A2)
                                      , ( simd::meta::is_pointing_to
                                          < A0
                                          , typename A2::type
                                          >
                                        )
                                      , (iterator_< unspecified_<A0> >)
                                        (scalar_< integer_<A1> >)
                                        (target_< unspecified_<A2> >)
                                      )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, A1 a1, A2 const&) const { return *(a0+a1); }
  };

  /// INTERNAL ONLY - Regular scalar load without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::aligned_load_ , tag::cpu_
                                      , (A0)(A2)
                                      , ( simd::meta::is_pointing_to
                                          < A0
                                          , typename A2::type
                                          >
                                        )
                                      , (iterator_< unspecified_<A0> >)
                                        (target_< unspecified_<A2> >)
                                      )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, A2 const&) const { return *a0; }
  };

  /// INTERNAL ONLY - scalar load with misalignment and offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::aligned_load_ , tag::cpu_
                                      , (A0)(A1)(A2)(A3)
                                      , ( simd::meta::is_pointing_to
                                          < A0
                                          , typename A2::type
                                          >
                                        )
                                      , (iterator_< unspecified_<A0> >)
                                        (scalar_< integer_<A1> >)
                                        (target_< scalar_< unspecified_<A2> > >)
                                        (mpl_integral_< scalar_< integer_<A3> > >)
                                      )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, A1 a1, A2 const&, A3 const&) const { return *(a0+a1); }
  };

  /// INTERNAL ONLY - scalar load with misalignment and without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::aligned_load_
                                      , tag::cpu_
                                      , (A0)(A2)(A3)
                                      , ( simd::meta::is_pointing_to
                                          < A0
                                          , typename A2::type
                                          >
                                        )
                                      , (iterator_< unspecified_<A0> >)
                                        (target_< unspecified_<A2> >)
                                        (mpl_integral_< scalar_< integer_<A3> > >)
                                      )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 a0, A2 const&, A3 const&) const { return *a0; }
  };

  /// INTERNAL ONLY - Scalar FusionSequence load with offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_, tag::cpu_
                                    , (A0)(A1)(A2)
                                    , (fusion_sequence_<A0>)
                                      (generic_< integer_<A1> >)
                                      ((target_< fusion_sequence_<A2> >))
                                    )
  {
    BOOST_DISPATCH_RETURNS_ARGS ( 3
                                , (A0 const& a0, A1 const& a1, A2 const& a2)
                                , (A0 const& a0, A1 a1, A2 const& )
                                , boost::simd::load<typename A2::type>(a0,a1)
                                );
  };

  /// INTERNAL ONLY - Scalar FusionSequence load without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_, tag::cpu_
                                    , (A0)(A2)
                                    , (fusion_sequence_<A0>)
                                      ((target_< fusion_sequence_<A2> >))
                                    )
  {
    BOOST_DISPATCH_RETURNS_ARGS ( 2
                                , (A0 const& a0, A2 const& a2)
                                , (A0 const& a0, A2 const& )
                                , boost::simd::load<typename A2::type>(a0)
                                );
  };
} } }

#endif
