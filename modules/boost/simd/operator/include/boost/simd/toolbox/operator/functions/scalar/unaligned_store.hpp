//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SCALAR_UNALIGNED_STORE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SCALAR_UNALIGNED_STORE_HPP_INCLUDED

#include <boost/simd/toolbox/operator/functions/unaligned_store.hpp>
#include <boost/simd/toolbox/operator/functions/simd/common/details/details_load_store.hpp>
#include <boost/simd/sdk/meta/iterate.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/simd/sdk/memory/iterator.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_store_, tag::cpu_, (A0)(A1)(A2)
                            , (unspecified_<A0>)
                              (iterator_< unspecified_<A1> >)
                              (scalar_< integer_<A2> >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(3)
    {
      A1 that = a1;
      std::advance(that,a2);
      return *that = a0;
    }
  };
} } }

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_store_, tag::cpu_, (A0)(A1)(A2)(A3)
                            , (unspecified_<A0>)
                              (iterator_< unspecified_<A1> >)
                              (scalar_< integer_<A2> >)
                              (mpl_integral_< scalar_<integer_<A3> > >)
                            )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(3)
    {
      A1 that = a1;
      std::advance(that,a2+A3::value);
      return *that = a0;
    }
  };

  // fusion sequence
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_store_, tag::cpu_
                                   , (A0)(A1)(A2)
                                   , (fusion_sequence_<A0>)
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
