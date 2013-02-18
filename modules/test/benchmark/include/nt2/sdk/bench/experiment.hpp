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
#ifndef NT2_SDK_BENCH_EXPERIMENT_HPP_INCLUDED
#define NT2_SDK_BENCH_EXPERIMENT_HPP_INCLUDED

#include <nt2/sdk/meta/type_id.hpp>
#include <nt2/sdk/error/exception.hpp>
#include <nt2/sdk/bench/details/prng.hpp>
#include <boost/dispatch/preprocessor/strip.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

/*!
 @brief Definition of an Experiment
**/
#define NT2_EXPERIMENT(Type)                      \
class BOOST_DISPATCH_PP_STRIP(Type) : public nt2::details::base_experiment \
/**/

/*!
 @brief Definition of an Experiment Constructor
**/
#define NT2_EXPRIMENT_CTOR(Duration, Unit)                      \
nt2::details::base_experiment ( (Duration)                      \
                              , ::nt2::type_id(*this)           \
                              , Unit                            \
                              , &nt2::details::main_bench_suite \
                              )                                 \
/**/

/*!
 @brief Registration of an Experiment
**/
#define NT2_RUN_EXPERIMENT(Type)                        \
Type const BOOST_PP_CAT(Type ## _experiment_, __LINE__) \
/**/

#define NT2_RUN_EXPERIMENT_STEP(r, data, elem)                          \
BOOST_PP_TUPLE_ELEM(2,0,data)<BOOST_DISPATCH_PP_STRIP(elem)> const      \
BOOST_PP_CAT( BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(2,0,data),_experiment_)  \
            , __COUNTER__                                               \
            )                                                           \
BOOST_PP_TUPLE_ELEM(2,1,data);                                          \
/**/

/*!
 @brief Registration of a set of template Experiments
**/
#define NT2_RUN_EXPERIMENT_TPL(Type,Types,Ctor)                   \
BOOST_PP_SEQ_FOR_EACH(NT2_RUN_EXPERIMENT_STEP,(Type,Ctor),Types)  \
/**/

#endif
