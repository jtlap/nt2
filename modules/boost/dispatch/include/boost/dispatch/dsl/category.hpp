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
#include <boost/dispatch/meta/value_of.hpp>

namespace boost { namespace dispatch { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Proto expression hierarchy depends of the EDSL nature. They however has
  // the same inheritance scheme based on semantic
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct ast_ : unspecified_<T>
  {
    typedef unspecified_<T> parent;
  };

  template<class T, class Tag, class N>
  struct node_ : node_<T, typename Tag::parent, N>
  {
    typedef node_<T, typename Tag::parent, N> parent;
  };

  template<class T, class Tag, class N>
  struct node_<T, unspecified_<Tag>, N> : ast_<T>
  {
    typedef ast_<T> parent;
  };

  template<class T, class Tag, class N>
  struct expr_ : expr_<typename T::parent, Tag, N>
  {
    typedef expr_<typename T::parent, Tag, N>  parent;
  };

  template<class T, class Tag, class N>
  struct expr_< unspecified_<T>, Tag, N> : node_<T, Tag, N>
  {
    typedef node_<T, Tag, N> parent;
  };
} } }

namespace boost { namespace dispatch { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Proto expression hierarchy computation
  //////////////////////////////////////////////////////////////////////////////
  template<class T, class Origin>
  struct hierarchy_of< T
                     , Origin
                     , typename T::proto_is_expr_
                     >
  {
    typedef typename meta::semantic_of<T>::type  semantic_type;
    
    typedef meta::expr_ < typename meta::hierarchy_of<semantic_type, Origin>::type
                        , typename meta::hierarchy_of<typename T::proto_tag>::type
                        , typename T::proto_arity
                        >                                          type;
  };

  template<class T>
  struct value_of< T
                 , typename T::proto_is_expr_
                 >
    : meta::semantic_of<T>
  {
  };

} } }

#endif
