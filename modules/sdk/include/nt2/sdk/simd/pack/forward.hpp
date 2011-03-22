/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_FORWARD_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_FORWARD_HPP_INCLUDED

#include <boost/proto/proto.hpp>
#include <nt2/sdk/simd/meta/native_cardinal.hpp>

namespace nt2 { namespace simd
{
  template< class Type, class Cardinal> struct domain;
  template< class Type, class Cardinal> struct data;

  template< class Expression
          , class Type
          , class Cardinal
          , class Dummy = boost::proto::is_proto_expr
          >
  struct expression;

  template< class Type
          , std::size_t Cardinal  = meta::native_cardinal<Type>::value
          , class Dummy           = boost::proto::is_proto_expr
          >
  struct pack;

} }

#endif
