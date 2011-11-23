//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_OPTIMIZE_BITWISE_ORNOT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_FUNCTIONS_OPTIMIZE_BITWISE_ORNOT_HPP_INCLUDED

#include <boost/simd/toolbox/bitwise/functions/bitwise_ornot.hpp>
#include <boost/simd/toolbox/operator/functions/bitwise_or.hpp>
#include <boost/simd/toolbox/operator/functions/complement.hpp>
#include <boost/simd/dsl/functions/optimize.hpp>
#include <boost/dispatch/dsl/category.hpp>
#include <boost/dispatch/functor/meta/call.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::bitwise_or_
                                    , boost::simd::tag::optimize_
                                    , (A0)(A1)(Domain)(Arity)
                                    , (unspecified_<A0>)
                                      ((expr_ < unspecified_<A1>
                                              , Domain
                                              , boost::simd::tag::complement_
                                              , Arity
                                              >
                                      ))
                                    )
  {
    typedef typename dispatch::meta::call< boost::simd::tag::bitwise_ornot_(
          A0 const&,
          typename boost::proto::result_of::child_c<A1, 0>::type const&
        ) >::type result_type; 

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return bitwise_ornot(a0, boost::proto::child_c<0>(a1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::bitwise_or_
                                    , boost::simd::tag::optimize_
                                    , (A0)(A1)(Domain)(Arity)
                                    , ((expr_ < unspecified_<A0>
                                              , Domain
                                              , boost::simd::tag::complement_
                                              , Arity
                                              >
                                      ))
                                      (unspecified_<A1>)
                            )
  {
    typedef typename dispatch::meta::call< boost::simd::tag::bitwise_ornot_(
          A1 const&,
          typename boost::proto::result_of::child_c<A0, 0>::type const&
        ) >::type result_type; 

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return bitwise_ornot(a1, boost::proto::child_c<0>(a0));
    }
  };
} } }

#endif
