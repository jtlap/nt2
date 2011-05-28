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

#ifdef BOOST_MSVC
  #include <intrin.h>
#endif

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is arithmetic_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ffs_, tag::cpu_,
                     (A0),
                     (arithmetic_<A0>)
                    )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::ffs_(tag::arithmetic_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      typename meta::as_bits<A0, unsigned>::type t1 = {a0};
      return nt2::ffs(uint32_t(t1.bits));
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type64_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ffs_, tag::cpu_,
                     (A0),
                     (type64_<A0>)
                    )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::ffs_(tag::type64_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      typename meta::as_bits<A0, unsigned>::type t1 = {a0};
      if(!t1.bits) return 0; 
    #if defined BOOST_MSVC && defined _WIN64
      unsigned long index;
      if(_BitScanForward64(&index, uint64_t(a0)))
          return index+1;
      return 0;
    #elif defined BOOST_MSVC
      unsigned long index;
      if (b_and(t1.bits, (uint64_t(-1) >> 32)))
      {
	    _BitScanForward(&index, t1.bits);
        return index+1;
      }
      if(_BitScanForward(&index, t1.bits >> 32))
        return 32+index+1;
      return 0;
    #else
      if (b_and(t1.bits, (uint64_t(-1) >> 32)))
	    return __builtin_ffs(t1.bits);
      return 32+__builtin_ffs(t1.bits >> 32);
    #endif
    }
  };
} }

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is type32_
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH(tag::ffs_, tag::cpu_,
                     (A0),
                     (type32_<A0>)
                    )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call<tag::ffs_(tag::type32_),
              tag::cpu_, Dummy> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      typename meta::as_bits<A0, unsigned>::type t1 = {a0};
    #ifdef BOOST_MSVC
      unsigned long index;
      if(_BitScanForward(&index, t1.bits))
          return index+1;
      return 0;
    #else
      return __builtin_ffs(t1.bits);
    #endif
    }
  };
} }

#endif
// modified by jt the 26/12/2010
// modified manually by jt the 26/12/2010
