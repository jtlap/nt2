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
  template<class Info>
  struct call<ffs_,tag::scalar_(tag::arithmetic_),Info>
  {
    template<class Sig> struct result;
    template<class This,class A0>
    struct result<This(A0)> : 
      meta::as_integer<A0, unsigned>{};

    NT2_FUNCTOR_CALL_DISPATCH(
      1,
      A0,
      (4, (types8_,types16_,types32_,types64_))
    )

    NT2_FUNCTOR_CALL_EVAL_IF(1,  types8_)
    {
      return ::ffs(uint32_t(uint8_t(a0))); 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,  types16_)
    {
      return ::ffs(uint32_t(uint16_t(a0))); 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,  types32_)
    {
      typename meta::as_bits<A0, unsigned>::type t1 = {a0};
      return ::ffs(t1.bits); 
    }
    NT2_FUNCTOR_CALL_EVAL_IF(1,  types64_)
    {
      typename meta::as_bits<A0, unsigned>::type t1 = {a0};
      return ::ffsl(t1.bits); 
    }

  };
} }


      
#endif
