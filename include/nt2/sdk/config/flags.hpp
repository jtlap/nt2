/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_NT2_SDK_CONFIG_FLAGS_HPP_INCLUDED
#define NT2_NT2_SDK_CONFIG_FLAGS_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// VERBOSE Mode informations on additional config macros
////////////////////////////////////////////////////////////////////////////////
#ifdef NT2_VERBOSE
  #if defined(NT2_USE_EXCEPTION) && !defined(BOOST_NO_EXCEPTIONS)
    #warning NT2 Configuration: Exception enabled
  #elif defined(NT2_USE_EXCEPTION) && defined(BOOST_NO_EXCEPTIONS)
    #warning NT2 Configuration: Exception disabled via BOOST_NO_EXCEPTIONS
  #endif
  #if defined(NT2_USE_ASSERT) && !defined(BOOST_DISABLE_ASSERTS)
    #warning NT2 Configuration: Assertion enabled
  #endif
  #if defined(NT2_USE_ASSERT) && !defined(BOOST_DISABLE_ASSERTS)
    #warning NT2 Configuration: Assertion disabled via BOOST_DISABLE_ASSERTS
  #endif
  #if defined(NT2_USE_CONCEPTS)
    #warning NT2 Configuration: Concepts checking activated
  #endif
#endif

////////////////////////////////////////////////////////////////////////////////
// Setup some additional string macros
////////////////////////////////////////////////////////////////////////////////
#if defined(NT2_USE_EXCEPTION) && !defined(BOOST_NO_EXCEPTIONS)
  #define NT2_EXCEPTION_STRING  "activated"
#else
  #define NT2_EXCEPTION_STRING  "desactivated"
#endif
#if defined(NT2_USE_ASSERT) && !defined(BOOST_DISABLE_ASSERTS)
  #define NT2_ASSERT_STRING  "activated"
#else
  #define NT2_ASSERT_STRING  "desactivated"
#endif
#if defined(NT2_USE_CONCEPTS)
  #define NT2_CONCEPT_STRING  "activated"
#else
  #define NT2_CONCEPT_STRING  "desactivated"
#endif
#if defined(NT2_USE_OPENMP)
  #define NT2_OPENMP_STRING  "activated"
#else
  #define NT2_OPENMP_STRING  "desactivated"
#endif
#if defined(NT2_VERBOSE)
  #define NT2_VERBOSE_STRING  "activated"
#else
  #define NT2_VERBOSE_STRING  "desactivated"
#endif

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Status header reporter - Head for the reporter list
  //////////////////////////////////////////////////////////////////////////////
  static void flags()
  {
    puts(" Verbose mode            : " NT2_VERBOSE_STRING    );
    puts(" Exceptions              : " NT2_EXCEPTION_STRING  );
    puts(" Assertions              : " NT2_ASSERT_STRING     );
    puts(" Concepts checks         : " NT2_CONCEPT_STRING    );
  }

  NT2_REGISTER_STATUS(flags);
} }

#endif
