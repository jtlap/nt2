/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_FUNCTOR_DETAILS_ENABLE_DISPATCH_HPP_INCLUDED
#define NT2_SDK_FUNCTOR_DETAILS_ENABLE_DISPATCH_HPP_INCLUDED

namespace nt2 { namespace meta
{
  template< class Tag,class Category, class Hierarchy, class Info
          , class Enable = void
          >
  struct  enable_dispatch : boost::mpl::false_
  {};

  template<class Tag,class Category, class Hierarchy, class Info>
  struct  enable_dispatch < Tag,Category,Hierarchy,Info
                          , typename functors ::call<Tag,Category,Hierarchy,Info>
                                              ::callable_type
                          >
        : boost::mpl::true_ {};
} }

#endif
