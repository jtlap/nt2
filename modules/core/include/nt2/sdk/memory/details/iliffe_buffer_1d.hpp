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

namespace nt2 { namespace memory
{
  //============================================================================
  // iliffe_buffer is specialized for 1D buffers to just forward to Data.
  //============================================================================
  template<typename Data> struct iliffe_buffer<Data,void> : public Data
  {
    typedef Data                              parent;
    typedef typename parent::size_type        size_type;
    typedef typename parent::difference_type  difference_type;
    typedef typename parent::reference        reference;
    typedef typename parent::const_reference  const_reference;
    typedef typename parent::allocator_type   allocator_type;

    iliffe_buffer( allocator_type const& a = allocator_type()) : parent(a) {}

    template<typename Sizes>
    iliffe_buffer ( Sizes const& sz, allocator_type const& a = allocator_type() )
                  : parent(boost::fusion::at_c<0>(sz),a)
    {}

    iliffe_buffer ( iliffe_buffer const& s)
                  : parent(static_cast<parent const&>(s))
    {}

    inline size_type        inner_size()  const { return parent::size();  }
    inline size_type        outer_size()  const { return 1;               }

    inline difference_type  inner_lower() const { return parent::lower(); }
    inline difference_type  outer_lower() const { return 1;               }

    inline difference_type  inner_upper() const { return parent::upper(); }
    inline difference_type  outer_upper() const { return 1;               }
  };
} }

#endif
