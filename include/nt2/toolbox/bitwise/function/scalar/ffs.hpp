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


namespace nt2 { namespace functors
{

  //  no special validate for ffs

  /////////////////////////////////////////////////////////////////////////////
  // Compute ffs(const A0& a0)
  /////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types8_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<ffs_,tag::scalar_(tag::arithmetic_),types8_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      return ::ffs(uint32_t(uint8_t(a0))); 
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types16_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<ffs_,tag::scalar_(tag::arithmetic_),types16_,Info> : callable
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL(1)
    {
      return ::ffs(uint32_t(uint16_t(a0))); 
    }
  };


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types32_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<ffs_,tag::scalar_(tag::arithmetic_),types32_,Info> : callable
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


  /////////////////////////////////////////////////////////////////////////////
  // Implementation when type A0 is types64_
  /////////////////////////////////////////////////////////////////////////////
  template<class Info>
  struct  call<ffs_,tag::scalar_(tag::arithmetic_),types64_,Info> : callable
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

#endif
/// Revised by jt the 15/11/2010
