//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_DETAILS_ILIFFE_BUFFER_AUTO_2D_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_DETAILS_ILIFFE_BUFFER_AUTO_2D_HPP_INCLUDED

#include <nt2/sdk/memory/array_buffer.hpp>

//==============================================================================
// nD specialisation for iliffe_buffer of "compact" automatic storage
//==============================================================================

namespace nt2 { namespace memory
{
  //============================================================================
  // iliffe_buffer is specialized in automatic storage nD case to behave as an
  // 1D array_buffer of contiguous data if Inner/Outer size is the same.
  //============================================================================
  template< typename Dims, typename T, std::size_t S
          , std::ptrdiff_t BI , std::ptrdiff_t BO
          >
  struct  iliffe_buffer < Dims
                        , array_buffer<T,S,BI>
                        , array_buffer<T*,S,BO>
                        >
        : public array_buffer<T,S,BI>
  {
    typedef array_buffer<T,S,BI>                      parent;
    typedef typename parent::allocator_type           allocator_type;
    typedef typename parent::value_type               value_type;
    typedef typename parent::iterator                 iterator;
    typedef typename parent::const_iterator           const_iterator;
    typedef typename parent::reference                reference;
    typedef typename parent::const_reference          const_reference;
    typedef typename parent::size_type                size_type;
    typedef typename parent::difference_type          difference_type;

    iliffe_buffer( allocator_type const& a = allocator_type()) : parent(a) {}

    template<typename Sizes>
    iliffe_buffer (Sizes const& sz, allocator_type const& a = allocator_type())
                  : parent(sz,a)
    {}

    template<class Position>
    BOOST_FORCEINLINE reference operator[]( Position const& pos )
    {
      return parent::operator[] ( boost::fusion::at_c<0>(pos) );
    }
    
    template<class Position>
    BOOST_FORCEINLINE const_reference operator[]( Position const& pos ) const
    {
      return parent::operator[] ( boost::fusion::at_c<0>(pos) );
    }
  };
} }

#endif
