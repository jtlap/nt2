//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MATPROD_FUNCTIONS_SIMD_COMMON_MUL_HN_HPP_INCLUDED
#define BOOST_SIMD_MATPROD_FUNCTIONS_SIMD_COMMON_MUL_HN_HPP_INCLUDED

#include <boost/simd/matprod/functions/mul_hn.hpp>
#include <boost/simd/include/functions/broadcast.hpp>
#include <boost/simd/include/functions/fma.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/functions/fma.hpp>
#include <boost/simd/include/functions/repeat_upper_half.hpp>
#include <boost/simd/include/functions/repeat_lower_half.hpp>
#include <boost/simd/include/functions/deinterleave_first.hpp>
#include <boost/simd/include/functions/broadcast.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/mpl/int.hpp>

//  Algorithm used for r =  a*b  a is (N/2)*(2*N) and b is (2*N)*2
//  The result r alwaysexactly fits in an simd vector of N elements
//       r =  zero<vT>
//       for(int i=0; i <N ; i++)
//       {
//         r+= rlh(a[i]*di < (2*i)%(N/2) > (b[i/(N/2)], b[i/(N/2)+2])+ ruh(a[i]*di < (2*i)/(N/2)+1 > (b[i/(N/2)], b[i/(N/2)+2]);
//       }
// where rlh is repeat_lower_half
//       ruh is repeat_upper_half
// and   di(b0, b1) is deinterleave_first(broadcast<I>(b0), broadcast<I>(b1));
// The algorithm is not dependant of the size of the simd vector, but size of the involved matrices is.

namespace boost { namespace simd {

  namespace details
  {
    template < size_t I, class A>
    BOOST_FORCEINLINE A di( A const& b0,  A const& b1)
    {
      return deinterleave_first(broadcast<I>(b0), broadcast<I>(b1));
    }

    template < size_t N, size_t I, class A, class B, class R> struct do_compute
    {
    BOOST_FORCEINLINE void operator()(const A& a, const B & b, R & r) const
      {
        static const size_t F = (2*(I-1))%(N);
        static const size_t G = (I-1)/(N/2);
        r = fma(repeat_lower_half(a[I-1]), details::di<F>(b[G],b[G+2])
               , fma(repeat_upper_half(a[I-1]), details::di<F+1>(b[G],b[G+2])
                   , r)
               );
        do_compute<N, I-1, A, B, R>()(a, b, r);
      }
    };
    template < size_t N, class A, class B, class R > struct do_compute <N, 0, A, B, R>
    {
       BOOST_FORCEINLINE void operator()(const A&  , const B &  , R &  ) const {}
    };
  }

namespace ext
{


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_hn_
                                    , boost::simd::tag::cpu_
                                    , (A)(B)(X)
                                    , ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<typename A::value_type>::value>>
                                       ))
                                      ((array_<simd_<floating_<B>,X>, boost::mpl::size_t<4>>
                                       ))
                                    )

  {
    typedef typename A::value_type  result_type;

    BOOST_FORCEINLINE  result_type operator()(const A& a, const B & b) const
    {
      static const size_t N = meta::cardinal_of<result_type>::value;
      result_type r = Zero<result_type>();
      details::do_compute<N, N, A, B, result_type>()(a, b, r);
      return r;
    }
  };


  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_hn_
                                    , boost::simd::tag::cpu_
                                    , (A)(B)(R)(X)
                                    , ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<typename A::value_type>::value>>
                                       ))
                                      ((array_<simd_<floating_<B>,X>, boost::mpl::size_t<4>>
                                       ))
                                      ((simd_<floating_<R>,X>))
                                    )

  {
    typedef void  result_type;

    BOOST_FORCEINLINE  result_type operator()(const A& a, const B &b
                                             , R& r) const
    {
      static const size_t N = meta::cardinal_of<R>::value;
      details::do_compute<N, N, A, B, R>()(a, b, r);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_hn_
                                    , boost::simd::tag::cpu_
                                    , (ALPHA)(A)(B)(R)(X)
                                    ,  (scalar_<arithmetic_<ALPHA>>)
                                      ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<typename A::value_type>::value>>
                                       ))
                                      ((array_<simd_<floating_<B>,X>, boost::mpl::size_t<4>>
                                       ))
                                      ((simd_<floating_<R>,X>))
                                    )

  {
    typedef void  result_type;
    typedef typename meta::scalar_of<typename A::value_type>::type stype;

    BOOST_FORCEINLINE  result_type operator()(const ALPHA& alpha, const A& a
                                             , const B &b
                                             , R& r) const
    {
      r += mul_hn(a, b)*stype(alpha);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_hn_
                                    , boost::simd::tag::cpu_
                                    , (ALPHA)(A)(B)(BETA)(R)(X)
                                    ,  (scalar_<arithmetic_<ALPHA>>)
                                      ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<typename A::value_type>::value>>
                                       ))
                                      ((array_<simd_<floating_<B>,X>, boost::mpl::size_t<4>>
                                       ))
                                      (scalar_<arithmetic_<BETA>>)
                                      ((simd_<floating_<R>,X>))
                                    )

  {
    typedef void  result_type;
    typedef typename meta::scalar_of<typename A::value_type>::type stype;
    BOOST_FORCEINLINE  result_type operator()(const ALPHA& alpha, const A& a
                                             , const B &b, const BETA &beta
                                             , R& r) const
    {
      r *= stype(beta);
      r += mul_hn(a, b)*stype(alpha);
    }
  };

} } }

#endif
