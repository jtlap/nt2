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

#include <nt2/sdk/dsl/semantic_of.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>

namespace nt2 { namespace tag
{
  //////////////////////////////////////////////////////////////////////////////
  // Expression category tag
  //////////////////////////////////////////////////////////////////////////////
  template<class Domain, class Tag, class Semantic> struct expr_ {};

  //////////////////////////////////////////////////////////////////////////////
  // Degenerate Expression category tag
  //////////////////////////////////////////////////////////////////////////////
  struct ast_ {};
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

  template<class T>
  struct  domain_< unknown_<T> > : unknown_<T>
  {
    typedef unknown_<T>                 parent;
    typedef typename unknown_<T>::type  type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Proto expression hierarchy depends of the EDSL nature. They however has
  // the same inheritance scheme based on domain
  //////////////////////////////////////////////////////////////////////////////
  template<class T, class Domain, class Tag, class Semantic>
  struct  expr_
        : expr_<T, typename Domain::parent, Tag, Semantic>
  {
    typedef expr_<T, typename Domain::parent, Tag, Semantic>   parent;
    typedef tag::expr_< typename Domain::type, Tag, Semantic> type;
  };

  template<class T, class Domain, class Tag, class Semantic>
  struct  expr_< T, unspecified_<Domain>, Tag, Semantic > : unspecified_<T>
  {
    typedef unspecified_<T>   parent;
    typedef tag::expr_< typename unspecified_<Domain>::type, Tag, Semantic> type;
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
} }

#endif
