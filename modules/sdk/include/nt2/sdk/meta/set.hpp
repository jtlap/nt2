//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_SET_HPP_INCLUDED
#define NT2_SDK_META_SET_HPP_INCLUDED

/*!
 * \file
 * \brief Defines and implements the nt2::meta::set class
 */

#include <boost/mpl/bool.hpp>
#include <boost/mpl/apply.hpp>
#include <nt2/sdk/meta/na.hpp>
#include <nt2/extension/parameters.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

namespace nt2 { namespace meta
{
  #if defined(DOXYGEN_ONLY)
  //============================================================================
  /*!
   * Defines a compile-time set of types similar in principles to
   * boost::mpl::set but optimized to be immutable, which means operations
   * like insertion ordeletion of key or iteration is unavailable.
   *
   * \see nt2::meta::has_key
   */
  //============================================================================
  template<class Args...> struct set {};
  #endif

  //============================================================================
  // Explicit set listing its elements
  //============================================================================
  #define M0(z,n,t) static boost::mpl::true_ key(BOOST_PP_CAT(A,n)*);

  template<BOOST_PP_ENUM_BINARY_PARAMS( NT2_MAX_META_ARITY
                                      , class A
                                      , = meta::na_ BOOST_PP_INTERCEPT
                                      )
                                      >
  struct set
  {
    typedef void  is_set_type;
    typedef set   type;
    template<class T> static boost::mpl::false_ key(T*);
    BOOST_PP_REPEAT(NT2_MAX_META_ARITY,M0,~)
  };

  #define M1(z,n,t)                                       \
  template<BOOST_PP_ENUM_PARAMS(n,class A)>               \
  struct  set<BOOST_PP_ENUM_PARAMS(n,A)>                  \
  {                                                       \
    typedef void  is_set_type;                            \
    typedef set   type;                                   \
    template<class T> static boost::mpl::false_ key(T*);  \
    BOOST_PP_REPEAT(n,M0,~)                               \
  };                                                      \
  /**/

  //============================================================================
  // Generate all hierarchy specialization
  //============================================================================
  BOOST_PP_REPEAT_FROM_TO(1,NT2_MAX_META_ARITY,M1,~)

  #undef M0
  #undef M1

} }

#endif
