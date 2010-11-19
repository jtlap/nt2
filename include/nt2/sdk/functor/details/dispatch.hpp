/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_DETAILS_DISPATCH_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_DETAILS_DISPATCH_HPP_INCLUDED

#include <boost/mpl/at.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/push_back.hpp>
#include <nt2/sdk/functor/hierarchy.hpp>
#include <nt2/sdk/functor/meta/find_type.hpp>
#include <nt2/sdk/functor/details/enable_dispatch.hpp>

namespace nt2 { namespace functors
{
  //////////////////////////////////////////////////////////////////////////////
  // Default dispatch just forward the type
  //////////////////////////////////////////////////////////////////////////////
  template<class Tag,class Category,class Info = void>
  struct dispatch : boost::mpl::_1 {};
} }

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Try to match a type onto an existing hierarchy
  //////////////////////////////////////////////////////////////////////////////
  template<class Tag,class Category, class Info>
  struct  make_list
  {
    typedef boost::mpl::if_ < meta::
                              enable_dispatch<Tag,Category,boost::mpl::_2,Info>
                            , boost::mpl::push_back < boost::mpl::_1
                                                    , boost::mpl::_2
                                                    >
                            , boost::mpl::_1
                            > selector;

    typedef typename  boost::mpl::fold< functors::hierarchies
                                      , boost::mpl::vector<>
                                      , selector
                                      >::type type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Build a call<> type by trying to fit a dispatched type either on a direct
  // call<> specialization or a hierarchical call<>
  //////////////////////////////////////////////////////////////////////////////
  template<class Tag,class Base,class Category,class Info>
  struct build_caller
  {
    typedef meta::find_type < typename Base::type
                            , typename details::make_list < Tag
                                                          , Category
                                                          , Info
                                                          >::type
                            >        hierarchized;
    typedef typename
          boost::mpl::eval_if < meta::enable_dispatch < Tag
                                                      , Category
                                                      , typename Base::type
                                                      , Info
                                                      >
                              , Base
                              , hierarchized
                              >::type  hierarchy_type;

    typedef functors::call<Tag,Category,hierarchy_type,Info> type;
  };
} }

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // For any given Tag in a given Category, construct the call<> able to process
  // the current function call over said category of type by selecting the proper
  // call<> specialization among all externals specializations available.
  //////////////////////////////////////////////////////////////////////////////
  template<class Tag, class Category,class Info>
  struct dispatch
  {
    typedef functors::dispatch<Tag,Category,Info> dispatcher;

    template<class Sig> struct result;

    #define M0(z,n,t) typename strip<BOOST_PP_CAT(t,n)>::type

    #define M1(z,n,t)                                                             \
    template<class This,BOOST_PP_ENUM_PARAMS(n,class A)>                          \
    struct result<This(BOOST_PP_ENUM_PARAMS(n,A))>                                \
    {                                                                             \
      typedef BOOST_PP_CAT(boost::mpl::apply,n) < dispatcher                      \
                                                , BOOST_PP_ENUM(n,M0,A)           \
                                                >                           base; \
      typedef typename details::build_caller<Tag,base,Category,Info>::type  type; \
    };                                                                            \
    /**/

    BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_ARITY),M1,~)

    #undef M1
    #undef M0
  };
} }

#endif
