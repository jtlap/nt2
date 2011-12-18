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

#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <nt2/core/container/meta/dimensions_of.hpp>

//==============================================================================
// Forward declaration
//==============================================================================
namespace nt2 { namespace memory
{
  template<typename Dimensions, typename Data, typename Index>
  struct iliffe_buffer;
} }

namespace nt2 { namespace meta
{
  //============================================================================
  // iliffe_buffer dimensions are in Ds
  //============================================================================
  template<typename Ds, typename D, typename I>
  struct dimensions_of< memory::iliffe_buffer<Ds,D,I> > : Ds
  {};
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // value_of specialization
  //============================================================================
  template<typename Ds, typename D, typename I>
  struct  value_of< nt2::memory::iliffe_buffer<Ds,D,I> >
        : value_of<D>
  {};

  //============================================================================
  // model_of specialization
  //============================================================================
  template<typename Ds, typename D, typename I>
  struct model_of< nt2::memory::iliffe_buffer<Ds,D,I> >
  {
    struct type
    {
      template<class X> struct apply
      {
        typedef typename model_of<D>::type model_data;
        typedef typename model_of<I>::type model_index;
        
        typedef nt2::memory::iliffe_buffer
                < Ds
                , typename boost::mpl::apply<model_data ,X>::type
                , typename boost::mpl::apply<model_index,X>::type
                >                                                   type;
      };
    };
  };
} } }

#endif
