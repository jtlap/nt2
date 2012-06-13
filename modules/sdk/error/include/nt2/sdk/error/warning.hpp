//==============================================================================
//         Copyright 2003 - 2012  LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012  LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#undef NT2_WARNING

//==============================================================================
// This file has no global header guards to be able to be used in the
// same fashion boost/assert.hpp is used.
//==============================================================================

//==============================================================================
// If warning are disabled, NT2_WARNING is a no-op
//==============================================================================
#if defined(NT2_DISABLE_WARNINGS) || defined(NDEBUG)

  #define NT2_WARNING(cond,msg) ((void)0)

//==============================================================================
// If NT2_WARNINGS_AS_ASSERTS is set, warnings turn into asserts
//==============================================================================
#elif defined(NT2_WARNINGS_AS_ASSERTS)

  #ifndef NT2_SDK_ERROR_WARNING_INCLUDED_HPP
  #define NT2_SDK_ERROR_WARNING_INCLUDED_HPP
  #include <boost/assert.hpp>

  #define NT2_WARNING(cond,msg) BOOST_ASSERT_MSG( cond, msg )
  #endif

//==============================================================================
// If NT2_ENABLE_WARNING_HANDLER is set, user must provide a function to process
// NT2_WARNING calls.
//==============================================================================
#elif defined(NT2_ENABLE_WARNING_HANDLER)

  namespace nt2
  {
    //==========================================================================
    // This warning_handler has to be user defined
    //==========================================================================
    void warning_handler( char const* cond, char const* msg
                        , char const* file, long line
                        );
  }

  #define NT2_WARNING(cond,msg)                                       \
  ((cond) ? ((void)0)                                                 \
          : ::nt2::warning_handler( #cond, msg, __FILE__, __LINE__ )  \
  )                                                                   \
  /**/

//==============================================================================
// Otherwise, warnings is handled as outputs on standard error output
//==============================================================================
#else

  #ifndef NT2_SDK_ERROR_WARNING_INCLUDED_HPP
  #define NT2_SDK_ERROR_WARNING_INCLUDED_HPP
  #include <boost/config.hpp>
  #include <cstdio>

  namespace nt2 { namespace details
  {
    BOOST_FORCEINLINE
    void warning_handler( char const* cond, char const* msg
                        , char const* file, long line
                        )
    {
      ::fprintf ( stderr, "Warning: %s failed: %s\nIn %s:%ld\n"
                        , cond, msg, file, line
                );
    }
  } }

  #define NT2_WARNING(cond,msg)                                               \
  ((cond) ? ((void)0)                                                         \
          : ::nt2::details::warning_handler( #cond, msg, __FILE__, __LINE__ ) \
  )                                                                           \
  /**/
  #endif
#endif
