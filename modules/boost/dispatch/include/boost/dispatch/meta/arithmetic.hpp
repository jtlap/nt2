//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_ARITHMETIC_HPP_INCLUDED
#define BOOST_DISPATCH_META_ARITHMETIC_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the meta::arithmetic \metafunction
 */

#include <boost/dispatch/details/typeof.hpp>
#include <boost/utility/declval.hpp>

#if defined(BOOST_DISPATCH_DONT_USE_PREPROCESSED_FILES)
#include <boost/dispatch/details/parameters.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#endif

namespace boost { namespace dispatch  { namespace meta
{
  //============================================================================
  /*!
   * \ingroup metafunctions
   * For a list of types \c T0,...,Tn, ref arithmetic computes the type obtained by the
   * recursive application of \c decltype(0 ? declval<T0>() : declval<T1>())
   *
   * \semantic
   *
   * For types \c T0,...,Tn,
   *
   * \code
   * typedef result_of<arithmetic(T0,...,Tn)>::type type
   * \endcode
   *
   * is equivalent to:
   *
   * \code
   * typedef boost::common_type<T0,...,TN>::type type;
   * \endcode
   *
   * \par Example Usage:
   *
   * \include arithmetic.cpp
   */
  //============================================================================
  struct arithmetic
  {
    template<class Sig> struct result;

#if !defined(BOOST_DISPATCH_DONT_USE_PREPROCESSED_FILES)
#include <boost/dispatch/meta/preprocessed/arithmetic.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/arithmetic.hpp")
#undef BOOST_DISPATCH_TYPEOF
#endif

    #define M0(z,n,t) 0 ? 
    #define M1(z,n,t)  : boost::declval<A##n>()
    #define M2(z,n,t)                                                                    \
    template<class This,BOOST_PP_ENUM_PARAMS(n,class A)>                                 \
    struct  result<This(BOOST_PP_ENUM_PARAMS(n,A))>                                      \
    {                                                                                    \
      BOOST_DISPATCH_TYPEOF( BOOST_PP_REPEAT_FROM_TO(1,n,M0,~)                           \
                             boost::declval<A0>() BOOST_PP_REPEAT_FROM_TO(1,n,M1,~)      \
                           , type );                                                     \
    };                                                                                   \
    /**/
    BOOST_PP_REPEAT_FROM_TO(2,BOOST_DISPATCH_MAX_ARITY,M2,~)
    
    #undef M2
    #undef M1
    #undef M0
    
#if defined(__WAVE__) && defined(BOOST_DISPATCH_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif

    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef A0 type;
    };

  };
} } }

#endif
