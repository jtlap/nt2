//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_META_ALIGN_PTR_HPP_INCLUDED
#define BOOST_SIMD_META_ALIGN_PTR_HPP_INCLUDED

/*!
  @file
  @brief Defines and implements the align_ptr @metafunction
**/

#include <boost/simd/memory/parameters.hpp>
#include <boost/simd/sdk/config/compiler.hpp>
#include <boost/simd/sdk/simd/preprocessor/repeat.hpp>

namespace boost { namespace simd {  namespace meta
{
  #if defined(DOXYGEN_ONLY)
  /*!
    @brief Apply alignment attribute to type

    Return the compiler specific, attribute ridden version of @c Type so it
    is recognized as being aligned on a boundary equal to @c Alignment.

    @par Semantic:

    For any type @c T and any integral value @c Alignment:

    @code
    typedef meta::align_ptr<T,Alignment>::type r;
    @endcode

    is equivalent to:

    @code
    typedef T* aligned_attribute r;
    @endcode

    On some compilers, the @a aligned_attribute is not available and the type
    returned by meta::align_ptr will be a simple pointer to @c T.

    @par Models:

    @metafunction

    @par Example:

    @include meta/align_ptr.cpp

    @tparam T     Type to mark as aligned.
    @tparam Align Integral power of two alignment boundary. By default,
            @c Align is equal to current SIMD extension alignment boundary.
  **/
  template<typename T, std::size_t Alignment = BOOST_SIMD_CONFIG_ALIGNMENT>
  struct align_ptr
  {
    typedef T* unspecified_attribute type;
  };
  #else
  template<typename T, std::size_t Alignment = BOOST_SIMD_CONFIG_ALIGNMENT>
  struct align_ptr;
  #endif

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
    __assume((std::size_t)(pointer) % n == 0);                                 \
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
