/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_EXPRESSION_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_EXPRESSION_HPP_INCLUDED

#include <nt2/sdk/simd/meta/extension_of.hpp>
#include <nt2/sdk/dsl/proto/extends.hpp>

namespace nt2 { namespace simd
{
  ////////////////////////////////////////////////////////////////////////////
  // Here is the domain-specific expression wrapper
  ////////////////////////////////////////////////////////////////////////////
  template<class Expr,class Type,class Cardinal, class Dummy>
  struct expression
  {
    typedef domain<Type,Cardinal>                 domain_type;
    typedef expression<Expr,Type,Cardinal,Dummy>  self_type;
/*
    typedef expr_< domain, tag>                nt2_hierarchy_tag;
*/
    typedef Type& reference;
    typedef Type  const_reference;

    BOOST_PROTO_BASIC_EXTENDS_TPL(Expr, self_type, domain_type)

    ////////////////////////////////////////////////////////////////////////////
    // Extract element
    ////////////////////////////////////////////////////////////////////////////
    const_reference operator[](int i)     const
    {
      data<Type,Cardinal> that;
      that.evaluate(*this);
      return that[i];
    }
  };
} }

#endif
