//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_OPTIMIZE_FMA_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_FUNCTIONS_OPTIMIZE_FMA_HPP_INCLUDED

#include <boost/simd/toolbox/arithmetic/functions/fma.hpp>
#include <boost/simd/toolbox/operator/functions/plus.hpp>
#include <boost/simd/toolbox/operator/functions/multiplies.hpp>
#include <boost/simd/dsl/functions/optimize.hpp>
#include <boost/dispatch/dsl/category.hpp>
#include <boost/dispatch/functor/meta/call.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::plus_
                                    , boost::simd::tag::optimize_
                                    , (A0)(A1)(Domain)(Arity)
                                    , ((expr_ < unspecified_<A0>
                                              , Domain
                                              , boost::simd::tag::multiplies_
                                              , Arity
                                              >
                                      ))
                                      (unspecified_<A1>)
                                   )
  {
    typedef typename dispatch::meta::call< boost::simd::tag::fma_(
          typename boost::proto::result_of::child_c<A0, 0>::type const&,
          typename boost::proto::result_of::child_c<A0, 1>::type const&,
          A1 const&
        ) >::type result_type; 
  
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return fma(boost::proto::child_c<0>(a0), boost::proto::child_c<1>(a0), a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::plus_
                                    , boost::simd::tag::optimize_
                                    , (A0)(A1)(Domain)(Arity)
                                    , (unspecified_<A0>)
                                      ((expr_ < unspecified_<A1>
                                              , Domain
                                              , boost::simd::tag::multiplies_
                                              , Arity
                                              >
                                      ))
                                    )
  {
    typedef typename dispatch::meta::call< boost::simd::tag::fma_(
          typename boost::proto::result_of::child_c<A1, 0>::type const&,
          typename boost::proto::result_of::child_c<A1, 1>::type const&,
          A0 const&
        ) >::type result_type; 

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return fma(boost::proto::child_c<0>(a1), boost::proto::child_c<1>(a1), a0);
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::plus_ , boost::simd::tag::optimize_, (A0)(A1)(Dom)
                                   , ((expr_< unspecified_<A0>,Dom,boost::simd::tag::multiplies_>))((expr_< unspecified_<A1>,Dom,boost::simd::tag::multiplies_>))
                                   )
  {
    typedef typename dispatch::meta::call< boost::simd::tag::fma_(
          typename boost::proto::result_of::child_c<A0, 0>::type const&,
          typename boost::proto::result_of::child_c<A0, 1>::type const&,
          A1 const&
        ) >::type result_type; 
  
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return fma(boost::proto::child_c<0>(a0), boost::proto::child_c<1>(a0), a1);
    }
  };
} } }

#endif
