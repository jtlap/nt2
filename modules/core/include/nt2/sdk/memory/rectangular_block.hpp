//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_RECTANGULAR_BLOCK_HPP_INCLUDED
#define NT2_SDK_MEMORY_RECTANGULAR_BLOCK_HPP_INCLUDED

//==============================================================================
// Implements the rectangular_ block specialisation
//==============================================================================

#include <nt2/sdk/memory/block_facade.hpp>

namespace nt2 { namespace memory
{
  template<class T, class S>
  struct block<rectangular_,T,S> : public block_facade<T,S>
  {    
    typedef block_facade<T,S> parent;
    
    block ( typename parent::allocator_type const&
            a = typename parent::allocator_type()
          )
          : parent(a)
    {}

    template<class Size>
    block ( Size const& sz
          , typename parent::allocator_type const&
            a = typename parent::allocator_type()
          )
          : parent(sz,a)
    {}

    block( block const& s ) : parent( static_cast<parent const&>(s) ) {}

    void swap( block& src ) { parent::data().swap( src.data() ); }
  };
} }

#endif
