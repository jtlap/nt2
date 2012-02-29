//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_ADAPTED_ILIFFE_BUFFER_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_ADAPTED_ILIFFE_BUFFER_HPP_INCLUDED

#include <boost/type_traits/is_void.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>

//==============================================================================
// Forward declaration
//==============================================================================
namespace nt2 { namespace memory
{
  template<typename Data, typename Index> struct iliffe_buffer;
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // value_of specialization
  //============================================================================
  template<typename D, typename I>
  struct  value_of< nt2::memory::iliffe_buffer<D,I> >
        : value_of<D>
  {};

  //============================================================================
  // model_of specialization
  //============================================================================
  template<typename D, typename I>
  struct model_of< nt2::memory::iliffe_buffer<D,I> >
  {
    struct type
    {
      template<class X> struct apply
      {
        typedef typename model_of<D>::type model_data;
        typedef typename model_of<I>::type model_index;

        typedef typename  boost::mpl::
                          if_ < boost::is_void<I>
                              , void
                              , typename  boost::mpl::
                                          apply<model_index,X>::type
                              >::type                               index_t;


        typedef nt2::memory::iliffe_buffer
                < typename boost::mpl::apply<model_data ,X>::type
                , index_t
                >                                                   type;
      };
    };
  };
} } }

#endif
