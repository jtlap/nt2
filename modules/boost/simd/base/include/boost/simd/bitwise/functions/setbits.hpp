//==============================================================================
//          Copyright 2015 J.T.  Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_SETBITS_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_SETBITS_HPP_INCLUDED
#include <boost/simd/include/functor.hpp>
#include <boost/dispatch/include/functor.hpp>

namespace boost { namespace simd { namespace tag
  {
    /*!
      @brief  setbits generic tag

      Represents the setbits function in generic contexts.

      @par Models:
      Hierarchy
    **/
    struct setbits_ : ext::elementwise_<setbits_>
    {
      /// @brief Parent hierarchy
      typedef ext::elementwise_<setbits_> parent;
      template<class... Args>
      static BOOST_FORCEINLINE BOOST_AUTO_DECLTYPE dispatch(Args&&... args)
      BOOST_AUTO_DECLTYPE_BODY( dispatching_setbits_( ext::adl_helper(), static_cast<Args&&>(args)... ) )
    };
  }
  namespace ext
  {
    template<class Site>
    BOOST_FORCEINLINE generic_dispatcher<tag::setbits_, Site> dispatching_setbits_(adl_helper, boost::dispatch::meta::unknown_<Site>, ...)
    {
      return generic_dispatcher<tag::setbits_, Site>();
    }
    template<class... Args>
    struct impl_setbits_;
  }
  /*!
    @ brief set bits in destination according to the bit pattern found in source at 'at' number of bits (counted from the least significant) of size 'numbits' (counted from the least significant)

    @par semantic:
    For any given value @c x of type @c T, i  of type @c I:

    @code
    as_integer<T> r = setbits(dest, src, at, numbits);
    @endcode

    @param dest     the destination integer before the insertion
    @param src      the source integer before the insertion
    @param at       number of bits counted from the least significant where source is to be inserted
    @param numbits  how many bits of source to be inserted into dest


    @return      a value of the type of the first input. dest with src inserted

  **/
  BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::setbits_, setbits, 4)
} }

#endif
