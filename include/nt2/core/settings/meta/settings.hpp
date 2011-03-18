/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_SETTINGS_META_SETTINGS_HPP_INCLUDED
#define NT2_CORE_SETTINGS_META_SETTINGS_HPP_INCLUDED

#include <nt2/extension/parameters.hpp>
#include <nt2/core/settings/meta/option.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace nt2
{
  //////////////////////////////////////////////////////////////////////////////
  // settings is a mark-up for lazy options list.
  //////////////////////////////////////////////////////////////////////////////
  struct settings {};
}

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // empty settings list returns default for the option
  //////////////////////////////////////////////////////////////////////////////
  template<class Option, class Default>
  struct option<settings(),Option,Default, typename Option::nt2_is_option_type>
  {
    typedef Default type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // settings list of one argument return the argument option value
  //////////////////////////////////////////////////////////////////////////////
  template<class S0, class Option, class Default>
  struct  option< settings(S0), Option, Default
                , typename Option::nt2_is_option_type
                >
        : option<S0,Option,Default>
  {};

  //////////////////////////////////////////////////////////////////////////////
  // Non-empty settings list is recursively inspected
  //////////////////////////////////////////////////////////////////////////////
  #define M0(z,n,t)                                                       \
  template< BOOST_PP_ENUM_PARAMS(n,class S), class Option, class Default> \
  struct option < settings(BOOST_PP_ENUM_PARAMS(n,S))                     \
                , Option, Default, typename Option::nt2_is_option_type    \
                >                                                         \
  {                                                                       \
    typedef typename                                                      \
            option< settings(BOOST_PP_ENUM_PARAMS(BOOST_PP_DEC(n),S))     \
                  , Option, Default>::type                  base_type;    \
    typedef typename                                                      \
            option< BOOST_PP_CAT(S,BOOST_PP_DEC(n))                       \
                  , Option,base_type>::type                 type;         \
  };                                                                      \
  /**/

  BOOST_PP_REPEAT_FROM_TO(2,NT2_MAX_META_ARITY,M0,~)
} }

////////////////////////////////////////////////////////////////////////////////
// Macros clean-up
////////////////////////////////////////////////////////////////////////////////
#undef M0

#endif
