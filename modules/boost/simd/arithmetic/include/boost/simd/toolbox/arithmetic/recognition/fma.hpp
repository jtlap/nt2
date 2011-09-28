/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_TOOLBOX_ARITHMETIC_RECOGNITION_FMA_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_ARITHMETIC_RECOGNITION_FMA_HPP_INCLUDED

#include <boost/dispatch/dsl/category.hpp>
#include <boost/simd/sdk/dsl/recognition.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/toolbox/arithmetic/functions/fma.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::plus_ , boost::simd::tag::recognition_, (A0)(A1)(Dom)
                                   , ((expr_< unspecified_<A0>,Dom,boost::simd::tag::multiplies_>))(unspecified_<A1>)
                                   )
  {
    typedef typename dispatch::meta::call< boost::simd::tag::fma_(
          typename boost::proto::result_of::child_c<A0, 0>::type,
          typename boost::proto::result_of::child_c<A0, 1>::type,
          A1
        ) >::type result_type; 
  
    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return fma(boost::proto::child_c<0>(a0), boost::proto::child_c<1>(a0), a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::plus_ , boost::simd::tag::recognition_, (A0)(A1)(Dom)
                                   , (unspecified_<A0>)((expr_< unspecified_<A1>,Dom,boost::simd::tag::multiplies_>))
                                   )
  {
    typedef typename dispatch::meta::call< boost::simd::tag::fma_(
          typename boost::proto::result_of::child_c<A1, 0>::type,
          typename boost::proto::result_of::child_c<A1, 1>::type,
          A0
        ) >::type result_type; 

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return fma(boost::proto::child_c<0>(a1), boost::proto::child_c<1>(a1), a0);
    }
  };
} } }

#endif
