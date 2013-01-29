//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/bench/nary_benchmark.hpp>

#include <boost/simd/include/native.hpp>
#include <nt2/include/functions/cos.hpp>
#include <boost/simd/include/functions/abs.hpp>
#include <boost/dispatch/functor/preprocessor/dispatch.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/stringize.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

using boost::simd::native;

typedef boost::dispatch::functor<boost::simd::tag::abs_> abs_;
typedef boost::dispatch::functor<nt2::tag::cos_> cos_;
typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;

#define NT2_TIMING_RANGE( RANGE )                       \
  BOOST_PP_TUPLE_ELEM(3, 1, BOOST_PP_SEQ_ELEM(0,RANGE)) \
, BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_SEQ_ELEM(0,RANGE)) \
                                                        \
/**/

#define NT2_TIMING_NAME(FUNC,RANGE)                             \
FUNC(BOOST_DISPATCH_PP_STRIP(                                   \
        BOOST_PP_TUPLE_ELEM (3,0,BOOST_PP_SEQ_ELEM(0,RANGE))))  \
/**/

#define NT2_TIMING(FUNC, RANGE )                                                \
nt2::unit::nary_benchmark< FUNC                                                 \
                            ( BOOST_PP_TUPLE_ELEM (3, 0                         \
                                                  , BOOST_PP_SEQ_ELEM(0,RANGE)  \
                                                  )                             \
                            )                                                   \
                          > const                                               \
BOOST_PP_CAT(Func ## _experiment_, __COUNTER__)                                 \
( NT2_TIMING_RANGE( RANGE )                                                     \
, BOOST_PP_STRINGIZE( (NT2_TIMING_RANGE( RANGE )) )                             \
, BOOST_PP_STRINGIZE( NT2_TIMING_NAME(FUNC,RANGE) )                             \
)                                                                               \
/**/

#define RS(T,V1,V2) (T, V1, V2)

NT2_TIMING(abs_, (RS(float                  , -100, 100)) );
NT2_TIMING(abs_, (RS(double                 , -100, 100)) );
NT2_TIMING(abs_, (RS((native<float ,ext_t>) , -100, 100)) );
NT2_TIMING(abs_, (RS((native<double,ext_t>) , -100, 100)) );
