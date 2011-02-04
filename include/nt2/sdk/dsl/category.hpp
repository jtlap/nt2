/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_DSL_CATEGORY_HPP_INCLUDED
#define NT2_SDK_DSL_CATEGORY_HPP_INCLUDED

#include <nt2/sdk/meta/hierarchy_of.hpp>

namespace nt2 { namespace tag
{
  //////////////////////////////////////////////////////////////////////////////
  // Expression category tag
  //////////////////////////////////////////////////////////////////////////////
  struct expr_ {};
} }

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Proto domain hierarchy is itself. parent domain is computed from
  // proto_super_domain. If no super_domain exist, we forward to unspecified
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct  domain_
        : boost::mpl::if_< boost::is_same < typename T::proto_super_domain
                                          , boost::proto::detail::not_a_domain
                                          >
        , unspecified_<T>
        , domain_<typename T::proto_super_domain>
        >::type
  {
    typedef
    typename boost::mpl::if_< boost::is_same< typename T::proto_super_domain
                                            , boost::proto::detail::not_a_domain
                                            >
                            , unspecified_<T>
                            , domain_<typename T::proto_super_domain>
                            >::type                 parent;
    typedef T                                       type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Proto expression hierarchy is defined by its domain and the top-most
  // node for expression
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class Domain,class Node>
  struct expr_ : expr_<T,typename Domain::parent,Node>
  {
    typedef expr_<T,typename Domain::parent,Node> parent;
    typedef tag::expr_                            type(Domain,Node);
  };

  template<class T,class Domain,class Node>
  struct expr_<T,unspecified_<Domain>,Node> : unspecified_<T>
  {
    typedef unspecified_<T> parent;
    typedef tag::expr_ type(typename unspecified_<T>::type,Node);
  };
} }

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Proto domain hierarchy specialization
  //////////////////////////////////////////////////////////////////////////////
  template<class T> struct hierarchy_of<T, typename T::proto_is_domain_>
  {
    typedef meta::domain_<T> type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Proto expression hierarchy specialization
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct  hierarchy_of<T, typename T::proto_is_expr_>
  {
    typedef typename boost::proto::domain_of<T>::type         domain_type;
    typedef typename boost::proto::result_of::value<T>::type  value_type;
    typedef meta::expr_< T
                       , typename meta::hierarchy_of<domain_type>::type
                       , typename meta::hierarchy_of<value_type>::type
                       >                                      type;
  };
} }

#endif
