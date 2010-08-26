/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_LINEAR_BLOCK_HPP_INCLUDED
#define NT2_SDK_MEMORY_LINEAR_BLOCK_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Linear allocation memory block
////////////////////////////////////////////////////////////////////////////////
#include <boost/typeof/typeof.hpp>
#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/stride.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <boost/fusion/include/at.hpp>

namespace nt2 { namespace memory
{
  template< int Dims
          , class Type
          , class Bases, class Sizes
          , class Padding
          , class Allocator
          >
  class linear_block
  {
    public:

    ////////////////////////////////////////////////////////////////////////////
    // Data related Type derived from Allocator
    ////////////////////////////////////////////////////////////////////////////
    typedef typename Allocator::template rebind<Type>::other  allocator_type;
    typedef typename allocator_type::value_type               value_type;
    typedef typename allocator_type::reference                reference;
    typedef typename allocator_type::const_reference          const_reference;
    typedef typename allocator_type::size_type                size_type;
    typedef typename allocator_type::difference_type          difference_type;

    ////////////////////////////////////////////////////////////////////////////
    // Type related to internal buffer
    // A linear_block holds a single [0,slice<1>(size)[ buffer
    ////////////////////////////////////////////////////////////////////////////
    typedef BOOST_TYPEOF_TPL(( slice<1>(Sizes(),Padding()) )) size_value_type;
    typedef boost::mpl::int_<0>                               base_value_type;
    typedef buffer< value_type      , base_value_type
                  , size_value_type , allocator_type  >       data_type;

    ////////////////////////////////////////////////////////////////////////////
    // Constructors
    ////////////////////////////////////////////////////////////////////////////
    linear_block() : data_(), bases_(), sizes_(), padding_() {}

    linear_block( Bases const& b, Sizes const& s, Padding const& p )
                : data_(base_value_type(),slice<1>(s,p))
                , bases_(b), sizes_(s), padding_(p)
    {}

    linear_block( linear_block const& src )
                : data_(src.data_)
                , bases_(src.bases_), sizes_(src.sizes_)
                , padding_(src.padding_)
    {}

    ////////////////////////////////////////////////////////////////////////////
    // Assignment
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    // Swap
    ////////////////////////////////////////////////////////////////////////////
    void swap( linear_block& src )
    {
      boost::swap(data_   , src.data_   );
      boost::swap(bases_  , src.bases_  );
      boost::swap(sizes_  , src.sizes_  );
      boost::swap(padding_, src.padding_);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Element access
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    // Size manipulation
    ////////////////////////////////////////////////////////////////////////////
    void rebase( Bases const& b ) { data_.rebase(b); }
    void resize( Sizes const& s ) { data_.resize(s); }
    void restructure( Bases const& b, Sizes const& s )
    {
      data_.restructure(b,s);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Size informations
    ////////////////////////////////////////////////////////////////////////////
    template<std::size_t N>
    typename boost::enable_if_c< (N>=1) && (N<=Dims), size_type>::type
    size() const
    {
      return boost::fusion::at_c<N-1>(sizes_);
    }

    template<std::size_t N>
    typename boost::disable_if_c< (N>=1) && (N<=Dims), size_type>::type
    size() const
    {
      return 1;
    }

    template<std::size_t N>
    typename boost::enable_if_c< (N>=1) && (N<=Dims), difference_type>::type
    lower() const
    {
      return boost::fusion::at_c<N-1>(bases_);
    }

    template<std::size_t N>
    typename boost::disable_if_c< (N>=1) && (N<=Dims), difference_type>::type
    lower() const
    {
      return 1;
    }

    template<std::size_t N> difference_type upper() const
    {
      return size<N>() + lower<N>() - 1;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Data members : sizes,bases, buffer and padder
    ////////////////////////////////////////////////////////////////////////////
    //private:
    data_type   data_;
    Bases       bases_;
    Sizes       sizes_;
    Padding     padding_;

  };
} }

#endif
