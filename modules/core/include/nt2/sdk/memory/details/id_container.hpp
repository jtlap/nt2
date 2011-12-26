//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_DETAILS_ID_CONTAINER_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_ID_CONTAINER_HPP_INCLUDED
#include <nt2/sdk/memory/details/container_base.hpp>

namespace nt2 { namespace memory
{
  //============================================================================
  // When given a non-null ID, containers share their block as a static member.
  // Every related methods and values are therefore static.
  //============================================================================
  template<class Tag, class ID, class T, class S>
  struct container : nt2::details::container_base<Tag,T,S>
  {
    typedef nt2::details::container_base<Tag,T,S>         parent;

    container ( typename parent::allocator_type const&
                a = typename parent::allocator_type()
              )
    {
      //========================================================================
      // First constructor call is given priority over the others
      // TODO: Check if additional construction attempt should assert or throw.
      //========================================================================
      if(!status_)
      {
        typename parent::block_t that(a);
        block_.swap(that);
      }
    }

    template<class Size>
    container ( Size const& sz
              , typename parent::allocator_type const&
                a = typename parent::allocator_type()
              )
    {
      //========================================================================
      // First constructor call is given priority over the others
      // TODO: Check if additional construction attempt should assert or throw.
      //========================================================================
      if(!status_)
      {
        typename parent::block_t that(sz,a);
        block_.swap(that);
      }
    }
    
    template<class Position> BOOST_FORCEINLINE
    typename parent::reference operator[]( Position const& pos )
    {
      return block_[pos];
    }
    
    template<class Position> BOOST_FORCEINLINE
    typename parent::const_reference operator[]( Position const& pos ) const
    {
      return block_[pos];
    }

    static typename parent::extent_type const& sizes() { return sizes_; }

    template<class Size> static void resize( Size const& szs )
    {
      sizes_ = typename parent::extent_type(szs);
      block_.resize(szs); 
    }
      
    //private:
    static bool                         status_;
    static typename parent::block_t     block_;
    static typename parent::extent_type sizes_;
  };

  //========================================================================
  // By default, block is non initialized
  //========================================================================
  template<class Tag, class ID, class T, class S>
  typename nt2::details::container_base<Tag,T,S>::block_t
  container<Tag, ID, T, S>::block_;

  //========================================================================
  // Set status to not constructed first
  //========================================================================
  template<class Tag, class ID, class T, class S>
  bool container<Tag, ID, T, S>::status_ = false;

  //========================================================================
  // Set size to default value
  //========================================================================
  template<class Tag, class ID, class T, class S>
  typename nt2::details::container_base<Tag,T,S>::extent_type
  container<Tag, ID, T, S>::sizes_;
} }

#endif
