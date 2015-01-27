//==============================================================================
//          Copyright 2015 J.T.  Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_BITWISE_FUNCTIONS_GENERIC_SWAPBYTES_HPP_INCLUDED
#define BOOST_SIMD_BITWISE_FUNCTIONS_GENERIC_SWAPBYTES_HPP_INCLUDED

#include <boost/simd/bitwise/functions/swapbytes.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT( swapbytes_, tag::cpu_
                          , (A0)
                          , (generic_< ints8_<A0> >)
                          )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return a0;
    }
  };
  BOOST_DISPATCH_IMPLEMENT( swapbytes_, tag::cpu_
                          , (A0)
                          , (generic_< ints16_<A0> >)
                          )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      int8_t i[2];
      memcpy(&i, &a0, sizeof(a0));
      std::swap(i[0], i[1]);
      return bitwise_cast<A0>(i);
    }
  };
  BOOST_DISPATCH_IMPLEMENT( swapbytes_, tag::cpu_
                          , (A0)
                          , (generic_< type32_<A0> >)
                          )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      int8_t i[4];
      memcpy(&i, &a0, sizeof(a0));
      std::swap(i[0], i[3]);
      std::swap(i[1], i[2]);
      return bitwise_cast<A0>(i);
    }
  };
  BOOST_DISPATCH_IMPLEMENT( swapbytes_, tag::cpu_
                          , (A0)
                          , (generic_< type64_<A0> >)
                          )
  {
    typedef A0 result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      int8_t i[8];
      memcpy(&i, &a0, sizeof(a0));
      std::swap(i[0], i[7]);
      std::swap(i[1], i[6]);
      std::swap(i[2], i[5]);
      std::swap(i[3], i[4]);
      return bitwise_cast<A0>(i);
    }
  };
} } }

#endif
