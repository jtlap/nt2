//==============================================================================
//          Copyright 2014    Jean-Thierry Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_CUMMIN_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_COMMON_CUMMIN_HPP_INCLUDED

#include <boost/simd/swar/functions/cummin.hpp>
#include <boost/simd/include/functions/simd/insert.hpp>
#include <boost/simd/include/functions/scalar/min.hpp>
#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT ( cummin_, tag::cpu_
                           , (A0)(X)
                           , ((simd_<arithmetic_<A0>,X>))
                           )
  {
    typedef A0 result_type;
    BOOST_SIMD_FUNCTOR_CALL(1)
    {
      result_type that = a0;
      do_funroll<0, meta::cardinal_of<A0>::value>()(that);
      return that;
    }
  private:
    template < size_t I, size_t N> struct do_funroll
    {
      BOOST_FORCEINLINE void operator()(result_type & r) const
      {
        r[I+1] = boost::simd::min(r[I], r[I+1]);
        do_funroll<I+1, N>()(r);
      }
    };
    template <size_t N> struct do_funroll<N, N>
    {
       BOOST_FORCEINLINE void operator()(result_type &) const { }
    };
  };

} } }

#endif
