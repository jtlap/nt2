//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_MEMORY_ALIGN_PTR_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_ALIGN_PTR_INCLUDED

/*!
  @file
  @brief Defines and implements make_aligned function
**/

#include <boost/simd/sdk/memory/meta/align_ptr.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/assert.hpp>

namespace boost { namespace simd {  namespace memory
{
  /*!
    @brief Mark pointer as properly aligned

    Make the compiler's optimizer assume that a given pointer is aligned on a
    given alignment boundary. This function takes an already aligned pointer and
    flags it as aligned so the compiler can keep track of this constraint in its
    optimization pass.

    @tparam T         Type of the pointee.
    @tparam Alignment A power of 2 alignment constraint.
    @param pointer Pointer to flag. Must already be aligned on @c Alignment

    @return A properly flagged pointer equals to the input argument but with
            compiler-specific attribute added to its type.
  **/
  template<std::size_t Alignment, typename T>
  BOOST_FORCEINLINE typename meta::align_ptr<T,Alignment>::type
  align_ptr(T* const pointer)
  {
    BOOST_ASSERT_MSG
    ( boost::simd::is_aligned(pointer,Alignment)
    , "The pointer you try to mark as aligned is not aligned "
      "on the specified alignment in this context"
    );

    return meta::align_ptr<T,Alignment>::value(pointer);
  }

} } }

#endif
