/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_CONTAINER_DETAILS_BLOCK_DATA_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DETAILS_BLOCK_DATA_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Internal data related components for blocks
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/memory/buffer.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/next_prior.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/include/as_vector.hpp>
#include <nt2/core/container/meta/composite.hpp>

////////////////////////////////////////////////////////////////////////////////
// heap_ and stack_ are short-cut and binder for additional info on allocator
////////////////////////////////////////////////////////////////////////////////
namespace nt2
{
  struct heap_;
  struct stack_;
}

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Compute the recursive tuple of buffer used to store data in a nD block
  //////////////////////////////////////////////////////////////////////////////
  template< class Type
          , class StorageKind
          , class Extend
          , bool  Enable = meta::is_composite<Type>::value
          >
  struct block_data_impl;

  //////////////////////////////////////////////////////////////////////////////
  // Compute the recursive tuple of buffer used to store data in a nD block
  //////////////////////////////////////////////////////////////////////////////
  template< class Type
          , class Allocator
          , class Extend
          , bool  Enable
          >
  struct block_data_impl<Type, heap_(Allocator), Extend, Enable>
  {
    typedef block_data_impl < Type
                            , heap_(Allocator)
                            , typename boost::mpl::prior<Extend>::type
                            , Enable
                            >                             prior_block;

    typedef typename boost::add_pointer<typename prior_block::base>::type base;
    typedef memory::buffer<base,Allocator>                         buffer_type;
    typedef typename prior_block::type                              prior_type;
    typedef typename boost::mpl::push_back<prior_type,buffer_type>::type  type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Special case : 1d block of non-composite types
  //////////////////////////////////////////////////////////////////////////////
  template<class Type,class Allocator>
  struct block_data_impl<Type, heap_(Allocator), boost::mpl::int_<1>,false>
  {
    typedef Type                                                    base;
    typedef boost::fusion::vector< memory::buffer<base,Allocator> > type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Special case : 2d block of composite types is a buffer of buffers pointer
  //////////////////////////////////////////////////////////////////////////////
  template<class Type,class Allocator>
  struct block_data_impl<Type, heap_(Allocator), boost::mpl::int_<2>,true>
  {
    typedef block_data_impl < Type
                            , heap_(Allocator)
                            , boost::mpl::int_<1>
                            , true
                            >                             prior_block;

    typedef typename boost::mpl::
            transform < typename boost::fusion::result_of::as_vector<Type>::type
                      , boost::add_pointer<boost::mpl::_>
                      >::type                                             base;
    typedef memory::buffer<base,Allocator>                         buffer_type;
    typedef typename prior_block::type                              prior_type;
    typedef typename boost::mpl::push_back<prior_type,buffer_type>::type  type;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Special case : 1d block of composite types is a fusion vector of buffers
  //////////////////////////////////////////////////////////////////////////////
  template<class Type,class Allocator>
  struct block_data_impl<Type, heap_(Allocator), boost::mpl::int_<1>,true>
  {
    typedef typename boost::mpl::transform< typename boost::fusion::result_of::
                                            as_vector<Type>::type
                                          , memory::buffer< boost::mpl::_
                                                          , Allocator
                                                          >
                                          >::type base;
    typedef boost::fusion::vector< base >         type;
  };
} }

#endif
