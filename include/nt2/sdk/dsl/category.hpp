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

////////////////////////////////////////////////////////////////////////////////
// Basic category registration
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/hierarchy_of.hpp>

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Proto domain hierarchy is itself. parent domain is computed from
  // proto_super_domain.
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct domain_ : domain_<typename T::proto_super_domain>
  {
    typedef domain_<typename T::proto_super_domain> parent;
    typedef T                                       type;
  };

  template<>
  struct  domain_<boost::proto::detail::not_a_domain>
        : unspecified_<boost::proto::detail::not_a_domain>
  {
    typedef unspecified_<boost::proto::detail::not_a_domain>  parent;
    typedef boost::proto::detail::not_a_domain                type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Proto expression hierarchy is defined by its domain and :
  //  - the top-most node for expression
  //  - the terminal value hierarchy (and its parent branches) for terminal
  //////////////////////////////////////////////////////////////////////////////
//  template<class T,class Domain>
//  struct expr_ : expr_<T,typename Domain::parent>
//  {
//    typedef expr_<T,typename Domain::parent> parent;
//    typedef tag::expr_      type(typename Domain::type);
//  };
//
//  template<class T,class Domain>
//  struct expr_<T,unspecified_<Domain> > : unspecified_<T>
//  {
//    typedef unspecified_<T> parent;
//    typedef tag::expr_      type(typename unspecified_<Domain>::type);
//  };
} }

namespace nt2 { namespace details
{
  template<class T> struct hierarchy_of<T, typename T::proto_is_domain_>
  {
    typedef meta::domain_<T> type;
  };

//  template<class T,class Node,class Domain>
//  struct expr_impl_
//  {
//    typedef expr_< T
//                 , node_type
//                 , typename meta::hierarchy_of<Domain>::type
//                 >                             type;
//  };
//  template<class T,class Node,class Domain>
//  struct expr_impl_<T,boost::proto::tag::terminal,Domain>
//  {
//    typedef typename boost::proto::result_of::value<T>::type value_type;
//    typedef expr_< T
//                 , typename meta::hierarchy_of<value_type>::type
//                 , typename meta::hierarchy_of<Domain>::type
//                 >                             type;
//  };
//  template<class T> struct hierarchy_of<T, typename T::proto_is_expr_>
//  {
//    typedef typename boost::proto::domain_of<T>::type domain_type;
//    typedef typename boost::proto::tag_of<T>::type    node_type;
//    typedef expr_impl_ < T
//                       , node_type
//                       , typename meta::hierarchy_of<domain_type>::type
//                       >                             type;
//  };
} }

#endif
