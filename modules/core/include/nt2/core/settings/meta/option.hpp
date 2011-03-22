/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_SETTINGS_META_OPTION_HPP_INCLUDED
#define NT2_CORE_SETTINGS_META_OPTION_HPP_INCLUDED

#include <nt2/sdk/error/static_assert.hpp>

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Extract an option value from a given type or type groups
  //////////////////////////////////////////////////////////////////////////////
  template<class Type, class Option, class Default, class Enable = void>
  struct option
  {
    NT2_STATIC_ASSERT ( sizeof(Enable*) == 0
                      , NT2_UNKNOWN_OPTION_TAG
                      , "An attempt has been made to recover a container setting "
                        "using an unregistered option tag. Check your option<> "
                        "calls for any typos in the Option parameters or, if you "
                        "are using a custom option tag, check for its Option "
                        "Concept conformance."
                      );
  };

  //////////////////////////////////////////////////////////////////////////////
  // By default, return the default options :p
  //////////////////////////////////////////////////////////////////////////////
  template<class Type, class Option, class Default>
  struct option<Type,Option,Default, typename Option::nt2_is_option_type>
  {
    typedef Default type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Forward option checking on S(*)(X) to S(X)
  //////////////////////////////////////////////////////////////////////////////
  template<class Type, class Option, class Default>
  struct option<Type*,Option,Default> : option<Type,Option,Default> {};
} }

#endif
