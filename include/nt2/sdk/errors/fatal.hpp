/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_NT2_SDK_ERRORS_FATAL_HPP_INCLUDED
#define NT2_NT2_SDK_ERRORS_FATAL_HPP_INCLUDED

#include <nt2/sdk/errors/error.hpp>
#include <nt2/sdk/errors/details/fatal.hpp>

////////////////////////////////////////////////////////////////////////////////
// Option to set exit code for fatal warning
////////////////////////////////////////////////////////////////////////////////
#ifndef NT2_FATAL_EXIT_CODE
#define NT2_FATAL_EXIT_CODE EXIT_FAILURE
#endif

////////////////////////////////////////////////////////////////////////////////
// Fatal can be requalified as ERROR
////////////////////////////////////////////////////////////////////////////////
#if defined(NT2_FATAL_AS_ERROR)

#if defined( NT2_VERBOSE )
#warning NT2 Fatal requalified as errors
#endif

#define NT2_FATAL(Condition,Message)              \
do                                                \
{                                                 \
  if(!(Condition))                                \
    NT2_ERROR ( nt2::error_exception              \
              , ((nt2::details::error_,Message))  \
              );                                  \
} while(0)                                        \
/**/
////////////////////////////////////////////////////////////////////////////////
// Fatal can be requalified as WARNING
////////////////////////////////////////////////////////////////////////////////
#elif defined(NT2_FATAL_AS_WARNING)

#if defined(NT2_VERBOSE)
#warning NT2 Fatal requalified as warning
#endif

#define NT2_FATAL(Condition,Message)        \
do                                          \
{                                           \
  if(!(Condition)) NT2_EMIT_FATAL(Message); \
} while(0)                                  \
/**/
////////////////////////////////////////////////////////////////////////////////
// Default Fatal behavior is log+exit
////////////////////////////////////////////////////////////////////////////////
#elif !defined(NT2_NO_FATAL)

#define NT2_FATAL(Condition,Message)  \
do                                    \
{                                     \
  if(!(Condition))                    \
  {                                   \
    NT2_EMIT_FATAL(Message);          \
    exit(NT2_FATAL_EXIT_CODE);        \
  }                                   \
} while(0)                            \
/**/
#else
////////////////////////////////////////////////////////////////////////////////
// Fatal can be disabled
////////////////////////////////////////////////////////////////////////////////
#define NT2_FATAL(Condition,Message)

#if defined(NT2_VERBOSE)
#warning NT2 Fatal disabled
#endif

#endif

#endif
