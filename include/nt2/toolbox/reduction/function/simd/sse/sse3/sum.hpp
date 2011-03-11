//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE3_SUM_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE3_SUM_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <boost/fusion/tuple.hpp>
#include <boost/fusion/include/fold.hpp>
#include <nt2/sdk/meta/strip.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::sum_, tag::cpu_,
                      (A0),
                      ((simd_<arithmetic_<A0>,tag::sse_>))
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::sum_(tag::simd_<tag::arithmetic_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename meta::scalar_of<A0>::type                 base;
      typedef typename std::tr1::result_of<meta::arithmetic(base)>::type  type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      return boost::fusion::fold(a0,0,functor<tag::plus_>());
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::sum_, tag::cpu_,
                      (A0),
                      ((simd_<double_<A0>,tag::sse_>))
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::sum_(tag::simd_<tag::double_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename meta::scalar_of<A0>::type                 type;
    };

    NT2_FUNCTOR_CALL(1) {
      A0 b1 = {_mm_hadd_pd (a0, Zero<A0>())};
      double r;
      _mm_store_sd(&r, b1);
      return r;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::sum_, tag::cpu_,
                      (A0),
                      ((simd_<float_<A0>,tag::sse_>))
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::sum_(tag::simd_<tag::float_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename meta::scalar_of<A0>::type   type;
    };

    NT2_FUNCTOR_CALL(1)
    {
      A0 b1 = {_mm_hadd_ps (a0, Zero<A0>())};
      b1 = _mm_hadd_ps (b1, Zero<A0>());
      float r;
      _mm_store_ss(&r, b1);
      return r;
    }
  };
} }

#endif
// modified by jt the 05/01/2011
