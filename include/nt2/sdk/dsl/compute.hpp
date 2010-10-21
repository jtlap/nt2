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
    namespace detail
    {
        template<typename Rules, typename Actions, int RuleSize = Rules::count>
        struct algorithm_case_impl;

#define M0(Z, N, DATA)                                                                              \
        boost::proto::when<                                                                                \
                typename Rules::BOOST_PP_CAT(rule, N)                                                   \
              , typename Actions::template action<typename Rules::BOOST_PP_CAT(rule, N), Actions>       \
            >                                                                                           \
            /**/

#define M1(Z, N, DATA)                                                                              \
        template<typename Rules, typename Actions>                                                      \
        struct algorithm_case_impl<Rules, Actions, N>                                                   \
          : boost::proto::or_<BOOST_PP_ENUM_ ## Z(N, M0, ~) >                                                  \
        {};                                                                                             \
        /**/

        BOOST_PP_REPEAT(BOOST_PROTO_MAX_LOGICAL_ARITY, M1, ~)
        #undef M1
        #undef M0

        template<typename Grammar, typename Actions, typename IsRule = void>
        struct algorithm_case
          : boost::proto::when<
                Grammar
              , typename Actions::template action<Grammar, Actions>
            >
        {};

        template<typename Grammar, typename Actions>
        struct algorithm_case<Grammar, Actions, typename Grammar::is_rule>
          : algorithm_case_impl<Grammar, Actions>
        {};
    }

    // A collection of grammar rules. Really, we could just use proto::or_ for this purpose.
    template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_PROTO_MAX_LOGICAL_ARITY, typename Rule, void), typename Dummy = void>
    struct rules;

#define M0(Z, N, DATA)                                                                              \
        typedef BOOST_PP_CAT(Rule, N) BOOST_PP_CAT(rule, N);                                            \
        /**/

#define M1(Z, N, DATA)                                                                              \
        template<BOOST_PP_ENUM_PARAMS_Z(Z, N, typename Rule)>                                           \
        struct rules<BOOST_PP_ENUM_PARAMS_Z(Z, N, Rule)>                                                \
        {                                                                                               \
            typedef void is_rule;                                                                       \
            static int const count = N;                                                                 \
            BOOST_PP_REPEAT_ ## Z(N, M0, ~)                                                             \
        };                                                                                              \
        /**/

    BOOST_PP_REPEAT(BOOST_PROTO_MAX_LOGICAL_ARITY, M1, ~)
#undef M1
#undef M0

    // By default, just use the actions that have already been
    // associated with the grammar rules. Could be in Proto.
    struct default_actions
    {
        template<typename Rule, typename Actions>
        struct action
          : Rule
        {};
    };

    template<typename Cases, typename Actions = default_actions>
    struct algorithm
      : boost::proto::switch_<algorithm<Cases, Actions> >
    {
        template<typename Tag>
        struct case_
          : detail::algorithm_case<
                typename Cases::template case_<Tag>
              , Actions
            >
        {};
    };

  template<class Tag, class Locality>
  struct compute;

  template<class Locality>
  struct actions
  {
      template <typename Rule, typename Actions>
      struct action
        : default_actions::action<Rule, Actions>
      {};
  };

  template <typename Locality>
  struct cases
  {
    template <typename Tag> struct case_ : boost::proto::otherwise<compute<Tag, Locality> > {};
  };

  template<class Locality = void>
  struct compile : algorithm<cases<Locality>, actions<Locality> > {};

  template <class Tag, class Locality>
  struct compute
    : boost::proto::
      unpack<boost::proto::call<functors::functor<Tag, Locality> >(compile<Locality>)>
  {};

  template<class Locality>
  struct  compute<functors::terminal_,Locality>
        : boost::proto::
          call<
            functors::functor<functors::terminal_,Locality>(
                boost::proto::_value
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
  template<typename Tag, class Locality>
  struct is_callable<nt2::dsl::compute<Tag, Locality> > : boost::mpl::true_  {};
} }

#endif
