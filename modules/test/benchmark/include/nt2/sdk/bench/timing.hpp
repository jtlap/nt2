//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//         Copyright 2012        Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TEST_BENCH_TIMING_HPP_INCLUDED
#define NT2_TEST_BENCH_TIMING_HPP_INCLUDED

#include <nt2/sdk/bench/nary_benchmark.hpp>
#include <boost/dispatch/functor/preprocessor/dispatch.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>

#define NT2_TIMING_RANGE_ELEM(r,d,i,e)              \
BOOST_PP_COMMA_IF(i)  BOOST_PP_TUPLE_ELEM(3, 1, e)  \
                    , BOOST_PP_TUPLE_ELEM(3, 2, e)  \
/**/

#define NT2_TIMING_RANGE( RANGE )                       \
BOOST_PP_SEQ_FOR_EACH_I(NT2_TIMING_RANGE_ELEM,~,RANGE)  \
/**/

#define NT2_TIMING_TYPES(r,d,i,e)                                         \
BOOST_PP_COMMA_IF(i) BOOST_DISPATCH_PP_STRIP(BOOST_PP_TUPLE_ELEM(3,0,e))  \
/**/

#define NT2_TIMING_NAME(FUNC,RANGE)                     \
FUNC(BOOST_PP_SEQ_FOR_EACH_I(NT2_TIMING_TYPES,~,RANGE)) \
/**/

#define NT2_TIMING(FUNC, RANGE )                                              \
nt2::unit::nary_benchmark                                                     \
    < boost::dispatch::functor<FUNC>                                          \
      (BOOST_PP_SEQ_FOR_EACH_I(NT2_TIMING_TYPES,~,RANGE)) > const             \
BOOST_PP_CAT(Func ## _experiment_, __COUNTER__)( NT2_TIMING_RANGE( RANGE ) ); \
/**/

#endif
