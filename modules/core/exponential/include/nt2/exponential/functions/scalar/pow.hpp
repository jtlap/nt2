//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_EXPONENTIAL_FUNCTIONS_SCALAR_POW_HPP_INCLUDED
#define NT2_EXPONENTIAL_FUNCTIONS_SCALAR_POW_HPP_INCLUDED
#include <nt2/exponential/functions/pow.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/is_odd.hpp>
#include <nt2/include/functions/scalar/is_flint.hpp>
#include <nt2/include/functions/scalar/abs.hpp>
#include <nt2/include/functions/scalar/signnz.hpp>
#include <nt2/include/functions/scalar/is_odd.hpp>
#include <nt2/include/functions/scalar/fma.hpp>
#include <nt2/include/functions/scalar/sqr.hpp>
#include <nt2/include/functions/scalar/rec.hpp>
#include <nt2/include/functions/scalar/oneplus.hpp>
#include <nt2/include/functions/scalar/shr.hpp>
#include <nt2/include/functions/scalar/is_eqz.hpp>
#include <nt2/include/functions/scalar/is_gtz.hpp>
#include <nt2/include/functions/scalar/is_ltz.hpp>
#include <nt2/include/functions/scalar/is_inf.hpp>
#include <nt2/include/functions/scalar/copysign.hpp>
#include <nt2/include/functions/scalar/oneminus.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/inf.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/minf.hpp>
#include <nt2/include/constants/zero.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                            , (A0)
                            , (scalar_< double_<A0> >)
                              (scalar_< double_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      bool ltza0 = a0 < Zero<A0>();
      if( (a0 == a1 && a0 == Minf<A0>()) ||  (ltza0 && !is_flint(a1)) )
        return Nan<A0>();

      A0 res = ::pow(nt2::abs(a0), a1);
      return  (ltza0&&nt2::is_odd(a1)) ? -res : res;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                            , (A0)
                            , (scalar_< single_<A0> >)
                              (scalar_< single_<A0> >)
                            )
  {

    typedef A0 result_type;

    NT2_FUNCTOR_CALL_REPEAT(2)
    {
      bool ltza0 = a0 < Zero<A0>();
      if((a0 == a1 && a0 == Minf<A0>()) || (ltza0 && !is_flint(a1)) )
        return Nan<A0>();

      A0 res =  ::powf(nt2::abs(a0), a1);
      return  (ltza0&&nt2::is_odd(a1)) ? -res : res;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pow_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_< floating_<A0> >)
                              (scalar_< integer_<A1> >)
                            )
  {
    typedef A0 result_type;

    NT2_FUNCTOR_CALL(2)
    {
      if (is_eqz(a1)) return One<result_type>();
      bool isodda1 = is_odd(a1);
      result_type x = nt2::abs(a0);
      if (is_eqz(a0)) return (is_gtz(a1)) ? a0 : isodda1 ? rec(a0) : Inf<result_type>();
      if (x == Inf<A0>()) return (isodda1&&is_ltz(a0)) ? -x : x;
      A1 sign_n = signnz(a1);
      A1 n = nt2::abs(a1);

      result_type n_oddf = is_odd(n);
      result_type nf = n_oddf;

      result_type y = madd(n_oddf,x,oneminus(n_oddf));
      result_type w = x;
      n >>= 1;

      while( n )
      {
        w =sqr( w);
        n_oddf = is_odd(n);
        y = y*madd(n_oddf,w,oneminus(n_oddf));
        n >>=1;
      }

      w = copysign(y, a0);
      y = madd(nf, w, (oneminus(nf))*y);

      w = rec(y);
      x = result_type(shr(oneplus(sign_n),1));  // 1 if positive, else 0
      return madd(x,y,(oneminus(x))*w);
    }
  };
} }
#endif
