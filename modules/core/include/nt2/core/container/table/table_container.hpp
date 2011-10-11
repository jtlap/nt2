//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_TABLE_TABLE_CONTAINER_HPP_INCLUDED
#define NT2_CORE_CONTAINER_TABLE_TABLE_CONTAINER_HPP_INCLUDED

#include <nt2/core/container/meta/make_block.hpp>
#include <nt2/core/container/meta/is_container.hpp>
#include <nt2/core/container/category.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>

namespace nt2 { namespace container
{

template<class T, class S>
struct table_container
{
  typedef typename make_block<T, S>::type block_type;
  block_type block;
};

template<class T, class S>
struct is_container< table_container<T, S> >
  : boost::mpl::true_
{
};

} }

namespace boost { namespace dispatch { namespace meta
{
  template<class T, class S>
  struct value_of< nt2::container::table_container<T, S> >
  {
    typedef T type;
  };
  
  template<class T, class S, class Origin>
  struct hierarchy_of< nt2::container::table_container<T, S>, Origin >
  {
    typedef table_< typename property_of<typename value_of<T>::type, Origin>::type, S > type;
  };
    
} } }

#endif
