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

#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/core/container/meta/is_block.hpp>
#include <boost/dispatch/meta/lambda_terminal.hpp>

namespace nt2 { namespace container
{
  //============================================================================
  // Anything goes in the grammar except for low level operators
  //============================================================================
  struct  grammar
        : boost::proto
          ::or_ <
                  boost::dispatch::
                  lambda_terminal< is_block<boost::proto::_value> >
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
                                                >
                            >
                      >
                > {};
} }

#endif
