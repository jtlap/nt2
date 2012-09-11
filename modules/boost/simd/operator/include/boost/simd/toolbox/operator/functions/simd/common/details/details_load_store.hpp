//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_DETAILS_DETAILS_LOAD_STORE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_DETAILS_DETAILS_LOAD_STORE_HPP_INCLUDED

#include <boost/dispatch/functor/meta/make_functor.hpp>
#include <boost/dispatch/meta/as.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/fusion/include/value_at.hpp>


////////////////////////////////////////////////////////////////////////////////
// Helpers for load and store over a fusion sequence.
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace simd { namespace details
{
  template<class Tag, class A0, class A1, class A2>
  struct loader
  {
    loader(A0 const& a0_, A1 const& a1_, A2& a2_)
    : a0(a0_), a1(a1_), a2(a2_)
    {}

    template<int I>
    void operator()() const
    {
      typename dispatch::
      make_functor< Tag
                  , typename fusion::result_of::value_at_c<A0,I>::type
                  >::type callee;
      fusion::at_c<I>(a2) = callee( fusion::at_c<I>(a0)
                                  , a1
                                  , dispatch::meta::as_<typename fusion::result_of::value_at_c<A2,I>::type>());
    }

    A0 const& a0;
    A1 const& a1;
    A2 &      a2;
  };

  template<class Tag, class A0, class A1, class A2>
  struct storer
  {
    storer(A0 const& a0_, A1 const& a1_, A2 const& a2_)
    : a0(a0_), a1(a1_), a2(a2_)
    {}

    template<int I>
    void operator()() const
    {
      typename dispatch::
      make_functor< Tag
                  , typename fusion::result_of::value_at_c<A0,I>::type
                  >::type callee;
      callee( fusion::at_c<I>(a0)
            , fusion::at_c<I>(a1)
            , a2
            );
    }

    A0 const& a0;
    A1 const& a1;
    A2 const& a2;
  };

} } }

#endif
