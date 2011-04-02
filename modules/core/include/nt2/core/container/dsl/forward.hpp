/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_CONTAINER_DSL_FORWARD_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_FORWARD_HPP_INCLUDED

#include <boost/proto/proto.hpp>
#include <nt2/core/settings/meta/settings.hpp>
#include <nt2/core/container/details/forward.hpp>

namespace nt2 { namespace container
{
  struct grammar;
  template<class Tag, class Dimension>                struct domain;
  template<class Tag, class Dimension>                struct generator;
  template<class Expression,class Tag,class Settings> struct expression;

  template< class Type
          , class Settings = nt2::settings()
          , class Dummy    = boost::proto::is_proto_expr
          >
  struct table;
} }

#endif
