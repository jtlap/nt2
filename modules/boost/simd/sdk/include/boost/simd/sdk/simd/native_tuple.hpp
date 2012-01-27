//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_NATIVE_TUPLE_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_NATIVE_TUPLE_HPP_INCLUDED

#include <boost/simd/sdk/simd/native_fwd.hpp>

#include <boost/simd/sdk/tuple.hpp>
#include <boost/fusion/include/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/dispatch/meta/strip.hpp>

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace boost { namespace simd
{
  namespace details
  {
    template<class X>
    struct vector_of_
    {
      template<class Sig>
      struct result;
      
      template<class This, class U>
      struct result<This(U)>
      {
        typedef typename dispatch::meta::strip<U>::type sU;
        typedef simd::native<sU, X> type;
      };
    };
  }

  template<class T, class X>
  struct native<T, X, typename boost::enable_if< boost::fusion::traits::is_sequence<T> >::type>
   : meta::as_tuple<T, details::vector_of_<X> >::type
  {
    typedef typename meta::as_tuple<T, details::vector_of_<X> >::type    parent;

    native()
    {
    }

    #define M0(z, n, t)                                                        \
    template<BOOST_PP_ENUM_PARAMS(n, class A)>                                 \
    native(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a))                        \
      : parent(BOOST_PP_ENUM_PARAMS(n, a))                                     \
    {                                                                          \
    }                                                                          \
    /**/

    BOOST_PP_REPEAT_FROM_TO(1, BOOST_DISPATCH_MAX_META_ARITY, M0, ~)
    #undef M0
  };

} }

#endif
