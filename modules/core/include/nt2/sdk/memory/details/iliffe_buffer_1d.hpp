//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_DETAILS_ILIFFE_BUFFER_1D_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_DETAILS_ILIFFE_BUFFER_1D_HPP_INCLUDED

//==============================================================================
// 
//==============================================================================

namespace nt2 { namespace memory
{
  //============================================================================
  // iliffe_buffer is specialized for 1D buffers to just forward to Data.
  //============================================================================
  template<typename Data, typename Index>
  struct iliffe_buffer<boost::mpl::size_t<1>,Data,Index> : public Data
  {    
    typedef Data                              parent;
    typedef typename parent::allocator_type   allocator_type;
    typedef typename parent::value_type       value_type;
    typedef typename parent::iterator         iterator;
    typedef typename parent::const_iterator   const_iterator;
    typedef typename parent::reference        reference;
    typedef typename parent::const_reference  const_reference;
    typedef typename parent::size_type        size_type;
    typedef typename parent::difference_type  difference_type;

    iliffe_buffer( allocator_type const& a = allocator_type()) : parent(a) {}

    template<typename Sizes>
    iliffe_buffer ( Sizes const& sz, allocator_type const& a = allocator_type() )
                  : parent(sz,a)
    {}
  };
} }

#endif
