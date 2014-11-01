//==============================================================================
//         Copyright 2014               Jean-Thierry Lapreste
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MATPROD_FUNCTIONS_SIMD_COMMON_MUL_NTP_HPP_INCLUDED
#define BOOST_SIMD_MATPROD_FUNCTIONS_SIMD_COMMON_MUL_NTP_HPP_INCLUDED

#include <boost/simd/matprod/functions/mul_ntp.hpp>
#include <boost/simd/matprod/functions/simd/common/mul_n1.hpp>
#include <boost/simd/include/functions/broadcast.hpp>
#include <boost/simd/include/functions/fma.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/simd/include/constants/zero.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/mpl/int.hpp>

// Algorithm used fpr r = a*tb
//       for(size_t j=0; j <P::value; j++)
//       {
//         r[j] = Zero<vtype>();
//         for(size_t i=0; i < N ; i++)
//         {
//           r[j]+= a[i]*broad(i, b[j]);
//         }
//      }
namespace boost { namespace simd {

  namespace details
  {
    template < size_t I, class M, class S> struct do_scale
    {
      void operator()(M & m, const S & s) const
      {
        m[I-1] *= s;
        do_scale<I-1, M, S>()(m, s);
      }
    };
    template <class M, class S> struct do_scale<0, M, S>
    {
      void operator()(M & , const S & ) const {}
    };
  }

namespace ext
{


