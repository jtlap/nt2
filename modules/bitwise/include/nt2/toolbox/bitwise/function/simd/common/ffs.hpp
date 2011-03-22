//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_FFS_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SIMD_COMMON_FFS_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/include/functions/is_nez.hpp>
#include <nt2/include/functions/firstbitset.hpp>
#include <nt2/include/functions/select.hpp>
#include <nt2/include/functions/shli.hpp>
#include <nt2/include/functions/shri.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/select.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is types8_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ffs_, tag::cpu_,
                      (A0)(X),
                      ((simd_<type8_<A0>,X>))
                     );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::ffs_(tag::simd_<tag::type8_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0,unsigned>::type rtype;
      typedef typename A0::extension_type ext;
      typedef typename simd::native<uint64_t,ext> ltype;
      rtype v = firstbitset(a0);
      return b_and(is_nez(v), b_or(b_or((-( is_nez(b_and(v, integral_constant<ltype,0xAAAAAAAAAAAAAAAAll>()))))
                   ,  shli(-( is_nez(b_and(v, integral_constant<ltype,0xCCCCCCCCCCCCCCCCll>()))), 1))
              ,  shli(-( is_nez(b_and(v, integral_constant<ltype,0xF0F0F0F0F0F0F0F0ll>()))), 2))+One<rtype>());
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type64_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ffs_, tag::cpu_,
                      (A0)(X),
                      ((simd_<type64_<A0>,X>))
                     );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::ffs_(tag::simd_<tag::type64_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0,unsigned>::type rtype;
      return  simd::native_cast<rtype>(map(functor<tag::ffs_>(), simd::native_cast<rtype>(a0)));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type16_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ffs_, tag::cpu_,
                      (A0)(X),
                      ((simd_<type16_<A0>,X>))
                     );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::ffs_(tag::simd_<tag::type16_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0,unsigned>::type rtype;
      typedef typename A0::extension_type ext;
      typedef typename simd::native<uint64_t,ext> ltype;
      rtype v = firstbitset(a0);
      return  b_and(is_nez(v), b_or(b_or(b_or((-( is_nez(b_and(v, integral_constant<ltype,0xAAAAAAAAAAAAAAAAll>()))))
                       ,  shli(-( is_nez(b_and(v, integral_constant<ltype,0xCCCCCCCCCCCCCCCCll>()))), 1))
                  ,  shli(-( is_nez(b_and(v, integral_constant<ltype,0xF0F0F0F0F0F0F0F0ll>()))), 2))
                            ,  shli(-( is_nez(b_and(v, integral_constant<ltype,0xFF00FF00FF00FF00ll>()))), 3))+One<rtype>());
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type32_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ffs_, tag::cpu_,
                      (A0)(X),
                      ((simd_<type32_<A0>,X>))
                     );

namespace nt2 { namespace ext
{
  template<class X, class Dummy>
  struct call<tag::ffs_(tag::simd_<tag::type32_, X> ),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      typedef typename meta::as_integer<A0,unsigned>::type rtype;
      typedef typename A0::extension_type ext;
      typedef typename simd::native<uint64_t, ext> ltype;
      rtype v = firstbitset(a0);
      return  b_and(is_nez(v), b_or(b_or(b_or(b_or((-( is_nez(b_and(v, integral_constant<ltype,0xAAAAAAAAAAAAAAAAll>()))))
                          ,  shli(-( is_nez(b_and(v, integral_constant<ltype,0xCCCCCCCCCCCCCCCCll>()))), 1))
                       ,  shli(-( is_nez(b_and(v, integral_constant<ltype,0xF0F0F0F0F0F0F0F0ll>()))), 2))
                  ,  shli(-( is_nez(b_and(v, integral_constant<ltype,0xFF00FF00FF00FF00ll>()))), 3))
               ,  shli(-( is_nez(b_and(v, integral_constant<ltype,0xFFFF0000FFFF0000ll>()))), 4))+One<rtype>());
    }
  };
} }

#endif
// modified by jt the 04/01/2011
