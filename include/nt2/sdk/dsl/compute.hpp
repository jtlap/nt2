/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DSL_COMPUTE_HPP_INCLUDED
#define NT2_SDK_DSL_COMPUTE_HPP_INCLUDED

#include <boost/proto/proto.hpp>
#include <nt2/sdk/meta/strip.hpp>
#include <nt2/sdk/functor/functor.hpp>
#include <nt2/sdk/dsl/proto/transform/unpack.hpp>

////////////////////////////////////////////////////////////////////////////////
// compile take any NT2 AST and evaluate them based on actions
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace dsl
{
  template <class Rule, class Actions, class Dispatch = Rule>
  struct  bind
        : boost::proto::when<Rule, typename Actions::template action<Dispatch> >

  template<class Actions>
  struct compiler : proto::switch_<Actions> {};

  //////////////////////////////////////////////////////////////////////////////
  // computation action
  //////////////////////////////////////////////////////////////////////////////
  template<class Locality = void>
  struct compute
  {
    template<class Tag>
    struct  case_
          : boost::proto::bind< boost::proto::_
                              , compute
                              , boost::proto::tag_of<boost::proto::_>()
                              >
    {};

    //////////////////////////////////////////////////////////////////////////////
    // Primary case captures any tag into appropriate functor and call it
    // recursively
    //////////////////////////////////////////////////////////////////////////////
    template<class Case,class Dummy=void>
    struct  action
          : boost::proto::
            unpack< functors::functor<Tag,Locality> ( boost::proto::
                                          visitor <
                                              compute_transform < boost::mpl::_1
                                                                , Locality
                                                                >
                                            , grammar<boost::mpl::_1>
                                                  >
                                        )
                >
  {};
  };

  //////////////////////////////////////////////////////////////////////////////
  // Captures terminal and forward their value, state and data to the functor
  //////////////////////////////////////////////////////////////////////////////
  template<class Locality> template<class Dummy>
  struct  compute::action<functors::terminal_,Dummy>
        : boost::proto::
          call<functors::functor< functors::terminal_
                                , Locality
                                > ( boost::proto::_value
                                  , boost::proto::_state
                                  , boost::proto::_data
                                  )
              >
  {};
} }

namespace boost { namespace proto
{
  template<class Actions>
  struct is_callable<nt2::dsl::compiler<Actions> > : boost::mpl::true_  {};
} }

#endif
