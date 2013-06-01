//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_TESTS_ULP_HPP_INCLUDED
#define NT2_SDK_UNIT_TESTS_ULP_HPP_INCLUDED

#include <nt2/sdk/unit/io.hpp>
#include <nt2/sdk/unit/stats.hpp>
#include <nt2/sdk/unit/details/eval.hpp>
#include <nt2/sdk/unit/details/ulp.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/include/functions/unaligned_load.hpp>
#include <nt2/include/functions/unaligned_store.hpp>
#include <boost/preprocessor/seq/elem.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/current_function.hpp>
#include <boost/typeof/typeof.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include <iomanip>
#include <vector>

/*!
  @brief Check for absolute precision

  For two given values @c A and @c B, consider the test successful if and only
  if the absolute difference between @c A and @b is less or equal to @c N.

  @usage
  @include test_ulp.cpp
**/
#define NT2_TEST_ULP_EQUAL(A, B, N)                                            \
do                                                                             \
{                                                                              \
  nt2::unit::test_count()++;                                                   \
                                                                               \
  nt2::details::test_ulp_equal( #A " == " #B                                   \
                              , BOOST_CURRENT_FUNCTION, __LINE__               \
                              , A, B, N                                        \
                              );                                               \
}                                                                              \
while(0)                                                                       \
/**/

/// INTERNAL ONLY Grab an input type
#define NT2_COVER_TYPE(z,n,t) BOOST_PP_TUPLE_ELEM(2,0,BOOST_PP_SEQ_ELEM(n,t))  \
/**/

/// INTERNAL ONLY Grab an input type
#define NT2_COVER_VAR(n,t) BOOST_PP_TUPLE_ELEM(2,1,BOOST_PP_SEQ_ELEM(n,t))     \
/**/

/// INTERNAL ONLY Load a part of the input of the cover
#define NT2_COVER_LOAD(z,n,t)                                                  \
nt2::unaligned_load<BOOST_PP_TUPLE_ELEM(2,0,BOOST_PP_SEQ_ELEM(n,t))>           \
  (&BOOST_PP_TUPLE_ELEM(2,1,BOOST_PP_SEQ_ELEM(n,t))[i])                        \
/**/

/// INTERNAL ONLY Display an input
#define NT2_COVER_DISP(z,n,t)                                                  \
<< ", " << nt2::unaligned_load<NT2_COVER_TYPE(z,n,t)>(&NT2_COVER_VAR(n,t)[ii]) \
/**/

#define NT2_COVER_ULP_EQUAL(TAG, INPUTS, REF, N)                               \
do                                                                             \
{                                                                              \
  nt2::unit::test_count()++;                                                   \
                                                                               \
  typedef typename nt2::meta::call                                             \
                  < TAG ( BOOST_PP_ENUM ( BOOST_PP_SEQ_SIZE(INPUTS)            \
                                        , NT2_COVER_TYPE                       \
                                        , INPUTS                               \
                                        )                                      \
                        )>::type r_t;                                          \
  typedef typename nt2::meta::scalar_of<r_t>::type                      out_t; \
                                                                               \
  std::vector<out_t> out(REF.size());                                          \
                                                                               \
  nt2::functor<TAG> callee;                                                    \
  std::size_t cc = nt2::meta::cardinal_of<BOOST_PP_TUPLE_ELEM ( 2,0            \
                                        , BOOST_PP_SEQ_ELEM(0,INPUTS)          \
                                        )>::value;                             \
                                                                               \
  for(std::size_t i=0; i<REF.size(); i+=cc)                                    \
  {                                                                            \
    nt2::unaligned_store( callee( BOOST_PP_ENUM ( BOOST_PP_SEQ_SIZE(INPUTS)    \
                                      , NT2_COVER_LOAD                         \
                                      , INPUTS                                 \
                                      )                                        \
                                                                               \
                                )                                              \
                        , &out[i]                                              \
              );                                                               \
  }                                                                            \
                                                                               \
  typedef BOOST_TYPEOF(nt2::unit::eval(REF[0]))                   a_t;         \
  typedef BOOST_TYPEOF(nt2::unit::eval(out[0]))                   b_t;         \
  typedef typename nt2::details::max_ulp_<a_t,b_t>::failure_type  f_t;         \
                                                                               \
  std::vector< f_t > ulps;                                                     \
  double ulpd = 0;                                                             \
  find_ulp_error(out,REF,ulps,ulpd,N);                                         \
                                                                               \
  if(ulps.empty())                                                             \
  {                                                                            \
   ::nt2::unit::pass( BOOST_PP_STRINGIZE(TAG) " coverage");                    \
  }                                                                            \
  else                                                                         \
  {                                                                            \
    ++nt2::unit::error_count();                                                \
    int ib = -1;                                                               \
    BOOST_FOREACH ( f_t const& f, ulps )                                       \
    {                                                                          \
      int ii = (f.index/cc)*cc;                                                \
      if(ii > ib)                                                              \
      {                                                                        \
        std::cout << std::setprecision(20)                                     \
                  << BOOST_PP_STRINGIZE(TAG)                                   \
                  << "("                                                       \
                  << nt2::unaligned_load<NT2_COVER_TYPE(~,0,INPUTS)>           \
                                              (&NT2_COVER_VAR(0,INPUTS)[ii])   \
                  BOOST_PP_REPEAT_FROM_TO ( 1                                  \
                                          , BOOST_PP_SEQ_SIZE(INPUTS)          \
                                          , NT2_COVER_DISP                     \
                                          , INPUTS                             \
                                          )                                    \
                  << ")"                                                       \
                  << " got "                                                   \
                  << nt2::unaligned_load<r_t>(&out[ii])                        \
                  << " while expecting "                                       \
                  << nt2::unaligned_load<r_t>(&REF[ii])                        \
                  << " (i.e "   << f.ulp_error << " ULPs)";                    \
        std::cout << std::endl;                                                \
        ib = ii;                                                               \
      }                                                                        \
    }                                                                          \
  }                                                                            \
}                                                                              \
while(0)                                                                       \
/**/

#endif
