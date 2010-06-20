/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_NT2_SDK_ERRORS_ERROR_HPP_INCLUDED
#define NT2_NT2_SDK_ERRORS_ERROR_HPP_INCLUDED

#include <nt2/sdk/errors/details/error.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <nt2/sdk/errors/details/failure.hpp>
#include <nt2/sdk/errors/details/warning.hpp>
#include <boost/preprocessor/seq/for_each.hpp>

////////////////////////////////////////////////////////////////////////////////
// No exception means no error unless they got requalified
////////////////////////////////////////////////////////////////////////////////
#include <boost/config.hpp>
#if defined(BOOST_NO_EXCEPTIONS)
#if defined( NT2_VERBOSE )
#warning Exceptions globally disabled
#endif
#define NT2_DISABLE_ERRORS
#endif

////////////////////////////////////////////////////////////////////////////////
// Verbose report
////////////////////////////////////////////////////////////////////////////////
#if defined( NT2_VERBOSE )
  #if defined(NT2_ERRORS_AS_WARNINGS)
    #warning Errors requalified as warnings
  #elif defined(NT2_ERRORS_AS_FAILURES)
    #warning Errors requalified as failures
  #elif defined(NT2_CUSTOM_ERRORS)
    #warning Errors handled by user
  #elif defined(NT2_DISABLE_ERRORS)
    #warning Errors disabled
  #else
    #warning Errors enabled
  #endif
#endif

////////////////////////////////////////////////////////////////////////////////
// Configuration string
////////////////////////////////////////////////////////////////////////////////
#if defined(NT2_ERRORS_AS_WARNINGS)
  #define NT2_ERRORS_CONFIG_STRING "enabled as warnings"
#elif defined(NT2_ERRORS_AS_FAILURES)
  #define NT2_ERRORS_CONFIG_STRING "enabled as failures"
#elif defined(NT2_CUSTOM_ERRORS)
  #define NT2_ERRORS_CONFIG_STRING "user-defined"
#elif defined(NT2_DISABLE_ERRORS)
  #if defined(BOOST_NO_EXCEPTIONS)
  #define NT2_ERRORS_CONFIG_STRING "globally disabled"
  #else
  #define NT2_ERRORS_CONFIG_STRING "disabled"
  #endif
#else
  #if defined(NT2_DISABLE_DAIGNOSTICS)
  #define NT2_ERRORS_CONFIG_STRING "enabled without diagnostic"
  #else
  #define NT2_ERRORS_CONFIG_STRING "enabled"
  #endif
#endif

////////////////////////////////////////////////////////////////////////////////
// Option to set exit code for failure error
////////////////////////////////////////////////////////////////////////////////
#ifndef NT2_ERROR_EXIT_CODE
#define NT2_ERROR_EXIT_CODE EXIT_FAILURE
#endif

////////////////////////////////////////////////////////////////////////////////
// try ... catch macro handlers
////////////////////////////////////////////////////////////////////////////////
#if defined(NT2_DISABLE_ERRORS)
#define NT2_TRY()
#define NT2_CATCH(X)    if(0)
#define NT2_RETHROW()
#define NT2_OTHERWISE() if(0)
#else
#define NT2_TRY()       try
#define NT2_CATCH(X)    catch( X )
#define NT2_RETHROW()   throw
#define NT2_OTHERWISE() catch( ... )
#endif

////////////////////////////////////////////////////////////////////////////////
// Option to set exit code for failure
////////////////////////////////////////////////////////////////////////////////
#ifndef NT2_ERROR_EXIT_CODE
  #define NT2_ERROR_EXIT_CODE EXIT_FAILURE
#endif

////////////////////////////////////////////////////////////////////////////////
// Errors can be requalified as warnings
////////////////////////////////////////////////////////////////////////////////
#if defined(NT2_ERRORS_AS_WARNINGS)
#define NT2_ERROR(TYPE,INFOS)                         \
NT2_EMIT_WARNING(BOOST_PP_STRINGIZE(TYPE) " thrown.") \
/**/

////////////////////////////////////////////////////////////////////////////////
// errors can be requalified as failures
////////////////////////////////////////////////////////////////////////////////
#elif defined(NT2_ERRORS_AS_FAILURES)
#define NT2_ERROR(TYPE,INFOS)                                 \
do  {  NT2_EMIT_FAILURE(BOOST_PP_STRINGIZE(TYPE) " thrown."); \
      exit(NT2_ERROR_EXIT_CODE);                              \
    } while(0)                                                \
/**/

////////////////////////////////////////////////////////////////////////////////
// Enabled errors
////////////////////////////////////////////////////////////////////////////////
#elif !defined(NT2_DISABLE_ERRORS)
#include <boost/exception/all.hpp>

#define NT2_ERROR_GENERATOR(r,d,e)                          \
<< BOOST_PP_TUPLE_ELEM(2,0,e)( BOOST_PP_TUPLE_ELEM(2,1,e) ) \
/**/

#define NT2_ERROR(TYPE,INFOS)                                                 \
BOOST_THROW_EXCEPTION ( TYPE()                                                \
                        BOOST_PP_SEQ_FOR_EACH(NT2_ERROR_GENERATOR, _, INFOS)  \
                      )                                                       \
/**/

////////////////////////////////////////////////////////////////////////////////
// Disabled errors
////////////////////////////////////////////////////////////////////////////////
#else
#define NT2_ERROR(TYPE,INFOS)
#endif

#endif
