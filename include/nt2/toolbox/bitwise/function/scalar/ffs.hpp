//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_FFS_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_FFS_HPP_INCLUDED
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_bits.hpp>



/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is types8_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ffs_, tag::cpu_,
                     (A0),
                     (types8_<A0>)
                    )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::ffs_(tag::types8_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      return ::ffs(uint32_t(uint8_t(a0)));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is types64_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ffs_, tag::cpu_,
                     (A0),
                     (types64_<A0>)
                    )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::ffs_(tag::types64_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      typename meta::as_bits<A0, unsigned>::type t1 = {a0};
      return ::ffsl(t1.bits);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is types16_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ffs_, tag::cpu_,
                     (A0),
                     (types16_<A0>)
                    )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::ffs_(tag::types16_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      return ::ffs(uint32_t(uint16_t(a0)));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is types32_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ffs_, tag::cpu_,
                     (A0),
                     (types32_<A0>)
                    )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::ffs_(tag::types32_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      typename meta::as_bits<A0, unsigned>::type t1 = {a0};
      return ::ffs(t1.bits);
    }
  };
} }

#endif
// modified by jt the 26/12/2010