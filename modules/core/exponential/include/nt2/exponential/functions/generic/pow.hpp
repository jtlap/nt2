//==============================================================================
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 NUMSCALE SAS
//         Copyright 2015        J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_GENERIC_POW_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_GENERIC_POW_HPP_INCLUDED

#include <nt2/exponential/functions/pow.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/negif.hpp>
#include <nt2/include/functions/simd/is_ltz.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/bitwise_cast.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/scalar/is_odd.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/sdk/meta/as_logical.hpp>
#include <nt2/sdk/meta/as_unsigned.hpp>
#include <boost/simd/operator/functions/details/assert_utils.hpp>
#include <boost/assert.hpp>
#include <boost/dispatch/meta/mpl.hpp>

namespace nt2
{
  namespace details
  {
    template < long N, bool P = (N > 0), bool O = (N&1l)> struct spow
    {
      template<class result_type>
      void operator()(const result_type & a0, result_type & result) const
      {
        result *= a0;
        spow<(N >> 1l)>()(sqr(a0), result);
      }
    };
    template < long N > struct spow < N, true, false >
    {
      template<class result_type>
      void operator()(const result_type & a0, result_type & result) const
      {
        spow<(N >> 1l)>()(sqr(a0), result);
      }
    };
    template < > struct spow<0, false, true>
    {
      template<class result_type>
      void operator()(const result_type &, result_type &) const
      {
        // do nothing
      }
    };
    template < long N, bool O> struct spow<N, false, O>
    {
      template<class result_type>
      void operator()(const result_type & a0, result_type & result) const
      {
        result =  rec(spow<-N>()(a0));
      }
    };
    template <> struct spow<0, false, false>
    {
      template<class result_type>
      void operator()(const result_type &, result_type &) const
      {
        // do nothing
      }
    };
  }

  namespace ext
  {
    BOOST_DISPATCH_IMPLEMENT  ( pow_, tag::cpu_
                              , (A0)(A1)
                              , (generic_< arithmetic_<A0> >)
                                (mpl_integral_< scalar_< integer_<A1> > >)
                              )
    {
      typedef A0 result_type;

      BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1&)
      {
        result_type result = One<result_type>();
        details::spow<A1::value>()(a0, result);
        return result;
      }
    };

    BOOST_DISPATCH_IMPLEMENT  ( pow_, tag::cpu_
                              , (A0)(A1)(X)
                              , ((simd_< arithmetic_<A0>, X>))
                                (mpl_integral_< scalar_< integer_<A1> > >)
                              )
    {
      typedef A0 result_type;

      BOOST_FORCEINLINE result_type operator()(const A0& a0, const A1&)
      {
        result_type result = One<result_type>();
        details::spow<A1::value>()(a0, result);
        return result;
      }
    };

    BOOST_DISPATCH_IMPLEMENT  ( pow_, tag::cpu_
                              , (A0)(A1)
                              , (generic_< arithmetic_<A0> >)
                                (scalar_< uint_<A1> >)
                              )
    {
      typedef A0 result_type;

      NT2_FUNCTOR_CALL(2)
      {
        A0 base = a0;
        A1 exp = a1;

        result_type result = One<result_type>();
        while(exp)
        {
          if(is_odd(exp))
            result *= base;
          exp >>= 1;
          base = sqr(base);
        }

        return result;
      }
    };

    BOOST_DISPATCH_IMPLEMENT  ( pow_, tag::cpu_
                              , (A0)(A1)
                              , (generic_< integer_<A0> >)
                                (generic_< int_<A1> >)
                              )
    {
      typedef A0 result_type;

      BOOST_FORCEINLINE NT2_FUNCTOR_CALL(2)
      {
        BOOST_ASSERT_MSG( boost::simd::assert_all(a1 >= 0), "integral pow with signed exponent" );

        typedef typename meta::as_unsigned<A1>::type utype;
        return pow(a0, bitwise_cast<utype>(a1));
      }
    };


    BOOST_DISPATCH_IMPLEMENT  ( pow_, tag::cpu_
                              , (A0)(A1)
                              , (generic_< floating_<A0> >)
                                (generic_< int_<A1> >)
                              )
    {
      typedef A0 result_type;

      NT2_FUNCTOR_CALL(2)
      {
        typedef typename meta::as_unsigned<A1>::type utype;
        typename meta::as_logical<A1>::type ltza1 = is_ltz(a1);
        result_type p = pow(a0, bitwise_cast<utype>(negif(ltza1, a1)));
        return if_else(ltza1, rec(p), p);
      }
    };
  }
}

#endif
