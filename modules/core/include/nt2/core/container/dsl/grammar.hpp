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
#include <nt2/dsl/functions/terminal.hpp>
#include <boost/dispatch/meta/is_scalar.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <boost/dispatch/meta/lambda_terminal.hpp>
#include <boost/simd/sdk/dsl/is_assignment_expression.hpp>

namespace nt2 { namespace container
{
  //============================================================================
  // NT2 container grammar accepts :
  //============================================================================
  struct  grammar
        : boost::proto
          ::or_ <
                  //============================================================
                  //  - any container     (types registered as such)
                  //  - any scalar value  (types with scalar_ hierarchy)
                  //============================================================
                    boost::proto
                    ::or_ < boost::dispatch::
                            lambda_terminal < meta::
                                            is_container<boost::proto::_value>
                                            >
                          , boost::dispatch::
                            lambda_terminal < boost::dispatch::meta::
                                              is_scalar<boost::proto::_value>
                                            >
                          >
                  //============================================================
                  //  - the _ object
                  //  - the end_ object
                  //  - the begin_ object
                  //  - the as_ helper
                  //============================================================
                  , boost::proto
                    ::or_ < boost::proto::terminal<colon_>
                          , boost::proto::terminal< extremum<false> >
                          , boost::proto::terminal< extremum<true> >
                          , boost::proto::terminal< meta::as_<boost::proto::_> >
                          >
                  //============================================================
                  //  - the box helper
                  //  - the dereference terminal
                  //============================================================
                  , boost::proto
                    ::or_ < boost::proto::
                                nullary_expr<tag::box_, boost::proto::_>
                          , boost::proto::
                                nullary_expr< boost::proto::tag::dereference
                                            , boost::proto::_
                                            >
                          >
                  //============================================================
                  //  - any operators and functions calls
                  //============================================================
                , boost::proto::
                  and_< boost::proto::
                        nary_expr < boost::proto::_
                                  , boost::proto::vararg< grammar >
                                  >
                        //======================================================
                        //  Except for:
                        // - address_of operator  (stl compliance)
                        // - dereference operator (stl compliance)
                        // - assignment operators (handled directly)
                        //======================================================
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
