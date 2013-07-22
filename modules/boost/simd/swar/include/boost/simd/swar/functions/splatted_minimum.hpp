//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SPLATTED_MINIMUM_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SPLATTED_MINIMUM_HPP_INCLUDED

#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd
{
  namespace tag
  {
    /*!
      @brief splatted_minimum generic tag

      Represents the splatted_minimum function in generic contexts.
    **/
    struct splatted_minimum_ : ext::unspecified_<splatted_minimum_>
    {
      /// @brief Parent hierarchy
      typedef ext::unspecified_<splatted_minimum_> parent;
    };
  }

  /*!
    @brief Splatted minimum

    Computes the splatted minimum of the element of its argument.

    @par Semantic

    Depending on the type of its arguments, splatted_minimum exhibits different
    semantics. For any type @c Type and value @c v of type @c Type:

    @code
    Type r = splatted_minimum(v);
    @endcode

    If @c Type is a SIMD value, this code is equivalent to:

    @code
    for(int i=0;i<Type::static_size;++i)
      x[i] = minimum(v);
    @endcode

    If @c Type is a scalar type, then it is equivalent to:

    @code
    r = v;
    @endcode

    @param a0 value to minimum

    @return A value containing the splatted minimum of @c a0
  */
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::splatted_minimum_, splatted_minimum, 1)
} }

#endif
