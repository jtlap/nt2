//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_RESULT_OF_HPP_INCLUDED
#define BOOST_DISPATCH_META_RESULT_OF_HPP_INCLUDED

#include <boost/dispatch/details/parameters.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/dispatch/meta/enable_if_type.hpp>
#include <boost/utility/enable_if.hpp>

#if (defined(BOOST_NO_VARIADIC_TEMPLATES) && defined(BOOST_DISPATCH_DONT_USE_PREPROCESSED_FILES)) || defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES)
#include <boost/dispatch/details/parameters.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#endif

namespace boost { namespace dispatch
{
  namespace meta
  {
    template<class Sig, class Enable = void>
    struct result_of {};

    template<class T>
    struct is_function
      : boost::is_function<typename boost::remove_pointer<typename meta::strip<T>::type>::type>
    {
    };
  }
} }

#if (!defined(BOOST_NO_VARIADIC_TEMPLATES) && !defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES)) || defined(DOXYGEN_ONLY)
namespace boost { namespace dispatch { namespace meta
{
  template<class F, class... Args>
  struct result_of<F(Args...), typename boost::enable_if< is_function<F> >::type>
    : boost::function_types::result_type<typename boost::remove_pointer<typename meta::strip<F>::type>::type>
  {
  };

  template<class F, class... Args>
  struct result_of<F(Args...), typename enable_if_type< typename F::result_type >::type>
  {
    typedef typename F::result_type type;
  };

  template<class F, class... Args>
  struct result_of<F(Args...), typename enable_if_type< typename F::template result<F(Args...)>::type >::type>
  {
    typedef typename F::template result<F(Args...)>::type type;
  };

} } }
#else
namespace boost { namespace dispatch { namespace meta
{
#if !defined(BOOST_DISPATCH_DONT_USE_PREPROCESSED_FILES)
#include <boost/dispatch/meta/preprocessed/result_of.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/result_of.hpp")
#endif

    #define M0(z, n, t)                                                                    \
    template<class F BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, class A)>                \
    struct result_of<F(BOOST_PP_ENUM_PARAMS(n, A)), typename boost::enable_if< is_function<F> >::type>\
      : boost::function_types::result_type<typename boost::remove_pointer<typename meta::strip<F>::type>::type>\
    {                                                                                      \
    };                                                                                     \
                                                                                           \
    template<class F BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, class A)>                \
    struct result_of<F(BOOST_PP_ENUM_PARAMS(n, A)), typename enable_if_type< typename F::result_type >::type>\
    {                                                                                      \
      typedef typename F::result_type type;                                                \
    };                                                                                     \
                                                                                           \
    template<class F BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, class A)>                \
    struct result_of<F(BOOST_PP_ENUM_PARAMS(n, A)), typename enable_if_type< typename F::template result<F(BOOST_PP_ENUM_PARAMS(n, A))>::type >::type>\
    {                                                                                      \
      typedef typename F::template result<F(BOOST_PP_ENUM_PARAMS(n, A))>::type type;       \
    };

    BOOST_PP_REPEAT(BOOST_PP_INC(BOOST_DISPATCH_MAX_ARITY), M0, ~)
    #undef M0

#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif

  }
} }
#endif

#endif
