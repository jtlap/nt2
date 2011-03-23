//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_NEXTPOW2_HPP_INCLUDED
#define NT2_TOOLBOX_IEEE_FUNCTION_SIMD_COMMON_NEXTPOW2_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/constant/real.hpp>
#include <boost/fusion/tuple.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/tofloat.hpp>
#include <nt2/include/functions/toint.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/frexp.hpp>
#include <nt2/include/functions/popcnt.hpp>
#include <nt2/include/functions/group.hpp>
#include <nt2/include/functions/split.hpp>
#include <nt2/include/functions/firstbitset.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::nextpow2_, tag::cpu_,
                           (A0)(X),
                           ((simd_<arithmetic_<A0>,X>))
                          );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::nextpow2_(tag::simd_<tag::arithmetic_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
      {
      typedef typename meta::as_integer<A0, unsigned>::type utype;
      return simd::native_cast<A0>(nextpow2(simd::native_cast<utype >(abs(a0))));
      //    return seladd(is_not_equal(popcnt(abs(a0)),One<A0>()), simd::native_cast<A0>(firstbitset(abs(a0))), One<A0>());
      }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is unsigned_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::nextpow2_, tag::cpu_,
                           (A0)(X),
                           ((simd_<unsigned_<A0>,X>))
                          );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::nextpow2_(tag::simd_<tag::unsigned_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
      {
      typedef typename meta::as_real<A0>::type rtype;
      typedef typename meta::as_integer<A0, signed>::type itype;
      rtype m;
      itype p;
      boost::fusion::tie(m, p) = frexp(tofloat(a0));
      //    std::cout << "a0 " << a0 << "  p " << p<< "  m " << m << std::endl;
      return simd::native_cast<A0>(seladd(is_equal(m, Half<rtype>()), p, Mone<itype>()));
      }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint16_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::nextpow2_, tag::cpu_,
                           (A0)(X),
                           ((simd_<uint16_<A0>,X>))
                          );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::nextpow2_(tag::simd_<tag::uint16_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
      {
      typedef typename meta::scalar_of<A0>::type  stype;
      typedef typename meta::upgrade<stype>::type itype;
      typedef simd::native<itype,X>              ivtype;
      ivtype a0l, a0h;
      boost::fusion::tie(a0l, a0h) = split(a0);
      return simd::native_cast<A0>(group(nextpow2(a0l),nextpow2(a0h)));
      //seladd(is_not_equal(popcnt(abs(a0)),One<A0>()), simd::native_cast<A0>(lastbitset(abs(a0))), One<A0>());
      }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is uint8_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::nextpow2_, tag::cpu_,
                           (A0)(X),
                           ((simd_<uint8_<A0>,X>))
                          );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::nextpow2_(tag::simd_<tag::uint8_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
      {
      typedef typename meta::scalar_of<A0>::type  stype;
      typedef typename meta::upgrade<stype>::type itype;
      typedef simd::native<itype, X>             ivtype;
      ivtype a0l, a0h;
      boost::fusion::tie(a0l, a0h) = split(a0);
      return simd::native_cast<A0>(group(nextpow2(a0l),nextpow2(a0h)));
      //seladd(is_not_equal(popcnt(abs(a0)),One<A0>()), simd::native_cast<A0>(lastbitset(abs(a0))), One<A0>());
      }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is real_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::nextpow2_, tag::cpu_,
                           (A0)(X),
                           ((simd_<real_<A0>,X>))
                          );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::nextpow2_(tag::simd_<tag::real_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::strip<A0>{};

    NT2_FUNCTOR_CALL(1)
      {
      typedef typename meta::as_integer<A0>::type int_type;
      A0 m;
      int_type p;
      boost::fusion::tie(m, p) = frexp(abs(a0));
      return tofloat(seladd(is_equal(m, Half<A0>()), p, Mone<int_type>()));
      }
  };
} }

#endif
// modified by jt the 04/01/2011
