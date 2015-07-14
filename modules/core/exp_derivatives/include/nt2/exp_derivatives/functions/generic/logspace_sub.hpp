//==============================================================================
//          Copyright 2015 J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_LOGSPACE_SUB_HPP_INCLUDED
#define NT2_EXP_DERIVATIVES_FUNCTIONS_GENERIC_LOGSPACE_SUB_HPP_INCLUDED
#include <nt2/exponential/functions/logspace_sub.hpp>
#include <nt2/exp_derivatives/functions/logspace_sub.hpp>
#include <nt2/include/functions/simd/divides.hpp>
#include <nt2/include/functions/simd/exp.hpp>
#include <nt2/include/functions/simd/multiplies.hpp>
#include <nt2/include/functions/simd/oneminus.hpp>
#include <nt2/include/functions/simd/rec.hpp>
#include <nt2/include/functions/simd/sqr.hpp>
#include <nt2/include/functions/simd/unary_minus.hpp>
#include <nt2/include/constants/mtwo.hpp>

namespace nt2 { namespace ext
{

  BOOST_DISPATCH_IMPLEMENT  ( logspace_sub_, tag::cpu_
                            , (order1)(order2)(A0)(A1)
                            , (unspecified_<order1>)
                              (unspecified_<order2>)
                              (generic_<unspecified_<A0>>)
                              (generic_<unspecified_<A1>>)
                            )
  {
    typedef A0                                                 result_type;
    typedef typename meta::scalar_of<A0>::type                         sA0;
    BOOST_FORCEINLINE result_type operator()( const order1&
                                            , const order2&
                                            , const A0& u
                                            , const A1& v) const
    {
      return compute(order1(), order2(), u, v);
    }
  private:
    BOOST_FORCEINLINE result_type compute( const boost::mpl::long_<0>
                                         , const boost::mpl::long_<0>
                                         , const A0& u, const A1& v) const
    {
      return logspace_sub(u, v);
    }

    BOOST_FORCEINLINE result_type compute( const boost::mpl::long_<0>
                                         , const boost::mpl::long_<1>
                                         , const A0& u, const A1& v) const
    {
      A0 tmp =  exp(v);
      return -rec(-tmp + exp(u))*tmp;
    }

    BOOST_FORCEINLINE result_type compute( const boost::mpl::long_<1>
                                         , const boost::mpl::long_<0>
                                         , const A0& u, const A1& v) const
    {
      A0 tmp =  exp(u);
      return rec(tmp - exp(v))*tmp;
    }

    BOOST_FORCEINLINE result_type compute( const boost::mpl::long_<0>
                                         , const boost::mpl::long_<2>
                                         , const A0& u, const A1& v) const
    {
      A0 eumv = exp(u-v);
      return -rec(Mtwo<result_type>()+eumv+rec(eumv));
    }
    BOOST_FORCEINLINE result_type compute( const boost::mpl::long_<2>
                                         , const boost::mpl::long_<0>
                                         , const A0& u, const A1& v) const
    {
      A0 eumv = exp(u-v);
      return -rec(Mtwo<result_type>()+eumv+rec(eumv));
    }


    BOOST_FORCEINLINE result_type compute( const boost::mpl::long_<1>
                                         , const boost::mpl::long_<1>
                                         , const A0& u, const A1& v) const
    {
      A0 eumv = exp(u-v);
      return -rec(Mtwo<result_type>()+eumv+rec(eumv));
    }

  };
} }


#endif
