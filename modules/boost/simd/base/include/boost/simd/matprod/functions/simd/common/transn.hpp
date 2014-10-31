//==============================================================================
//         Copyright 2014               Jean-Thierry Lapreste
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MATPROD_FUNCTIONS_SIMD_COMMON_TRANSN_HPP_INCLUDED
#define BOOST_SIMD_MATPROD_FUNCTIONS_SIMD_COMMON_TRANSN_HPP_INCLUDED

#include <boost/simd/matprod/functions/transn.hpp>
#include <boost/simd/include/functions/broadcast.hpp>
#include <boost/simd/include/functions/fma.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/fma.hpp>
#include <boost/simd/include/functions/interleave_first.hpp>
#include <boost/simd/include/functions/interleave_second.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/mpl/int.hpp>
#include <boost/static_assert.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <utility>

//  Algorithm used (unrolled)
//       for(int j=N; j >= 2 ; j/= 2)
//       {
//         if (j == N)
//         {
//           for(int I=N/2-1; I >= 0 ; --I)
//           {
//             r1[2*I  ] = interleave_first(a[I], a[I+N/2]);
//             r1[2*I+1] = interleave_second(a[I], a[I+N/2]);
//           }
//         }
//         else
//         {
//           result_type r2;
//           for(int I=N/2-1; I >= 0 ; --I)
//           {
//             r2[2*I  ] = interleave_first(r[I],  r[I+N/2]);
//             r2[2*I+1] = interleave_second(r[I],  r[I+N/2]);
//           }
//           r= std::move(r2);
//         }
//      }
// r is the transpose.

namespace boost { namespace simd {

  namespace details
  {
    template < size_t N, class A, class R, size_t I> struct  do_interleave
    {

      BOOST_FORCEINLINE void operator()( A const& in,  R& out)
      {
        out[2*I-2] = interleave_first(in[I-1], in[I+N/2-1]);
        out[2*I-1] = interleave_second(in[I-1], in[I+N/2-1]);
        do_interleave <N, A, R, I-1>()(in, out);
      }
    };
    template <size_t N, class A, class R> struct  do_interleave < N, A, R, 0 >
    {

      BOOST_FORCEINLINE void operator()( A const& ,  R& ){ }
    };


    template <size_t N,  size_t J, class A, class R> struct  do_transpose
    {
      typedef typename dispatch::meta::strip<R>::type  rtype;

      BOOST_FORCEINLINE void operator()( A const& a, R& r)
      {
        details::do_transpose<N, J/2, A, R>()(a, r);
        rtype r2;
        details::do_interleave<N, A, R, N/2>()(r, r2);
        r = std::move(r2);
      }
    };

    template <size_t N, class A, class R> struct  do_transpose<N, 2, A, R>
    {

      BOOST_FORCEINLINE void operator()( A const& a, R& r)
      {
        details::do_interleave<N, A, R, N/2>()(a, r);
      }
    };


   }

namespace ext
{


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::transn_
                                    , boost::simd::tag::cpu_
                                    , (A)(X)
                                    , ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<typename A::value_type>::value>>
                                       ))
                                    )

  {
    typedef typename dispatch::meta::strip<A>::type  result_type;
    typedef typename result_type::value_type  vtype;

    BOOST_FORCEINLINE  result_type operator()(const A& a) const
    {
      static const int N = meta::cardinal_of<vtype>::value;
      result_type r;

       details::do_transpose<N, N, A, result_type>()(a, r);
       return r;
    }
  };


} } }

#endif
