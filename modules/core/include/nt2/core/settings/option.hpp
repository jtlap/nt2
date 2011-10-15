//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_OPTION_HPP_INCLUDED
#define NT2_CORE_SETTINGS_OPTION_HPP_INCLUDED

/*!
 * \file
 * \brief Defines NT2 container option base system 
 **/

#include <boost/mpl/assert.hpp>

//==============================================================================
/*!
 * Defines the maximum number of options that can be passed to a composite
 * settings. Thismacro can be set by users if needed. 
 **/
//==============================================================================
#ifndef NT2_META_MAX_OPTIONS_NB
#define NT2_META_MAX_OPTIONS_NB 8
#endif

namespace nt2 { namespace meta
{  
  //============================================================================
  /*!
   * Extract an option value from a given type or type groups, returning a given
   * default option if none is found.
   * 
   * \tparam Type Settings type to introspect
   * \tparam Option Option tag to be retrieved
   * \tparam Default If no Option is found, use this option as a source
   **/
  //============================================================================
  template<class Type, class Option, class Default = void> 
  struct  option : option<Default,Option>
  {};

  struct no_such_option {};

  template<class Option> struct  option<void,Option, void> 
  {
    typedef no_such_option type;
  };

  //============================================================================
  // Forward option checking on S(*)(X) to S(X)
  //============================================================================
  template<class Type, class Option, class Default>
  struct option<Type*,Option,Default> : option<Type,Option,Default> {};
} }

#endif
