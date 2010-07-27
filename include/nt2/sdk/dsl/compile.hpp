/******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DSL_COMPILE_HPP_INCLUDED
#define NT2_SDK_DSL_COMPILE_HPP_INCLUDED

#include <boost/mpl/apply.hpp>
#include <nt2/sdk/dsl/process_leaf.hpp>
#include <nt2/sdk/dsl/process_node.hpp>

namespace nt2 { namespace dsl
{
  //////////////////////////////////////////////////////////////////////////////
  // the compile<> template grammar perform a generic traversal of a proto AST
  // and aly Visitor specialization through tag-dispatching on each node and
  // terminal encountered. User may define new visitor easily using visitor
  // archetype;
  //
  // Grammar works as follow:
  //  * For any node, visit it
  //  * Don't visit node already transformed but return their value
  //////////////////////////////////////////////////////////////////////////////
  template<class Visitor> struct compile
  : boost::proto::or_
      < boost::proto::when< boost::proto::terminal<
                                    typename boost::mpl::apply< Visitor
                                                              , boost::proto::_
                                                              >::type
                                                  >
                          , boost::proto::_value
                          >
      , boost::proto::when<boost::proto::_,details::traversal<Visitor>()>
      >
  {};
} }

#endif
