//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_POPCNT_HPP_INCLUDED
#define NT2_TOOLBOX_BITWISE_FUNCTION_SCALAR_POPCNT_HPP_INCLUDED
#include <nt2/sdk/constant/digits.hpp>

#include <nt2/include/functions/lo.hpp>
#include <nt2/include/functions/hi.hpp>
#include <nt2/include/functions/sbits.hpp>
#include <nt2/sdk/meta/as_integer.hpp>


/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::popcnt_, tag::cpu_,
                        (A0),
                        (arithmetic_<A0>)
                       )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::popcnt_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> :meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      return __builtin_popcount(a0); //& Mone<A0>());
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is double
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::popcnt_, tag::cpu_,
                        (A0),
                        (double_<A0>)
                       )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::popcnt_(tag::double_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> :meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      int64_t v = sbits(a0);
      return  __builtin_popcount( hi(v) )
            + __builtin_popcount( lo(v) );
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is float
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::popcnt_, tag::cpu_,
                        (A0),
                        (float_<A0>)
                       )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::popcnt_(tag::float_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> :meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      return __builtin_popcount(sbits(a0));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int8_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::popcnt_, tag::cpu_,
                        (A0),
                        (int8_<A0>)
                       )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::popcnt_(tag::int8_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> :meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      return __builtin_popcount(a0 & 0xFF);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int16_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::popcnt_, tag::cpu_,
                        (A0),
                        (int16_<A0>)
                       )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::popcnt_(tag::int16_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> :meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      return __builtin_popcount(a0 & 0xFFFF);
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is int64_t
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::popcnt_, tag::cpu_,
                        (A0),
                        (int64_<A0>)
                       )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::popcnt_(tag::int64_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
      struct result<This(A0)> :meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      return  __builtin_popcount( hi(a0) )
            + __builtin_popcount( lo(a0) );
    }
  };
} }

#endif
// modified by jt the 26/12/2010