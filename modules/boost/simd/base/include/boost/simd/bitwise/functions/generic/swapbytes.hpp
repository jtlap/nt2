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
      typedef union { A0 a; int8_t i[2]; } trick;
      trick t;
      t.a = a0;
      std::swap(t.i[0], t.i[1]);
      return t.a;
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
      typedef union { A0 a; int8_t i[4]; } trick;
      trick t;
      t.a = a0;
      std::swap(t.i[0], t.i[3]);
      std::swap(t.i[1], t.i[2]);
      return t.a;
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
      typedef union { A0 a; int8_t i[8]; } trick;
      trick t;
      t.a = a0;
      std::swap(t.i[0], t.i[7]);
      std::swap(t.i[1], t.i[6]);
      std::swap(t.i[2], t.i[5]);
      std::swap(t.i[3], t.i[4]);
      return t.a;
    }
  };
} } }

#endif
