/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_DETAILS_VALIDATE_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_DETAILS_VALIDATE_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// User-overloadable validation meta-function
//* TODO : Documentation:http://nt2.lri.fr/sdk/howto/functor.html
////////////////////////////////////////////////////////////////////////////////
#include <boost/mpl/bool.hpp>
#include <nt2/sdk/meta/any.hpp>
#include <nt2/sdk/meta/unknown.hpp>
#include <nt2/sdk/meta/is_result_of_supported.hpp>

#if !defined(BOOST_HAS_VARIADIC_TMPL)
#include <nt2/extension/parameters.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#endif

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // A functor call is validated iff :
  //  * a call<Function,Category,Info> overload exists wiht a proper result_of
  //  * no bool appears in the list of argument types
  //  * Category is not tag::unknwon
  //////////////////////////////////////////////////////////////////////////////
  template<class Function,class Category,class Info>
  struct validate
  {
    template<class Sig> struct result;
    #if defined(BOOST_HAS_VARIADIC_TMPL)
    template<class This, class... Args>
    struct  result<This(Args...)>
    {
      typedef call<Function,Category,Info>                            callee;
      typedef typename
      nt2::meta::is_result_of_supported<callee(Args...)>::type        callable;
      typedef meta::any<boost::is_same<boost::mpl::_,bool>, Args... > bools;
      typedef boost::mpl::bool_<callable::value && !bools::value>     type;
    };
    #else
    #define M0(z,n,t)                                                           \
    template<class This, BOOST_PP_ENUM_PARAMS(n,class A)>                       \
    struct  result<This(BOOST_PP_ENUM_PARAMS(n,A))>                             \
    {                                                                           \
      typedef call<Function,Category,Info>                            callee;   \
      typedef typename                                                          \
      nt2::meta::                                                               \
      is_result_of_supported<callee(BOOST_PP_ENUM_PARAMS(n,A))>::type callable; \
      typedef meta::any < boost::is_same<boost::mpl::_,bool >                   \
                        , BOOST_PP_ENUM_PARAMS(n,A)         >         bools;    \
      typedef boost::mpl::bool_<callable::value && !bools::value>     type;     \
    };                                                                          \
    /**/
    BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_ARITY),M0,~)
    #undef M0
    #endif
  };

  template<class Function,class Info>
  struct validate<Function,tag::unknown,Info>
  {
    typedef boost::mpl::false_ result_type;
  };
/*


*/

} }

#endif
