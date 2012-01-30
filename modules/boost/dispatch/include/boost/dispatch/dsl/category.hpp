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
#include <boost/proto/domain.hpp>
#include <boost/proto/traits.hpp>

namespace boost { namespace dispatch { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Proto expression hierarchy depends of the EDSL nature. They however has
  // the same inheritance scheme based on semantic
  //////////////////////////////////////////////////////////////////////////////
  template<class T>
  struct ast_ : ast_<typename T::parent>
  {
    typedef ast_<typename T::parent> parent;
  };
  
  template<class T>
  struct ast_< unspecified_<T> > : unspecified_<T>
  {
    typedef unspecified_<T> parent;
  };
  
  template<class T, class Domain, class Tag>
  struct  expr_
        : expr_<typename T::parent, Domain, Tag>
  {
    typedef expr_<typename T::parent, Domain, Tag>  parent;
  };

  template<class T, class Domain, class Tag>
  struct  expr_< unspecified_<T>, Domain, Tag > 
    : ast_<typename hierarchy_of<typename semantic_of<T>::type, T>::type>
  {
    typedef ast_<typename hierarchy_of<typename semantic_of<T>::type, T>::type> parent;
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
                     , typename boost::
                       enable_if< proto::is_expr<T> >::type
                     >
  {
    typedef typename meta::semantic_of<T>::type  semantic_type;
    typedef typename proto::domain_of<T>::type   domain_type;
    typedef typename proto::tag_of<T>::type      tag_type;
    
    typedef meta::expr_ < typename meta::
                          hierarchy_of< semantic_type
                                      , Origin
                                      >::type
                        , domain_type
                        , typename meta::hierarchy_of<tag_type>::type
                        >                        type;
  };
  
  template<class T>
  struct value_of< T
                 , typename boost::
                   enable_if< proto::is_expr<T> >::type
                 >
    : meta::semantic_of<T>
  {
  };
  
} } }

#endif
