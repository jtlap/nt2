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

#include <nt2/core/settings/size.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/core/container/category.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <nt2/core/container/meta/make_block.hpp>
#include <nt2/core/container/meta/is_container.hpp>

namespace nt2 { namespace container
{
  //============================================================================
  /*!
   * table_container is the base class handling a table semantic, layout and
   * memory used by the table proto terminal class. It is built from a value
   * \c Type and a list of \c Settings describing how it should behave both at
   * runtime and compile-time.
   *
   * \tparam Type Value type to store in the table
   * \tparam Setting Compound options list describing the behavior of the table
   **/
  //============================================================================
  template<class Type, class Settings> struct table_container
  {
    typedef typename make_block<Type, Settings>::type block_type;
    block_type block;

    typedef typename meta::option<Settings, tag::of_size_, _4D>::type size_type;
    size_type size_;

    typedef nt2::settings settings_type(size_type);

    size_type const& extent() const { return size_; }
  };
}

namespace meta
{
  //============================================================================
  // Register table_container as a proper container
  //============================================================================
  template<class T, class S>
  struct is_container< container::table_container<T, S> > : boost::mpl::true_
  {};
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // Register table_container as a proper Hierarchizable
  //============================================================================
  template<class T, class S>
  struct value_of< nt2::container::table_container<T, S> >
  {
    typedef T type;
  };

  template<class T, class S, class Origin>
  struct hierarchy_of< nt2::container::table_container<T, S>, Origin >
  {
    typedef table_< typename property_of< typename value_of<T>::type
                                        , Origin
                                        >::type
                  , S
                  >                                   type;
  };

  //============================================================================
  // table_container produce container expression from proper type and settings
  //============================================================================
  template<class T, class S>
  struct terminal_of< nt2::container::table_container<T, S> >
  {
    // Retrieve normalized settings
    typedef typename nt2::container::
            table_container<T, S>::settings_type                  settings_type;

    typedef nt2::container::table_container<T, settings_type>         container;

    typedef nt2::container::
            expression< typename boost::proto::terminal< container >::type
                      , container&
                      >                                                    type;
  };

  //============================================================================
  // table use table_container to do its biddings
  //============================================================================
  template<class T, class S> struct semantic_of< nt2::container::table<T, S> >
  {
    typedef nt2::container::table_container<T, S>& type;
  };
} } }

#endif
