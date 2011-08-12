/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_TOOLBOX_BITWISE_RECOGNITION_BITWISE_ANDNOT_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_BITWISE_RECOGNITION_BITWISE_ANDNOT_HPP_INCLUDED

#include <boost/dispatch/dsl/category.hpp>
#include <boost/simd/sdk/dsl/recognition.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/simd/toolbox/bitwise/functions/bitwise_andnot.hpp>


namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::bitwise_and_ , boost::simd::tag::recognition_
                            , (A0)(A1)(Dom)(Sema)
                            , (unspecified_<A0>)
                              ((expr_<A1,Dom,boost::simd::tag::complement_,Sema>))
                            )
  {
    typedef typename dispatch::
            meta::call< boost::simd::tag::bitwise_andnot_( A0
                                            , typename boost::proto::result_of::
                                                      child_c<A1, 0>::type
                                            )
                      >::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return bitwise_andnot(a0, boost::proto::child_c<0>(a1));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION(boost::simd::tag::bitwise_and_ , boost::simd::tag::recognition_
                            , (A0)(A1)(Dom)(Sema)
                            , ((expr_<A0,Dom,boost::simd::tag::complement_,Sema>))
                              (unspecified_<A1>)
                            )
  {
    typedef typename dispatch::
            meta::call< boost::simd::tag::bitwise_andnot_( A1
                                            , typename boost::proto::result_of::
                                                      child_c<A0, 0>::type
                                            )
                      >::type result_type;

    BOOST_SIMD_FUNCTOR_CALL(2)
    {
      return bitwise_andnot(a1, boost::proto::child_c<0>(a0));
    }
  };
} } }

#endif
