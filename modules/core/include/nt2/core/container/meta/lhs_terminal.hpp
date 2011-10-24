//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_META_LHS_TERMINAL_HPP_INCLUDED
#define NT2_CORE_CONTAINER_META_LHS_TERMINAL_HPP_INCLUDED

#include <boost/proto/traits.hpp>
#include <boost/proto/transform.hpp>

namespace nt2 { namespace meta
{
  struct  lhs_terminal
        : boost::proto::or_<
            boost::proto::when< boost::proto::terminal< boost::proto::_ >
                              , boost::proto::_
                              >
          , boost::proto::when< boost::proto::nary_expr< boost::proto::_ >
                              , lhs_terminal ( boost::proto::_child0 )
                              >
          >
  {
  };
} }

#endif
