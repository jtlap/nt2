//==============================================================================
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_PREPROCESSOR_MAKE_HPP_INCLUDED
#define BOOST_SIMD_PREPROCESSOR_MAKE_HPP_INCLUDED

#include <boost/simd/sdk/simd/preprocessor/repeat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

#define BOOST_SIMD_PP_DETAILS_MAKE(z, Cardinal, Args)                          \
BOOST_FORCEINLINE                                                              \
result_type eval( BOOST_PP_ENUM_BINARY_PARAMS ( BOOST_PP_TUPLE_ELEM(2,0,Args)  \
                                              , const A,& a                    \
                                              )                                \
                , boost::mpl::size_t<Cardinal> const&                          \
                ) const                                                        \
{                                                                              \
  return make<result_type>(BOOST_PP_ENUM( Cardinal                             \
                                        , BOOST_PP_TUPLE_ELEM(2,1,Args)        \
                                        , Cardinal                             \
                                        )                                      \
                          );                                                   \
}                                                                              \
/**/

/*!
  @brief make-based implementation generator

  Some SIMD functions can't be defined otherwise than as the explicit
  building of a SIMD register using make<T>(...). This macro facilitate
  the generation of regular, cardinal based use of make in this case for
  every valid cardinal.

  @param Args     Number of actual parameters to the inner call
  @param Function Preprocessor macro generating one element of the make call
**/
#define BOOST_SIMD_PP_IMPLEMENT_WITH_MAKE(Args,Function)                       \
BOOST_SIMD_PP_REPEAT_POWER_OF_2_FROM( 2                                        \
                                    , BOOST_SIMD_PP_DETAILS_MAKE               \
                                    , (Args,Function)                          \
                                    )                                          \
/**/

#endif
