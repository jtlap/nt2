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
  // Proto expression hierarchy is defined by its domain and :
  //  - the top-most node for expression
  //  - the terminal value hierarchy (and its parent branches) for terminal
  //////////////////////////////////////////////////////////////////////////////

  //////////////////////////////////////////////////////////////////////////////
  // Case for terminals
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class Domain,class Node,bool Enable=true>
  struct expr_ : expr_<T,Domain,typename Node::parent>
  {
    typedef expr_<T,Domain,typename Node::parent> parent;
    typedef tag::expr_  type(Domain,typename Node::type);
  };

  template<class T,class Domain,class Node>
  struct expr_<T,Domain,unspecified_<Node> >
       : expr_<T
              ,typename Domain::parent
              ,typename meta::hierarchy_of<Node>::type
              >
  {
    typedef expr_ < T
                  , typename Domain::parent
                  , typename meta::hierarchy_of<Node>::type
                  >         parent;
    typedef tag::expr_      type(Domain, typename unspecified_<Node>::type);
  };

  template<class T,class Domain,class Node>
  struct expr_<T,unspecified_<Domain>,unspecified_<Node> >
       : unspecified_<T>
  {
    typedef unspecified_<T> parent;
    typedef tag::expr_      type( typename unspecified_<Domain>::type
                                , typename unspecified_<Node>::type
                                );
  };

  //////////////////////////////////////////////////////////////////////////////
  // Case for non-terminals
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class Domain,class Node>
  struct expr_<T,Domain,Node,false>
       : expr_<T,typename Domain::parent,Node,false>
  {
    typedef expr_<T,typename Domain::parent,Node,false> parent;
    typedef tag::expr_                                  type(Domain,Node);
  };

  template<class T,class Domain,class Node>
  struct expr_<T,unspecified_<Domain>,Node,false>
       : unspecified_<T>
  {
    typedef unspecified_<T> parent;
    typedef tag::expr_ type(typename unspecified_<T>::type,Node);
  };

  //////////////////////////////////////////////////////////////////////////////
  // Select between terminals and non-terminals
  //////////////////////////////////////////////////////////////////////////////
  template<class T,long Arity>
  struct expr_impl_
  {
    typedef typename boost::proto::domain_of<T>::type domain_type;
    typedef typename boost::proto::tag_of<T>::type    node_type;
    typedef expr_ < T
                  , typename meta::hierarchy_of<domain_type>::type
                  , node_type
                  , false
                  >                             type;
  };

  template<class T> struct expr_impl_<T,0>
  {
    typedef typename boost::proto::domain_of<T>::type        domain_type;
    typedef typename boost::proto::result_of::value<T>::type value_type;
    typedef expr_< T
                 , typename meta::hierarchy_of<domain_type>::type
                 , typename meta::hierarchy_of<value_type>::type
                 >                             type;
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
        : meta::expr_impl_< T, boost::proto::arity_of<T>::value >
  {};
} }

#endif
