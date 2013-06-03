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
#include <boost/mpl/vector.hpp>
#include <boost/mpl/at.hpp>
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
#define NT2_COVER_VAR(z,n,t) BOOST_PP_TUPLE_ELEM(2,1,BOOST_PP_SEQ_ELEM(n,t))   \
/**/

/// INTERNAL ONLY Display an input
#define NT2_COVER_DISP(z,n,t)                                                  \
<< ", "<< nt2::unaligned_load<NT2_COVER_TYPE(z,n,t)>(&NT2_COVER_VAR(z,n,t)[ii])\
/**/

#define NT2_COVER_INPUT_TYPES(z,n,t)                                           \
typedef typename boost::mpl::at_c<Types,n>::type type_##n;                     \
/**/

#define NT2_COVER_LOADS(z,n,t)                                                 \
nt2::unaligned_load<type_##n>(&i##n[i])                                        \
/**/

#define NT2_COVER_TYPES_LIST(INPUTS)                                           \
boost::mpl::vector<BOOST_PP_ENUM( BOOST_PP_SEQ_SIZE(INPUTS)                    \
                                , NT2_COVER_TYPE                               \
                                , INPUTS                                       \
                                )>()                                           \
/**/

#define NT2_COVER_VALUES_LIST(INPUTS)                                          \
BOOST_PP_ENUM( BOOST_PP_SEQ_SIZE(INPUTS), NT2_COVER_VAR, INPUTS )              \
/**/

namespace nt2 { namespace details
{
  #define NT2_COVER_COMPUTE(z,n,t)                                             \
  template< typename Function, typename Data, typename Types                   \
          , BOOST_PP_ENUM_PARAMS(n,typename I)                                 \
          >                                                                    \
  Data compute_coverage ( Function f, Data const& ref, Types const&            \
                        , BOOST_PP_ENUM_BINARY_PARAMS(n,I, const& i)           \
                        )                                                      \
  {                                                                            \
    Data out(ref.size());                                                      \
                                                                               \
    BOOST_PP_REPEAT(n,NT2_COVER_INPUT_TYPES,~)                                 \
    std::size_t cc = meta::cardinal_of<type_0>::value;                         \
                                                                               \
    for(std::size_t i=0; i<out.size(); i+=cc)                                  \
    {                                                                          \
      nt2::unaligned_store( f(BOOST_PP_ENUM(n,NT2_COVER_LOADS,~)), &out[i]);   \
    }                                                                          \
                                                                               \
    return out;                                                                \
  }                                                                            \
  /**/

  BOOST_PP_REPEAT_FROM_TO ( 1
                          , BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY)
                          , NT2_COVER_COMPUTE
                          , ~
                          )
} }

#define NT2_COVER_ULP_EQUAL(TAG, INPUTS, REF, N)                               \
do                                                                             \
{                                                                              \
  nt2::unit::test_count()++;                                                   \
                                                                               \
  std::size_t cc = nt2::meta::cardinal_of                                      \
                            < BOOST_PP_TUPLE_ELEM( 2, 0                        \
                                                 , BOOST_PP_SEQ_ELEM(0,INPUTS) \
                                                 )                             \
                            >::value;                                          \
                                                                               \
  nt2::functor<TAG> callee;                                                    \
  BOOST_AUTO( out                                                              \
            , ::nt2::details                                                   \
                  ::compute_coverage( callee, ref                              \
                                    , NT2_COVER_TYPES_LIST(INPUTS)             \
                                    , NT2_COVER_VALUES_LIST(INPUTS)            \
                                    )                                          \
            );                                                                 \
                                                                               \
  typedef BOOST_TYPEOF(nt2::unit::eval(out[0]))          t_t;                  \
  typedef typename nt2::details::max_ulp_<t_t,t_t>::failure_type  f_t;         \
                                                                               \
  std::vector< f_t > ulps;                                                     \
  double ulpd = 0;                                                             \
  find_ulp_error(out,REF,ulps,ulpd,N);                                         \
                                                                               \
  if(ulps.empty())                                                             \
  {                                                                            \
    ::nt2::unit::pass( BOOST_PP_STRINGIZE(TAG) " coverage");                   \
  }                                                                            \
  else                                                                         \
  {                                                                            \
    ::nt2::unit::fail( BOOST_PP_STRINGIZE(TAG) " coverage",__LINE__,__FILE__); \
    int ib = -1;                                                               \
    typedef typename nt2::meta::call                                           \
                    < TAG ( BOOST_PP_ENUM ( BOOST_PP_SEQ_SIZE(INPUTS)          \
                                          , NT2_COVER_TYPE                     \
                                          , INPUTS                             \
                                          )                                    \
                          )>::type r_t;                                        \
                                                                               \
    BOOST_FOREACH ( f_t const& f, ulps )                                       \
    {                                                                          \
      int ii = (f.index/cc)*cc;                                                \
      if(ii > ib)                                                              \
      {                                                                        \
        std::cout << std::setprecision(20)                                     \
                  << BOOST_PP_STRINGIZE(TAG)                                   \
                  << "("                                                       \
                  << nt2::unaligned_load<NT2_COVER_TYPE(~,0,INPUTS)>           \
                                        (&NT2_COVER_VAR(~,0,INPUTS)[ii])       \
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
