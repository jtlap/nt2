//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_ADAPTED_CONTAINER_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_ADAPTED_CONTAINER_HPP_INCLUDED

#include <nt2/sdk/meta/is_container.hpp>
#include <nt2/sdk/meta/container_of.hpp>
#include <nt2/sdk/meta/add_settings.hpp>
#include <nt2/sdk/meta/dimensions_of.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/dispatch/meta/terminal_of.hpp>

//==============================================================================
// Forward declaration
//==============================================================================
namespace nt2 { namespace memory
{
  template<class Tag, class ID, class T, class S> struct container;
} }

namespace nt2 { namespace meta
{
  //============================================================================
  // container dimensions are in its extent_type
  //============================================================================
  template<class Tag, class ID, class T, class S>
  struct  dimensions_of< memory::container<Tag,ID,T,S> >
        : boost::mpl::
          size_t<memory::container<Tag,ID,T,S>::sizes_type::static_size>
  {};

  //============================================================================
  // Register container as a proper container
  //============================================================================
  template<class Tag, class ID, class T, class S>
  struct is_container< memory::container<Tag, ID, T, S> > : boost::mpl::true_ {};

  template<class Tag, class ID, class T, class S, class S2>
  struct add_settings< memory::container<Tag, ID, T, S>, S2 >
  {
    typedef memory::container<Tag, ID, T, nt2::settings(S2,S) > type;
  };
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // value_of specialization
  //============================================================================
  template<class Tag, class ID, class T, class S>
  struct  value_of< nt2::memory::container<Tag,ID,T,S> >
        : value_of<T>
  {};

  //============================================================================
  // model_of specialization
  //============================================================================
  template<class Tag, class ID, class T, class S>
  struct model_of< nt2::memory::container<Tag,ID,T,S> >
  {
    struct type
    {
      template<class X> struct apply
      {
        typedef typename model_of<T>::type model;

        typedef nt2::memory::container< Tag,ID
                                      , typename boost::mpl::
                                        apply<model,X>::type
                                      , S
                                      >     type;
      };
    };
  };

  template<class Tag, class ID, class T, class S, class Origin>
  struct hierarchy_of< nt2::memory::container<Tag, ID, T, S>, Origin >
  {
    typedef typename Tag::template apply<T,S,Origin>::type type;
  };


  //============================================================================
  // container produce container expression from proper type and settings.
  //============================================================================
  template<class Tag, class ID, class T, class S>
  struct terminal_of< nt2::memory::container<Tag,ID,T,S> >
  {
    typedef nt2::container::
            expression< typename boost::proto::
                        terminal< nt2::memory::container<Tag,ID,T,S> >::type
                      , nt2::memory::container<Tag,ID,T, S>
                      >                                                 type;
  };
} } }

#endif
