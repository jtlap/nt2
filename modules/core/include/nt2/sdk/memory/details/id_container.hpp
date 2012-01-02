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
    typedef typename parent::block_t                      block_t;
    typedef typename parent::allocator_type               allocator_type;
    typedef typename parent::extent_type                  extent_type;
    typedef typename parent::size_type                    size_type;
    typedef typename parent::difference_type              difference_type;
    typedef typename parent::is_static_sized              is_static_sized;
    typedef typename parent::reference                    reference;
    typedef typename parent::const_reference              const_reference;

    //==========================================================================
    // Default constructor can be called endlessly to reuse data
    //==========================================================================
    container()
    {
      if(!status_)
      {
        parent::init(block_,sizes_, is_static_sized());
        status_ = true;
      }
    }

    //==========================================================================
    // First constructor call is given priority over the others
    // Default constructor never throw nor assert as multiple instance can
    // coexist
    //==========================================================================
    container( allocator_type const& a )
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
              , allocator_type const& a = allocator_type()
              )
    {
      if(!status_)
      {
        block_t that(sz,a);
        block_.swap(that);
        status_ = true;
      }
    }

    //==========================================================================
    // Element access from instance
    //==========================================================================
    template<class Position>
    BOOST_FORCEINLINE reference operator[]( Position const& pos )
    {
      return block_[pos];
    }

    template<class Position>
    BOOST_FORCEINLINE const_reference operator[]( Position const& pos ) const
    {
      return block_[pos];
    }

    //==========================================================================
    // Size of the container
    //==========================================================================
    static BOOST_FORCEINLINE extent_type const& sizes() { return sizes_; }

    static BOOST_FORCEINLINE size_type size()       { return block_.size();       }
    static BOOST_FORCEINLINE size_type inner_size() { return block_.inner_size(); }
    static BOOST_FORCEINLINE size_type outer_size() { return block_.outer_size(); }

    static BOOST_FORCEINLINE bool empty() { return block_.empty(); }

    static BOOST_FORCEINLINE difference_type lower()        { return block_.lower();        }
    static BOOST_FORCEINLINE difference_type inner_lower()  { return block_.inner_upper();  }
    static BOOST_FORCEINLINE difference_type outer_lower()  { return block_.outer_lower();  }

    static BOOST_FORCEINLINE difference_type upper()        { return block_.upper();        }
    static BOOST_FORCEINLINE difference_type inner_upper()  { return block_.inner_upper();  }
    static BOOST_FORCEINLINE difference_type outer_upper()  { return block_.outer_upper();  }

    //==========================================================================
    // Resize of the container
    //==========================================================================
    template<class Size> static BOOST_FORCEINLINE void resize( Size const& szs )
    {
      parent::resize( block_,sizes_,szs, is_static_sized() );
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
