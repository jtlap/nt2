//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_FORWARD_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_FORWARD_HPP_INCLUDED

#include <boost/proto/proto_fwd.hpp>
#include <nt2/core/settings/settings.hpp>

namespace nt2 { namespace tag
{
  struct container_;
} }

namespace nt2
{
  template<class T, class Dummy = boost::proto::is_proto_expr>
  struct box;
}

namespace nt2 { namespace container
{
  struct colon_;

  template<class Domain>
  struct generator_transform;

  template<class Domain>
  struct size_transform;

  struct grammar;
  struct domain;

  template<class Expression, class ResultType, class Dummy = boost::proto::is_proto_expr>
  struct expression;

  template<class Type, class Settings = nt2::settings(), class Dummy = boost::proto::is_proto_expr>
  struct table;
} }

#endif
