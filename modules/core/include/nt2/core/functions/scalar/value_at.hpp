//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_VALUE_AT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_VALUE_AT_HPP_INCLUDED

#include <nt2/sdk/meta/fusion.hpp>

/////////////////////////////////////////////////////////////////////////////
// Implementation when type A0 is fundamental
/////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_DISPATCH ( tag::value_at_, tag::cpu_
                      , (A0)(A1)
                      , (fundamental_<A0>)(fusion_sequence_<A1>)
                      )

namespace nt2 { namespace ext
{
  template<class Dummy>
  struct call < tag::value_at_(tag::fundamental_,tag::fusion_sequence_)
              , tag::cpu_, Dummy
              > : callable
  {
    template<class Sig> struct result;
    template<class This,class A0,class A1>
    struct result<This(A0,A1)> : meta::strip<A0> {};

    NT2_FUNCTOR_CALL(2)
    {
      /////////////////////////////////////////////////////////////////////////
      // Scalar value acts as adaptative size container, so w/e the position
      // we returnt he scalar value. Note that it is tied to the fact scalars
      // value appears as "0D" elements while their dimension is [1 1]
      /////////////////////////////////////////////////////////////////////////
      return a0;
    }
  };
} }

#endif
