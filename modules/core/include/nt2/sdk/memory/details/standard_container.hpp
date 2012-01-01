//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_DETAILS_STANDARD_CONTAINER_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_STANDARD_CONTAINER_HPP_INCLUDED

#include <nt2/core/settings/id.hpp>
#include <nt2/sdk/memory/details/container_base.hpp>

namespace nt2 { namespace memory
{
  //============================================================================
  /*!
   * container is the base class handling a container semantic, layout and
   * memory used by the table proto terminal class. It is built from a value
   * \c Type and a list of \c Settings describing how it should behave both at
   * runtime and compile-time.
   *
   * \tparam Type Value type to store in the table
   * \tparam Setting Compound options list describing the behavior of the table
   **/
  //============================================================================
  template<class Tag, class T, class S>
  struct container<Tag, id_<0>, T, S> : nt2::details::container_base<Tag,T,S>
  {
    typedef nt2::details::container_base<Tag,T,S>         parent;

    container ( typename parent::allocator_type const&
                a = typename parent::allocator_type()
              )
              : block_(a)
    {
      parent::init(block_,sizes_, typename parent::is_static_sized());
    }

    template<class Size>
    container ( Size const& sz
              , typename parent::allocator_type const&
                a = typename parent::allocator_type()
              )
              : block_(sz,a), sizes_(sz)
    {}

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

    template<class Size> void resize( Size const& szs )
    {
      parent::resize( block_,sizes_,szs
                    , typename parent::is_static_sized()
                    );
    }
    typename parent::extent_type const&  sizes() const { return sizes_;  }

    private:
    typename parent::block_t      block_;
    typename parent::extent_type  sizes_;
  };
} }

#endif
