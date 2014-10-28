//==============================================================================
//         Copyright 2014               Jean-Thierry Lapreste
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MATPROD_FUNCTIONS_SIMD_COMMON_MUL_NP_HPP_INCLUDED
#define BOOST_SIMD_MATPROD_FUNCTIONS_SIMD_COMMON_MUL_NP_HPP_INCLUDED

#include <boost/simd/matprod/functions/mul_np.hpp>
#include <boost/simd/matprod/functions/simd/common/mul_n1.hpp>
#include <boost/simd/include/functions/broadcast.hpp>
#include <boost/simd/include/functions/fma.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/plus.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace simd { namespace ext
{


  // return a*b
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_np_
                                    , boost::simd::tag::cpu_
                                    , (A)(B)(X)(P)
                                    , ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<typename A::value_type>::value>>
                                       ))
                                      ((array_<simd_<floating_<B>,X>, P>))
                                    )

  {
    typedef typename dispatch::meta::strip<B>::type result_type;

    BOOST_FORCEINLINE  result_type operator()(const A& a, const B & x) const
    {
      result_type r;
      do_funroll<P::value>()(a, x, r);
      return r;
    }
  private:
    template < size_t I, class dummy = void> struct do_funroll
    {
      void operator()(const A& a, const B & x, result_type & r) const
      {
        r[I-1] = mul_n1(a, x[I-1]);
        do_funroll<I-1>()(a, x, r);
      }
    };
    template <class dummy > struct do_funroll<0, dummy>
    {
      void operator()(const A& , const B & , result_type & ) const
      {
      }
    };
  };


  //a*b is added to r
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_np_
                                    , boost::simd::tag::cpu_
                                    , (A)(B)(R)(X)(P)
                                    , ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<typename A::value_type>::value>>
                                       ))
                                      ((array_<simd_<floating_<B>,X>, P>))
                                      ((array_<simd_<floating_<R>,X>, P>))
                                     )

  {
    typedef void result_type;

    BOOST_FORCEINLINE  result_type operator()(const A& a, const B & b, R & r) const
    {
      do_funroll<P::value>()(a, b, r);
    }
  private:
    template < size_t I, class dummy = void> struct do_funroll
    {
      void operator()(const A& a, const B & b, R & r) const
      {
        r[I-1] += mul_n1(a, b[I-1]);
        do_funroll<I-1>()(a, b, r);
      }
    };
    template <class dummy > struct do_funroll<0, dummy>
    {
      void operator()(const A& , const B & , R & ) const
      {
      }
    };
  };

  //alpha*a*b is added to r
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_np_
                                    , boost::simd::tag::cpu_
                                    , (ALPHA)(A)(B)(R)(X)(P)
                                    , (scalar_<arithmetic_<ALPHA>>)
                                      ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<typename A::value_type>::value>>
                                       ))
                                      ((array_<simd_<floating_<B>,X>, P>))
                                      ((array_<simd_<floating_<R>,X>, P>))
                                     )

  {
    typedef void result_type;
    typedef typename  dispatch::meta::scalar_of<typename A::value_type>::type ftype;
    BOOST_FORCEINLINE  result_type operator()(const ALPHA& alpha,const A& a, const B & b, R & r) const
    {
      do_funroll<P::value>()(ftype(alpha), a, b, r);
    }
  private:
    template < size_t I, class dummy = void> struct do_funroll
    {
      void operator()(const ftype& alpha, const A& a, const B & b, R & r) const
      {
        mul_n1(alpha, a, b[I-1], r[I-1]);
        do_funroll<I-1>()(alpha, a, b, r);
      }
    };
    template <class dummy > struct do_funroll<0, dummy>
    {
      void operator()(const ftype& , const A& , const B & , R & ) const
      {
      }
    };
  };

  //r receives beta*r+ alpha*a*b
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::mul_np_
                                    , boost::simd::tag::cpu_
                                    , (ALPHA)(A)(B)(BETA)(R)(X)(P)
                                    , (scalar_<arithmetic_<ALPHA>>)
                                      ((array_<simd_<floating_<A>,X>
                                       , boost::mpl::size_t<boost::simd::meta::cardinal_of<typename A::value_type>::value>>
                                       ))
                                      ((array_<simd_<floating_<B>,X>, P>))
                                      (scalar_<arithmetic_<BETA>>)
                                      ((array_<simd_<floating_<R>,X>, P>))
                                     )

  {
    typedef void result_type;
    typedef typename  dispatch::meta::scalar_of<typename A::value_type>::type ftype;
    BOOST_FORCEINLINE  result_type operator()(const ALPHA& alpha,const A& a, const B & b, const BETA& beta, R & r) const
    {
      do_funroll<P::value>()(ftype(alpha), a, b, ftype(beta), r);
    }
  private:
    template < size_t I, class dummy = void> struct do_funroll
    {
      void operator()(const ftype& alpha, const A& a, const B & b, const ftype& beta, R & r) const
      {
        mul_n1(alpha, a, b[I-1], beta, r[I-1]);
        do_funroll<I-1>()(alpha, a, b, beta, r);
      }
    };
    template <class dummy > struct do_funroll<0, dummy>
    {
      void operator()(const ftype& , const A& , const B & , const ftype& , R & ) const
      {
      }
    };
  };
} } }

#endif
