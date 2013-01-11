//==============================================================================
//         Copyright 2003 - 2013   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_MEMORY_META_ALIGN_PTR_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_META_ALIGN_PTR_INCLUDED

/*!
  @file
  @brief Defines and implements align_ptr function
**/

#include <boost/simd/sdk/config/compiler.hpp>
#include <boost/simd/sdk/simd/preprocessor/repeat.hpp>

namespace boost { namespace simd {  namespace meta
{
  /*!
    @brief Apply alignment attribute to type

    Return the compiler specific, attribute ridden version of @c Type so it
    is recognized as being aligned on a boundary equal to @c Alignment.

    @tparam T Type to mark as aligned.
    @tparam Alignment Power of 2 unsigned integer boundary
  **/
  template<typename T, std::size_t Alignment>
  struct align_ptr;

#if defined(__INTEL_COMPILER)

#define M0(z,n,t)                                                              \
template<typename T>                                                           \
struct align_ptr<T,n>                                                          \
{                                                                              \
  typedef T __attribute__ (( aligned ((n)) )) base;                            \
  typedef base*                               type;                            \
                                                                               \
  static type value(T* const pointer)                                          \
  {                                                                            \
    __assume_aligned(pointer, n);                                              \
    return static_cast<type>(pointer);                                         \
  }                                                                            \
};                                                                             \
/**/

  BOOST_SIMD_PP_REPEAT_POWER_OF_2(M0, ~)

#undef M0

#elif defined(BOOST_SIMD_COMPILER_GCC_LIKE)

  template<typename T, std::size_t Alignment>
  struct align_ptr
  {
    #if (BOOST_SIMD_GCC_VERSION >= 40300) || defined(__clang__)
    typedef T __attribute__ (( aligned ((Alignment)) )) base;
    #else
    typedef T                                           base;
    #endif

    typedef base*                               type;

    static type value(T* const pointer)
    {
      #if (BOOST_SIMD_GCC_VERSION >= 40700)
      return static_cast<type>(__builtin_assume_aligned(pointer, Alignment));
      #else
      return static_cast<type>(pointer);
      #endif
    }
  };

#elif defined(BOOST_SIMD_COMPILER_MSVC)

#define M0(z,n,t)                                                              \
template<typename T>                                                           \
struct align_ptr<T,n>                                                          \
{                                                                              \
  typedef T __declspec(align(n))  base;                                        \
  typedef base*                   type;                                        \
                                                                               \
  static type value(T* const pointer)                                          \
  {                                                                            \
    __assume(pointer % n == 0);                                                \
    return static_cast<type>(pointer);                                         \
  }                                                                            \
};                                                                             \
/**/

  BOOST_SIMD_PP_REPEAT_POWER_OF_2(M0, ~)

#undef M0

#else

  template<typename T, std::size_t Alignment>
  struct align_ptr;
  {
    typedef T* type

    static type value(T* const pointer)
    {
      return static_cast<type>(pointer);
    }
  };

#endif

} } }

#endif
