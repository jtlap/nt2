//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//============================================================================== 
#ifndef NT2_SDK_META_RESULT_OF_HPP_INCLUDED
#define NT2_SDK_META_RESULT_OF_HPP_INCLUDED

#include <nt2/extension/parameters.hpp>
#include <boost/function_types/result_type.hpp>
#include <boost/mpl/has_xxx.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <boost/mpl/or.hpp>
#include <boost/utility/enable_if.hpp>

#if !defined(BOOST_HAS_VARIADIC_TMPL) || !defined(NT2_DONT_USE_PREPROCESSED_FILES) || (defined(__WAVE__) && defined(NT2_CREATE_PREPROCESSED_FILES))
#include <nt2/extension/parameters.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#endif

namespace nt2
{
  namespace meta
  {
    template<class Sig, class Enable = void>
    struct result_of;
    
    BOOST_MPL_HAS_XXX_TRAIT_DEF(result_type);
    
    template<class T>
    struct is_function
      : boost::is_function<typename boost::remove_pointer<typename meta::strip<T>::type>::type>
    {
    };
  }
}
    
#if (defined(BOOST_HAS_VARIADIC_TMPL) && !defined(__WAVE__)) || defined(DOXYGEN_ONLY)
#include <functional>
namespace nt2 { namespace meta
{
  template<class Sig, class Enable>
  struct result_of : std::result_of<Sig>
  {
  };
} }
#else
namespace nt2 { namespace meta
{
#if !defined(NT2_DONT_USE_PREPROCESSED_FILES)
#include <nt2/sdk/meta/preprocessed/result_of.hpp>
#else
#if defined(__WAVE__) && defined(NT2_CREATE_PREPROCESSED_FILES)
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
    struct result_of<F(BOOST_PP_ENUM_PARAMS(n, A)), typename boost::enable_if< has_result_type<F> >::type>\
    {                                                                                      \
      typedef typename F::result_type type;                                                \
    };                                                                                     \
                                                                                           \
    template<class F BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, class A)>                \
    struct result_of<F(BOOST_PP_ENUM_PARAMS(n, A)), typename boost::disable_if< boost::mpl::or_< is_function<F>, has_result_type<F> > >::type>\
    {                                                                                      \
      typedef typename F::template result<F(BOOST_PP_ENUM_PARAMS(n, A))>::type type;       \
    };

    BOOST_PP_REPEAT(BOOST_PP_INC(NT2_MAX_ARITY), M0, ~)
    #undef M0
    
#if defined(__WAVE__) && defined(NT2_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif
    
  }
}
#endif

#endif
