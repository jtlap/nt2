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

    //==========================================================================
    // Default constructor can be called endlessly to reuse data
    //==========================================================================
    container()
    {
      if(!status_)
      {
        parent::init(block_,sizes_, typename parent::is_static_sized());
        status_ = true;
      }
    }

    //==========================================================================
    // First constructor call is given priority over the others
    // Default constructor never throw nor assert as multiple instance can
    // coexist
    //==========================================================================
    container( typename parent::allocator_type const& a )
    {
      if(!status_)
      {
        typename parent::block_t that(a);
        block_.swap(that);
        status_ = true;
      }
    }

    template<class Size>
    container ( Size const& sz
              , typename parent::allocator_type const&
                a = typename parent::allocator_type()
              )
    {
      if(!status_)
      {
        typename parent::block_t that(sz,a);
        block_.swap(that);
        status_ = true;
      }
    }

    //==========================================================================
    // Element access
    //==========================================================================
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

    //==========================================================================
    // Size of the container
    //==========================================================================
    static typename parent::extent_type const&  sizes() { return sizes_;        }
    static typename parent::size_type           size()  { return block_.size(); }
    static bool                                 empty() { return block_.empty();}
    static typename parent::difference_type     lower() { return block_.lower();}
    static typename parent::difference_type     upper() { return block_.upper();}

    //==========================================================================
    // Resize of the container
    //==========================================================================
    template<class Size> static void resize( Size const& szs )
    {
      parent::resize( block_,sizes_,szs
                    , boost::mpl::bool_<parent::extent_type::static_status>()
                    );
    }

    private:
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
