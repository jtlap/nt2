//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013          MetaScale SAS
//         Copyright 2013          Domagoj Saric, Little Endian Ltd.
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_STACK_BUFFER_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_STACK_BUFFER_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements stack allocation related macros

  Stack alignment is a tricky topic (as sketched here
  http://gcc.gnu.org/bugzilla/show_bug.cgi?id=16660 ), this file provides
  various macro that use the proper system dependent ways to define stack based
  buffer fulfilling both stack alignment and SIMD alignment is constraints.
**/
#include <boost/simd/sdk/config/arch.hpp>
#include <boost/simd/memory/aligned_on.hpp>
#include <boost/simd/memory/parameters.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <boost/assert.hpp>

#include <malloc.h>

#if defined(NT2_DOXYGEN_ONLY)
/*!
 @brief System dependent value for ::alloca alignment

 This macro is defined to be equal to the current system alignment of
 address returned by ::alloca. This macro is usually equals to current
 architecture stack alignment boundary ( as given by BOOST_SIMD_ARCH_ALIGNMENT )
 but maybe modified by some compiler/OS combination.
**/
#define BOOST_SIMD_ALLOCA_ALIGNMENT unspecified-value
#else
#if defined( _MSC_VER ) && defined( _WIN32 ) && !defined( _WIN64 )
  #define BOOST_SIMD_ALLOCA_ALIGNMENT 16
#else
  #define BOOST_SIMD_ALLOCA_ALIGNMENT BOOST_SIMD_ARCH_ALIGNMENT
#endif

#endif

/// INTERNAL ONLY
#define BOOST_SIMD_STACK_BUFFER_AUX_MAKE_RANGE( variableName, type, size )     \
boost::iterator_range<type*> const                                             \
variableName( &__##variableName##helper_pointer__[ 0 ]                         \
            , &__##variableName##helper_pointer__[ size ]                      \
            )                                                                  \
/**/

/// INTERNAL ONLY
#define BOOST_SIMD_STACK_BUFFER_AUX_BUILTIN_ALLOCA( type, size )               \
::alloca( size * sizeof( type ) )                                              \
/**/

#if BOOST_SIMD_ALLOCA_ALIGNMENT >= BOOST_SIMD_CONFIG_ALIGNMENT
/// INTERNAL ONLY
#define BOOST_SIMD_STACK_BUFFER_AUX_ALIGNED_ALLOCA                             \
BOOST_SIMD_STACK_BUFFER_AUX_BUILTIN_ALLOCA                                     \
/**/
#else
/// INTERNAL ONLY
#define BOOST_SIMD_STACK_BUFFER_AUX_ALIGNED_ALLOCA( type, size )               \
reinterpret_cast<void *>                                                       \
(                                                                              \
  (                                                                            \
    reinterpret_cast</*std::*/intptr_t>                                        \
    (                                                                          \
      ::alloca( size * sizeof( type )                                          \
    + BOOST_SIMD_CONFIG_ALIGNMENT - BOOST_SIMD_ALLOCA_ALIGNMENT )              \
    )                                                                          \
    + BOOST_SIMD_CONFIG_ALIGNMENT - BOOST_SIMD_ALLOCA_ALIGNMENT                \
  ) & ~( BOOST_SIMD_CONFIG_ALIGNMENT - 1 )                                     \
)                                                                              \
/**/
#endif

/// INTERNAL ONLY
/// Assignment construction syntax workaround for the most-vexing parse problem
#define BOOST_SIMD_STACK_BUFFER_AUX(variableName, type, size, alignment, impl) \
BOOST_SIMD_ALIGN_ON( alignment ) type * BOOST_DISPATCH_RESTRICT const          \
__##variableName##helper_pointer__  =                                          \
static_cast<type * BOOST_DISPATCH_RESTRICT const>( impl( type, size ) );       \
BOOST_ASSERT_MSG                                                               \
(                                                                              \
  reinterpret_cast<std::size_t>( __##variableName##helper_pointer__ )          \
  % alignment == 0                                                             \
,  "Alignment assumption breached in BOOST_SIMD_STACK_BUFFER"                  \
);                                                                             \
BOOST_SIMD_STACK_BUFFER_AUX_MAKE_RANGE( variableName, type, size )             \
/**/

/*!
  @brief Defines a memory buffer allocated on the stack

  This macro creates a Range named @c variableName that stores @c size
  elements of POD type @c type. Said range is allocated on the stack using
  system dependent code that enforce proper stack alignment.

  @param variableName Name of the buffer to be created
  @param type         Type stored into the buffer
  @param size         Number of element in the buffer
**/
#define BOOST_SIMD_STACK_BUFFER( variableName, type, size )                    \
BOOST_SIMD_STACK_BUFFER_AUX ( variableName, type, size                         \
                            , BOOST_SIMD_ALLOCA_ALIGNMENT                      \
                            , BOOST_SIMD_STACK_BUFFER_AUX_ALIGNED_ALLOCA       \
                            )                                                  \
/**/


/*!
  @brief Defines a memory buffer allocated on the stack suitable for SIMD

  This macro creates a Range named @c variableName that stores @c size
  elements of POD type @c type. Said range is allocated on the stack using
  system dependent code that enforce proper SIMD compatible alignment.

  @param variableName Name of the buffer to be created
  @param type         Type stored into the buffer
  @param size         Number of element in the buffer

**/
#define BOOST_SIMD_ALIGNED_STACK_BUFFER( variableName, type, size )            \
BOOST_SIMD_STACK_BUFFER_AUX ( variableName, type, size                         \
                            , BOOST_SIMD_CONFIG_ALIGNMENT                      \
                            , BOOST_SIMD_STACK_BUFFER_AUX_ALIGNED_ALLOCA       \
                            )                                                  \
/**/

#if defined(NT2_DOXYGEN_ONLY)
/*!
  @brief Defines a scoped memory buffer allocated on the stack

  This macro creates a Range named @c variableName that stores @c size
  elements of POD type @c type. Said range is allocated on the stack using
  system dependent code that enforce proper SIMD compatible alignment. This
  Range is made to be deallocated at current scope's exit.

  @param variableName Name of the buffer to be created
  @param type         Type stored into the buffer
  @param size         Number of element in the buffer

**/
#define BOOST_SIMD_SCOPED_STACK_BUFFER( variableName, type, size )
#else
#if defined( __GNUC__ )
#define BOOST_SIMD_SCOPED_STACK_BUFFER( variableName, type, size )             \
BOOST_SIMD_ALIGN_ON( BOOST_SIMD_ARCH_ALIGNMENT ) type                          \
__##variableName##helper_pointer__[ size ];                                    \
BOOST_ASSERT_MSG                                                               \
(                                                                              \
    reinterpret_cast<std::size_t>( __##variableName##helper_pointer__ )        \
  % BOOST_SIMD_ARCH_ALIGNMENT == 0,                                            \
  "Alignment assumption breached in BOOST_SIMD_SCOPED_STACK_BUFFER"            \
);                                                                             \
BOOST_SIMD_STACK_BUFFER_AUX_MAKE_RANGE( variableName, type, size )             \
/**/
#else
#define BOOST_SIMD_SCOPED_STACK_BUFFER BOOST_SIMD_STACK_BUFFER
#endif
#endif


#if defined(NT2_DOXYGEN_ONLY)
/*!
  @brief Defines a scoped memory buffer allocated on the stack suitable for SIMD

  This macro creates a Range named @c variableName that stores @c size
  elements of POD type @c type. Said range is allocated on the stack using
  system dependent code that enforce proper SIMD compatible alignment. This
  Range is made to be deallocated at current scope's exit.

  @param variableName Name of the buffer to be created
  @param type         Type stored into the buffer
  @param size         Number of element in the buffer

**/
#define BOOST_SIMD_ALIGNED_SCOPED_STACK_BUFFER( variableName, type, size )
#else
#if BOOST_SIMD_ARCH_ALIGNMENT >= BOOST_SIMD_CONFIG_ALIGNMENT
#define BOOST_SIMD_ALIGNED_SCOPED_STACK_BUFFER BOOST_SIMD_SCOPED_STACK_BUFFER
#else
#define BOOST_SIMD_ALIGNED_SCOPED_STACK_BUFFER BOOST_SIMD_ALIGNED_STACK_BUFFER
#endif
#endif

#endif
