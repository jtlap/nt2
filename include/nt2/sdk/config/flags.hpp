/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_CONFIG_FLAGS_HPP_INCLUDED
#define NT2_SDK_CONFIG_FLAGS_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// VERBOSE Mode informations on additional config macros
////////////////////////////////////////////////////////////////////////////////
#ifdef NT2_VERBOSE
  #if !defined(BOOST_NO_EXCEPTIONS)
    #warning NT2 Configuration: Exception enabled
  #endif
  #if defined(NT2_USE_CONCEPTS)
    #warning NT2 Configuration: Concepts checking activated
  #endif
#endif

////////////////////////////////////////////////////////////////////////////////
// Setup some additional string macros
////////////////////////////////////////////////////////////////////////////////
#if defined(NT2_USE_CONCEPTS)
  #define NT2_CONCEPT_STRING  "activated"
#else
  #define NT2_CONCEPT_STRING  "desactivated"
#endif

namespace nt2 { namespace config
{
  //////////////////////////////////////////////////////////////////////////////
  // Status header reporter - Head for the reporter list
  //////////////////////////////////////////////////////////////////////////////
  static void flags()
  {
    #if defined(NT2_VERBOSE)
    puts(" Verbose mode            : activated" );
    #else
    puts(" Verbose mode            : desactivated" );
    #endif
    puts(" Concepts checks         : " NT2_CONCEPT_STRING "\n");
  }

  NT2_REGISTER_STATUS(flags);
} }

#endif
