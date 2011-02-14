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
} }

#endif
