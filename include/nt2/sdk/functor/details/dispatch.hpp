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
  template<class Tag,class Category,class Info=void>
  struct dispatch : boost::mpl::_1 {};
} }

namespace nt2 { namespace meta
{
  template<class Tag,class Category>
  struct  make_dispatch_list
  {
    typedef boost::mpl::if_ < meta::enable_dispatch<Tag,Category,boost::mpl::_2>
                            , boost::mpl::push_back<boost::mpl::_1,boost::mpl::_2>
                            , boost::mpl::_1
                            > selector;

    typedef typename  boost::mpl::fold< boost::mpl::
                                        vector10< nt2::uint8_t  , nt2::int8_t
                                                , nt2::uint16_t , nt2::int16_t
                                                , nt2::uint32_t , nt2::int32_t
                                                , nt2::uint64_t , nt2::int64_t
                                                , float         , double
                                                >
                                      , boost::mpl::vector<>
                                      , selector
                                      >::type base;

    typedef typename  boost::mpl::fold< functors::hierarchies
                                      , base, selector
                                      >::type type;
  };

  template<class Tag, class Category,class Info>
  struct dispatch
  {
    typedef functors::dispatch<Tag,Category,Info> dispatcher;

    template<class Sig> struct result;

    template<class This,class A0>
    struct result<This(A0)>
    {
      typedef typename make_dispatch_list<Tag,Category>::type   pool;
      typedef typename boost::mpl::apply1 < dispatcher
                                          , typename strip<A0>::type
                                          >::type               base;
      typedef typename meta::find_type<base, pool>::type        hierarchy_type;
      typedef functors::call<Tag,Category,hierarchy_type,Info>  type;
    };

    template<class This,class A0,class A1>
    struct result<This(A0,A1)>
    {
      typedef typename make_dispatch_list<Tag,Category>::type pool;
      typedef typename boost::mpl::apply2 < dispatcher
                                          , typename strip<A0>::type
                                          , typename strip<A1>::type
                                          >::type               base;
      typedef typename meta::find_type<base, pool>::type        hierarchy_type;
      typedef functors::call<Tag,Category,hierarchy_type,Info>  type;
    };

    template<class This,class A0,class A1,class A2>
    struct result<This(A0,A1,A2)>
    {
      typedef typename make_dispatch_list<Tag,Category>::type pool;
      typedef typename boost::mpl::apply3 < dispatcher
                                          , typename strip<A0>::type
                                          , typename strip<A1>::type
                                          , typename strip<A2>::type
                                          >::type               base;
      typedef typename meta::find_type<base, pool>::type        hierarchy_type;
      typedef functors::call<Tag,Category,hierarchy_type,Info>  type;
    };

    template<class This,class A0,class A1,class A2,class A3>
    struct result<This(A0,A1,A2,A3)>
    {
      typedef typename make_dispatch_list<Tag,Category>::type pool;
      typedef typename boost::mpl::apply4 < dispatcher
                                          , typename strip<A0>::type
                                          , typename strip<A1>::type
                                          , typename strip<A2>::type
                                          , typename strip<A3>::type
                                          >::type               base;
      typedef typename meta::find_type<base, pool>::type        hierarchy_type;
      typedef functors::call<Tag,Category,hierarchy_type,Info>  type;
    };
  };
} }

#endif
