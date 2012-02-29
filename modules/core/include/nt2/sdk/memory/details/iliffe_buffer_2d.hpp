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
#include <nt2/sdk/meta/view_at.hpp>

//==============================================================================
// nD specialisation for iliffe_buffer of "compact" automatic storage
//==============================================================================

namespace nt2 { namespace memory
{
  //============================================================================
  // iliffe_buffer is specialized in automatic storage nD case to behave as an
  // 1D array_buffer of contiguous data if Inner/Outer size is the same.
  //============================================================================
  template< typename T, std::ptrdiff_t S
          , std::ptrdiff_t BI , std::ptrdiff_t BO
          >
  struct  iliffe_buffer < array_buffer<T ,S,BI>
                        , array_buffer<T*,S,BO>
                        >
        : public array_buffer<T,S,BI>
  {
    typedef array_buffer<T,S,BI>              parent;
    typedef array_buffer<T*,S,BO>             index_parent;
    typedef typename parent::allocator_type   allocator_type;
    typedef typename parent::size_type        size_type;
    typedef typename parent::difference_type  difference_type;
    typedef typename parent::reference        reference;
    typedef typename parent::const_reference  const_reference;

    iliffe_buffer( allocator_type const& = allocator_type()) {}

    template<typename Sizes>
    iliffe_buffer (Sizes const&, allocator_type const& = allocator_type())
    {}

    template<typename Sizes> inline void resize( Sizes const& szs )
    {
      parent::resize(boost::fusion::at_c<0>(szs));
    }

    //==========================================================================
    // Element random access
    //==========================================================================
    BOOST_FORCEINLINE reference operator()( difference_type i )
    {
      return parent::operator()(i);
    }

    BOOST_FORCEINLINE const_reference operator()( difference_type i ) const
    {
      return parent::operator()(i);
    }

    BOOST_FORCEINLINE reference operator()(difference_type i, difference_type )
    {
      return parent::operator()(i);
    }

    BOOST_FORCEINLINE const_reference
    operator()(difference_type i, difference_type ) const
    {
      return parent::operator()(i);
    }

    inline size_type        inner_size()  const { return 1;       }
    inline size_type        outer_size()  const { return S;       }

    inline difference_type  inner_lower() const { return BI;      }
    inline difference_type  outer_lower() const { return BO;      }

    inline difference_type  inner_upper() const { return 1;       }
    inline difference_type  outer_upper() const { return BO+S-1;  }
  };
} }

#endif
