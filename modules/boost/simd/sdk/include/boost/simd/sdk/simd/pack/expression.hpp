/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_SIMD_PACK_EXPRESSION_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_PACK_EXPRESSION_HPP_INCLUDED

#include <boost/dispatch/dsl/category.hpp>
#include <boost/dispatch/dsl/proto/extends.hpp>
#include <boost/simd/sdk/simd/meta/extension_of.hpp>

namespace boost { namespace simd
{
  ////////////////////////////////////////////////////////////////////////////
  // Here is the domain-specific expression wrapper
  ////////////////////////////////////////////////////////////////////////////
  template<class Expr,class Type,class Cardinal,class Dummy>
  struct  expression
  {
    BOOST_PROTO_BASIC_EXTENDS_TPL(Expr, (expression<Expr, Type, Cardinal>)
                                      , (domain<Type, Cardinal>))

    ////////////////////////////////////////////////////////////////////////////
    // expression hierarchy of simd:::expression
    ////////////////////////////////////////////////////////////////////////////
    typedef typename
    dispatch::details::hierarchy_of_expr<expression>::type dispatch_hierarchy_tag;

    ////////////////////////////////////////////////////////////////////////////
    // FusionRandomAccessSequence interface
    ////////////////////////////////////////////////////////////////////////////
    typedef pack<Type,Cardinal::value>              data_type;
    typedef typename data_type::value_type          value_type;
    typedef typename data_type::reference           reference;
    typedef typename data_type::const_reference     const_reference;
    typedef typename data_type::size_type           size_type;
    typedef typename data_type::iterator            iterator;
    typedef typename data_type::const_iterator      const_iterator;

    ////////////////////////////////////////////////////////////////////////////
    // Array interface
    ////////////////////////////////////////////////////////////////////////////
    BOOST_STATIC_CONSTANT(size_type, static_size = Cardinal::value);

    ////////////////////////////////////////////////////////////////////////////
    // Range interface
    ////////////////////////////////////////////////////////////////////////////
    const_iterator  begin()  const
    {
      data_type that;
      that.evaluate(*this);
      return that.begin();
    }

    const_iterator  end()    const
    {
      data_type that;
      that.evaluate(*this);
      return that.end();
    }

    ////////////////////////////////////////////////////////////////////////////
    // Extract element
    ////////////////////////////////////////////////////////////////////////////
    const_reference operator[](int i)     const
    {
      data_type that;
      that.evaluate(*this);
      return that[i];
    }
  };
} }

#endif
