//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE2_ALL_HPP_INCLUDED
#define NT2_TOOLBOX_REDUCTION_FUNCTION_SIMD_SSE_SSE2_ALL_HPP_INCLUDED

#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/cardinal_of.hpp>
#include <nt2/include/functions/hmsb.hpp>
#include <nt2/include/functions/split.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <boost/fusion/tuple.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::all_, tag::cpu_,
                      (A0),
                      ((simd_<arithmetic_<A0>,tag::sse_>))
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::all_(tag::simd_<tag::arithmetic_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>    { typedef bool type; };

    NT2_FUNCTOR_CALL(1)
    {
      return hmsb(is_eqz(a0)) == 0;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint8_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::all_, tag::cpu_,
                      (A0),
                      ((simd_<uint8_<A0>,tag::sse_>))
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::all_(tag::simd_<tag::uint8_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>    { typedef bool type; };

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type                            stype;
      typedef typename meta::upgrade<stype>::type                           utype;
      typedef simd::native<utype,tag::sse_>                                 ttype;
      ttype a0h, a0l;
      boost::fusion::tie(a0h, a0l) = split(a0);
      return (hmsb(is_eqz(a0h)) || hmsb(is_eqz(a0l))) == 0;
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int8_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::all_, tag::cpu_,
                      (A0),
                      ((simd_<int8_<A0>,tag::sse_>))
                     );

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::all_(tag::simd_<tag::int8_, tag::sse_> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)>    { typedef bool type; };

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::scalar_of<A0>::type                            stype;
      typedef typename meta::upgrade<stype>::type                           utype;
      typedef simd::native<utype,tag::sse_>                                 ttype;
      ttype a0h, a0l;
      boost::fusion::tie(a0h, a0l) = split(a0);
      return (hmsb(is_eqz(a0h)) || hmsb(is_eqz(a0l)))== 0;
    }
  };
} }

#endif
// modified by jt the 05/01/2011
