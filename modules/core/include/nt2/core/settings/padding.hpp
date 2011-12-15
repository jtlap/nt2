//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_PADDING_HPP_INCLUDED
#define NT2_CORE_SETTINGS_PADDING_HPP_INCLUDED

#include <boost/mpl/eval_if.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/misc.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace nt2
{
  //===========================================================================
  /*! 
   * Composite settings for container memory padding strategies.
   **/
  //============================================================================
  struct padding_ {};
}

namespace nt2 { namespace meta
{
  //============================================================================
  // empty padding list returns default for any option
  //============================================================================
  template<class Option, class Default>
  struct option<padding_(),Option,Default> : option<Default,Option>
  {};

  //============================================================================
  // padding list of one argument return the argument option value
  //============================================================================
  template<class S0, class Option, class Default>
  struct  option< padding_(S0), Option, Default >
        : option<S0,Option,Default>
  {};

  //============================================================================
  // padding list of one argument return the argument option value
  //============================================================================
  template<class S0, std::size_t N, class Option, class Default>
  struct  option< padding_(S0, with_<N>), Option, Default >
        : option<S0,Option,Default>
  {};


} }

#endif
