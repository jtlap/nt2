/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_DISPATCH_DSL_CATEGORY_HPP_INCLUDED
#define BOOST_DISPATCH_DSL_CATEGORY_HPP_INCLUDED

#include <boost/dispatch/dsl/semantic_of.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/proto/domain.hpp>

namespace boost { namespace dispatch { namespace tag
{
  //////////////////////////////////////////////////////////////////////////////
  // Degenerate Expression category tag
  //////////////////////////////////////////////////////////////////////////////
  struct ast_ {};
} } }

namespace boost { namespace dispatch { namespace meta
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
  };

  template<class T>
  struct  domain_< unknown_<T> > : unknown_<T>
  {
    typedef unknown_<T> parent;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Proto expression hierarchy depends of the EDSL nature. They however has
  // the same inheritance scheme based on domain
  //////////////////////////////////////////////////////////////////////////////
  template<class T> struct ast_ : unspecified_<T>
  {
    typedef unspecified_<T> parent;
  };
  
  template<class T, class Domain, class Tag, class Semantic>
  struct  expr_
        : expr_<T, typename Domain::parent, Tag, Semantic>
  {
    typedef expr_<T, typename Domain::parent, Tag, Semantic>  parent;
  };

  template<class T, class Domain, class Tag, class Semantic>
  struct  expr_< T, unspecified_<Domain>, Tag, Semantic > : ast_<T>
  {
    typedef unspecified_<T> parent;
  };
} } }

namespace boost { namespace dispatch { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Proto domain hierarchy specialization
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class Origin>
  struct hierarchy_of<T, Origin,typename T::proto_is_domain_>
  {
    typedef meta::domain_<T> type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Proto expression hierarchy computation
  //////////////////////////////////////////////////////////////////////////////
  template<class T> struct hierarchy_of_expr
  {
    typedef typename boost::proto::domain_of<T>::type domain_type;
    typedef typename boost::proto::tag_of<T>::type    tag_type;
    typedef meta::expr_ < T
                        , typename meta::hierarchy_of<domain_type>::type
                        , tag_type
                        , typename meta::semantic_of<T>::type
                        > type;
  };
} } }

#endif