  // return a*tb
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_ntp_
                                    , boost::simd::tag::cpu_
                                    , (A)(B)(X)(P)
                                    , ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<typename A::value_type>::value>>
                                       ))
                                      ((array_<simd_<floating_<B>,X>, P>))
                                    )

  {
    typedef typename dispatch::meta::strip<B>::type result_type;
    typedef typename result_type::value_type vtype;

    BOOST_FORCEINLINE  result_type operator()(const A& a, const B & b) const
    {
      result_type r;
      do_treat_lines<P::value, result_type>()(a, b, r);
      return r;
    }
  private:
    template <size_t J, class R> struct do_treat_lines
    {
      BOOST_FORCEINLINE void operator()(const A& a, const B & b, R & r) const
      {
        static const size_t N = boost::simd::meta::cardinal_of<typename A::value_type>::value;
        r[J-1] = Zero<vtype>();
        do_treat_cols<N, J-1, vtype>()(a, b, r[J-1]);
        do_treat_lines<J-1, R>()(a, b, r);
      }
    };

    template <class R> struct do_treat_lines < 0, R>
    {
      BOOST_FORCEINLINE void operator()(const A& , const B & , R & ) const
      {
      }
    };

  template < size_t I, size_t J, class R> struct do_treat_cols
    {
      BOOST_FORCEINLINE void operator()(const A& a, const B & b, R & r) const
      {
        r += a[I-1]*broadcast<I-1>(b[J]);
        do_treat_cols<I-1, J, R>()(a, b, r);
      }
    };

    template <size_t J, class R> struct do_treat_cols<0, J, R>
    {
      BOOST_FORCEINLINE void operator()(const A& , const B & , R & ) const
      {
      }
    };
  };


  //a*tb is added to r
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_ntp_
                                    , boost::simd::tag::cpu_
                                    , (A)(B)(RR)(X)(P)
                                    , ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<typename A::value_type>::value>>
                                       ))
                                      ((array_<simd_<floating_<B>,X>, P>))
                                      ((array_<simd_<floating_<RR>,X>, P>))
                                     )

  {
    typedef void result_type;
    typedef typename dispatch::meta::strip<B>::type btype;
    typedef typename btype::value_type vtype;

    BOOST_FORCEINLINE  result_type operator()(const A& a, const B & b, RR & r) const
    {
      do_treat_lines<P::value, btype>()(a, b, r);
    }
  private:
    template <size_t J, class R> struct do_treat_lines
    {
      BOOST_FORCEINLINE void operator()(const A& a, const B & b, R & r) const
      {
        static const size_t N = boost::simd::meta::cardinal_of<typename A::value_type>::value;
        do_treat_cols<N, J-1, vtype>()(a, b, r[J-1]);
        do_treat_lines<J-1, R>()(a, b, r);
      }
    };

    template <class R> struct do_treat_lines < 0, R>
    {
      BOOST_FORCEINLINE void operator()(const A& , const B & , R & ) const
      {
      }
    };

  template < size_t I, size_t J, class R> struct do_treat_cols
    {
      BOOST_FORCEINLINE void operator()(const A& a, const B & b, R & r) const
      {
        r += a[I-1]*broadcast<I-1>(b[J]);
        do_treat_cols<I-1, J, R>()(a, b, r);
      }
    };

    template <size_t J, class R> struct do_treat_cols<0, J, R>
    {
      BOOST_FORCEINLINE void operator()(const A& , const B & , R & ) const
      {
      }
    };
  };

  //alpha*a*tb is added to r
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_ntp_
                                    , boost::simd::tag::cpu_
                                    , (ALPHA)(A)(B)(RR)(X)(P)
                                    , (scalar_<arithmetic_<ALPHA>>)
                                      ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<typename A::value_type>::value>>
                                       ))
                                      ((array_<simd_<floating_<B>,X>, P>))
                                      ((array_<simd_<floating_<RR>,X>, P>))
                                     )

  {
    typedef void result_type;
    typedef typename dispatch::meta::scalar_of<typename A::value_type>::type ftype;
    typedef typename dispatch::meta::strip<B>::type btype;
    typedef typename btype::value_type vtype;
    BOOST_FORCEINLINE  result_type operator()(const ALPHA& alpha, const A& a, const B & b, RR & r) const
    {
      do_treat_lines<P::value, btype>()(ftype(alpha), a, b, r);
    }
  private:
    template <size_t J, class R> struct do_treat_lines
    {
      BOOST_FORCEINLINE void operator()(const ftype& alpha, const A& a, const B & b, R & r) const
      {
        static const size_t N = boost::simd::meta::cardinal_of<typename A::value_type>::value;
        do_treat_cols<N, J-1, vtype>()(alpha, a, b, r[J-1]);
        do_treat_lines<J-1, R>()(alpha, a, b, r);
      }
    };

    template <class R> struct do_treat_lines < 0, R>
    {
      BOOST_FORCEINLINE void operator()(const ftype&, const A& , const B & , R & ) const
      {
      }
    };

    template < size_t I, size_t J, class R> struct do_treat_cols
    {
      BOOST_FORCEINLINE void operator()(const ftype& alpha, const A& a, const B & b, R & r) const
      {
        do_treat_cols<I-1, J, R>()(alpha, a, b, r);
        r = fma(alpha, a[I-1]*broadcast<I-1>(b[J]), r);
      }
    };

    template <size_t J, class R> struct do_treat_cols<0, J, R>
    {
      BOOST_FORCEINLINE void operator()(const ftype&, const A& , const B & , R & ) const
      {
      }
    };
  };

  //r receives beta*r+ alpha*a*tb
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_ntp_
                                    , boost::simd::tag::cpu_
                                    , (ALPHA)(A)(B)(BETA)(RR)(X)(P)
                                    , (scalar_<arithmetic_<ALPHA>>)
                                      ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<typename A::value_type>::value>>
                                       ))
                                      ((array_<simd_<floating_<B>,X>, P>))
                                      (scalar_<arithmetic_<BETA>>)
                                      ((array_<simd_<floating_<RR>,X>, P>))
                                     )

  {
    typedef void result_type;
    typedef typename  dispatch::meta::scalar_of<typename A::value_type>::type ftype;
    typedef typename dispatch::meta::strip<B>::type btype;
    typedef typename btype::value_type vtype;
    BOOST_FORCEINLINE  result_type operator()(const ALPHA& alpha,const A& a, const B & b, const BETA& beta, RR & r) const
    {
      details::do_scale<P::value, RR, ftype>()(r, ftype(beta));
      do_treat_lines<P::value, RR>()(ftype(alpha), a, b, r);
    }
  private:
    template <size_t J, class R> struct do_treat_lines
    {
      BOOST_FORCEINLINE void operator()(const ftype& alpha, const A& a, const B & b, R & r) const
      {
        static const size_t N = boost::simd::meta::cardinal_of<typename A::value_type>::value;
        do_treat_cols<N, J-1, vtype>()(alpha, a, b, r[J-1]);
        do_treat_lines<J-1, R>()(alpha, a, b, r);
      }
    };

    template <class R> struct do_treat_lines < 0, R>
    {
      BOOST_FORCEINLINE void operator()(const ALPHA& , const A& , const B & , R & ) const
      {
      }
    };

    template < size_t I, size_t J, class R> struct do_treat_cols
    {
      BOOST_FORCEINLINE void operator()(const ftype& alpha, const A& a, const B & b, R & r) const
      {
        do_treat_cols<I-1, J, R>()(alpha, a, b, r);
        r = fma(alpha, a[I-1]*broadcast<I-1>(b[J]), r);
      }
    };

    template <size_t J, class R> struct do_treat_cols<0, J, R>
    {
      BOOST_FORCEINLINE void operator()(const ftype&, const A& , const B & , R & ) const
      {
      }
    };
  };
} } }

#endif
