//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include "../common/bandwidth.hpp"
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#define M0(z,n,t)                                                              \
NT2_RUN_EXPERIMENT_TPL( bandwidth                                              \
                      , (( boost::simd::native < BOOST_PP_SEQ_ELEM(n, t)       \
                                                , BOOST_SIMD_DEFAULT_EXTENSION \
                                                >                              \
                          , nt2_                                               \
                        ))                                                     \
                      , (1<<26,3)                                              \
                      );                                                       \
/**/

BOOST_PP_REPEAT ( BOOST_PP_SEQ_SIZE(BOOST_SIMD_SIMD_TYPES)
                , M0
                , BOOST_SIMD_SIMD_TYPES
                )

#undef M0
