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
  template <typename Grammar, typename Visitor, typename IsRule = void>
  struct algorithm_case
      : Grammar
  {};

  template <typename Rule, typename Visitor, int RulesSize = Rule::size>
  struct algorithm_case_rule;

  template <typename Rule, typename Visitor>
  struct algorithm_case_rule<Rule, Visitor, 1>
      : boost::proto::when<typename Rule::rule0, typename Visitor::template visit<typename Rule::rule0> >
  {};

  template <typename Rule, typename Visitor>
  struct algorithm_case_rule<Rule, Visitor, 2>
      : boost::proto::or_<
          boost::proto::when<typename Rule::rule0, typename Visitor::template visit<typename Rule::rule0> >
        , boost::proto::when<typename Rule::rule1, typename Visitor::template visit<typename Rule::rule1> >
      >
  {};

  template <typename Rule, typename Visitor>
  struct algorithm_case_rule<Rule, Visitor, 3>
      : boost::proto::or_<
          boost::proto::when<typename Rule::rule0, typename Visitor::template visit<typename Rule::rule0> >
        , boost::proto::when<typename Rule::rule1, typename Visitor::template visit<typename Rule::rule1> >
        , boost::proto::when<typename Rule::rule2, typename Visitor::template visit<typename Rule::rule2> >
      >
  {};

  template <typename Grammar, typename Visitor>
  struct algorithm_case<Grammar, Visitor, typename Grammar::is_rule>
      : algorithm_case_rule<Grammar, Visitor>
  {};

  template <typename Cases, typename Visitor>
  struct algorithm
      : boost::proto::switch_<algorithm<Cases, Visitor> >
  {
      template <typename Tag>
      struct case_
          : algorithm_case<typename Cases::template case_<Tag>, Visitor>
      {};
  };

  template <typename Grammar>
  struct rule
  {
      typedef void is_rule;

      static int const size = 1;
      typedef Grammar rule0;
  };

  template <typename Grammar0 = void, typename Grammar1 = void, typename Grammar2 = void, typename Dummy = void>
  struct rules;

  template <typename Grammar>
  struct rules<Grammar>
  {
      typedef void is_rule;

      static int const size = 1;
      typedef Grammar rule0;
  };

  template <typename Grammar0, typename Grammar1>
  struct rules<Grammar0, Grammar1>
  {
      typedef void is_rule;

      static int const size = 2;
      typedef Grammar0 rule0;
      typedef Grammar1 rule1;
  };

  template <typename Grammar0, typename Grammar1, typename Grammar2>
  struct rules<Grammar0, Grammar1, Grammar2>
  {
      typedef void is_rule;

      static int const size = 3;
      typedef Grammar0 rule0;
      typedef Grammar1 rule1;
      typedef Grammar2 rule2;
  };

  template <class Rule, class Actions, class Dispatch = Rule>
  struct  bind
        : boost::proto::when<Rule, typename Actions::template action<Dispatch> >
  {};

  template<class Tag, class Locality = void> struct compute;

  template<class Locality> struct visitor
  {
      template<class Rule>
      struct  visit
            : boost::proto::lazy<compute<boost::proto::tag_of<boost::proto::_>(),Locality> >
      {};
  };

  struct cases
  {
    template <typename Tag> struct case_ : rule<boost::proto::_> {};
  };

  template<class Locality>
  struct compile : algorithm<cases, visitor<Locality> > {};

/*
  template <>
  struct cases::case_<proto::tag::left_shift>
      : rule<proto::left_shift<proto::_, proto::_> >
  {};

  template <>
  struct cases::case_<proto::tag::plus>
      : rule<proto::plus<proto::multiplies<proto::_, proto::_>, proto::_> >
  {};
*/

  template<class Tag,class Locality>
  struct  compute
        : boost::proto::
          unpack< functors::functor<Tag,Locality> ( compile<Locality> )>
  {};

  template<class Locality>
  struct  compute<functors::terminal_,Locality>
        : boost::proto::
          call<functors::functor<functors::terminal_,Locality>( boost::proto::_value
                                                              , boost::proto::_state
                                                              , boost::proto::_data
                                                              )
                      >
  {};
} }

namespace boost { namespace proto
{
  template<class Locality>
  struct is_callable<nt2::dsl::compile<Locality> > : boost::mpl::true_  {};
} }

#endif
