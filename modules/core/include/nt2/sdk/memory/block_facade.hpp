//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_BLOCK_FACADE_HPP_INCLUDED
#define NT2_SDK_MEMORY_BLOCK_FACADE_HPP_INCLUDED

//==============================================================================
/**
  * \file
  * \brief Defines and implements the \c nt2::memory::block_facade class
  **/
//==============================================================================

#include <nt2/core/settings/option.hpp>
#include <nt2/core/settings/storage_scheme.hpp>

namespace nt2 { namespace memory
{
  //============================================================================
  /**!
   *
   **/
  //============================================================================
  template<class Shape, class Type, class Settings> class block;

  //============================================================================
  /**!
   *
   **/
  //============================================================================
  template<class T, class S> class block_facade
  {
    public:
    //==========================================================================
    // Builds the buffer from the Settings
    //==========================================================================
    typedef typename meta::option<S, tag::storage_scheme_>::type  scheme_t;
    typedef typename scheme_t::template apply<T,S>::type          buffer_t;

    //==========================================================================
    // Public type interface
    //==========================================================================
    typedef typename buffer_t::allocator_type   allocator_type;
    typedef typename buffer_t::value_type       value_type;
    typedef typename buffer_t::iterator         iterator;
    typedef typename buffer_t::const_iterator   const_iterator;
    typedef typename buffer_t::reference        reference;
    typedef typename buffer_t::const_reference  const_reference;
    typedef typename buffer_t::size_type        size_type;
    typedef typename buffer_t::difference_type  difference_type;

    //==========================================================================
    // Default Constructor
    //==========================================================================
    block_facade( allocator_type const& a = allocator_type() ) : data_(a) {}

    //==========================================================================
    // Size based Constructor
    // This is the base case, any special handling can be overloaded in the
    // shape specific block specialisation. More specifically, all padding or
    // shape related adaptation on Size/Base is handled by the specialisation.
    //==========================================================================
    template<class Size>
    block_facade( Size const& sz, allocator_type const& a = allocator_type() )
                : data_(sz,a)
    {}

    //==========================================================================
    /**
     * Access to a given position in the underlying buffer
     * \param pos nD Index of the element to retrieve passed either as an
     * integral value or as a Fusion RandomAccessSequence of size 1 or 2.
     **/
    //==========================================================================
    template<class Position>
    BOOST_FORCEINLINE reference operator[]( Position const& pos )
    {
      return data_[pos];
    }

    template<class Position>
    BOOST_FORCEINLINE const_reference operator[]( Position const& pos ) const
    {
      return data_[pos];
    }

    //==========================================================================
    // Shape management
    // These are the base case, any special handling can be overloaded in the
    // shape specific block specialisation. More specifically, all padding or
    // shape related adaptation on Size is handled by the specialisation.
    //==========================================================================
    template<class Size> void resize( Size const& szs ) { data_.resize(szs); }

    //==========================================================================
    // Size related informations
    //==========================================================================
    BOOST_FORCEINLINE size_type size()        const { return data_.size();       }
    BOOST_FORCEINLINE size_type inner_size()  const { return data_.inner_size(); }
    BOOST_FORCEINLINE size_type outer_size()  const { return data_.outer_size(); }

    BOOST_FORCEINLINE bool empty() const { return data_.empty(); }

    BOOST_FORCEINLINE difference_type lower()       const { return data_.lower();        }
    BOOST_FORCEINLINE difference_type inner_lower() const { return data_.inner_upper();  }
    BOOST_FORCEINLINE difference_type outer_lower() const { return data_.outer_lower();  }

    BOOST_FORCEINLINE difference_type upper()       const { return data_.upper();        }
    BOOST_FORCEINLINE difference_type inner_upper() const { return data_.inner_upper();  }
    BOOST_FORCEINLINE difference_type outer_upper() const { return data_.outer_upper();  }

    //==========================================================================
    // Access to data
    //==========================================================================
    buffer_t&       data()        { return data_; }
    buffer_t const& data() const  { return data_; }

    private:
    buffer_t    data_;
  };
} }

#endif
