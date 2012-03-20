//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_DSL_GRAMMAR_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DSL_GRAMMAR_HPP_INCLUDED

#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/meta/is_container.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <boost/dispatch/meta/lambda_terminal.hpp>
#include <boost/simd/sdk/dsl/is_assignment_expression.hpp>

namespace nt2 { namespace tag { struct box_; } }

namespace nt2 { namespace container
{
  //============================================================================
  // NT2 container grammar accept :
  //  - any container
  //  - any scalar value
  //  - the _ operator
  //  - the as_<> helper
  //  - the box helper
  //  - any oerations except for low-level ones and assignment
  //============================================================================
  struct  grammar
        : boost::proto
          ::or_ < boost::dispatch::
                  lambda_terminal< meta::is_container<boost::proto::_value> >
                , boost::dispatch::
                  lambda_terminal< boost::is_arithmetic<boost::proto::_value> >
                , boost::proto::terminal<colon_>
                , boost::proto::terminal< meta::as_<boost::proto::_> >
                , boost::proto::nullary_expr<tag::box_, boost::proto::_>
                , boost::proto::
                  and_< boost::proto::
                        nary_expr < boost::proto::_
                                  , boost::proto::vararg< grammar >
                                  >
                      , boost::proto::
                        not_< boost::proto::or_ < boost::proto::
                                                  address_of< grammar >
                                                , boost::proto::
                                                  dereference< grammar >
                                                , boost::simd::meta::
                                                  assignment_operators
                                                >
                            >
                      >
                > {};
} }

#endif
