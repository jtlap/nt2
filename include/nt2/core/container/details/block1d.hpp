/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_CONTAINER_DETAILS_BLOCK1D_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DETAILS_BLOCK1D_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Defines a 1D block of memory to be used by 1D container
// This is a specialisation of block<T,N,S> as 1D block are quite frequent and
// can be optimized out of all Fusion meta-programming layer
////////////////////////////////////////////////////////////////////////////////

#include <boost/mpl/size.hpp>
#include <boost/utility/enable_if.hpp>
#include <nt2/core/settings/allocator.hpp>
#include <nt2/core/settings/meta/options.hpp>

namespace nt2 { namespace container
{
  //////////////////////////////////////////////////////////////////////////////
  // 1D block is basically a buffer with specialized behavior
  //////////////////////////////////////////////////////////////////////////////
  template<class T,class S> struct  block<T,boost::mpl::int_<1>,S>
  {
    ////////////////////////////////////////////////////////////////////////////
    // block hierarchy
    ////////////////////////////////////////////////////////////////////////////
    //typedef xxx nt2_hierarchy_tag;

    ////////////////////////////////////////////////////////////////////////////
    // Data type
    // TODO: Make a fusion::vector of buffer if T is composite
    ////////////////////////////////////////////////////////////////////////////
    typedef typename meta::
    option< S
          , options::allocator_
          , nt2::memory::allocator<boost::mpl::_>
          >::type                                           allocator_type;

    typedef memory::buffer< T
                          , typename boost::mpl::
                            apply<allocator_type,T>::type
                          >                                 data_type;

    ////////////////////////////////////////////////////////////////////////////
    // Sequence interface
    ////////////////////////////////////////////////////////////////////////////
    typedef typename data_type::value_type       value_type;
    typedef typename data_type::pointer          pointer;
    typedef typename data_type::const_pointer    const_pointer;
    typedef typename data_type::reference        reference;
    typedef typename data_type::const_reference  const_reference;
    typedef typename data_type::size_type        size_type;
    typedef typename data_type::difference_type  difference_type;
    typedef typename data_type::difference_type  index_type;

    ////////////////////////////////////////////////////////////////////////////
    // Size related methods
    // size,lower and upper require a dimension, return 1 if out of bound
    // size has a std conformant version that return total number of elements
    ////////////////////////////////////////////////////////////////////////////
    size_t    size() const { return mData.size();  }

    template<std::size_t I>
    size_t    size() const { return (I==1) ? mData.size()   : 1;  }

    template<std::size_t I>
    ptrdiff_t lower() const { return (I==1) ? mData.lower()  : 1;  }

    template<std::size_t I>
    ptrdiff_t upper() const { return (I==1) ? mData.upper()  : 1;  }

    ////////////////////////////////////////////////////////////////////////////
    // Range interface
    // TODO: Make iterator be some linear_indexed_(const_)iterator
    ////////////////////////////////////////////////////////////////////////////
    typedef pointer       iterator;
    typedef const_pointer const_iterator;

    iterator        begin()       { return mData.begin(); }
    const_iterator  begin() const { return mData.begin(); }
    iterator        end()         { return mData.end();   }
    const_iterator  end()   const { return mData.end();   }

    ////////////////////////////////////////////////////////////////////////////
    // Default constructor
    ////////////////////////////////////////////////////////////////////////////
    block() : mData() {}

    ////////////////////////////////////////////////////////////////////////////
    // Copy constructor
    ////////////////////////////////////////////////////////////////////////////
    block( block const& src ) : data_type(src.mData) {}

    ////////////////////////////////////////////////////////////////////////////
    // Constructor taking a Base and a Size fusion random access sequence
    ////////////////////////////////////////////////////////////////////////////
    template<class Bases,class Sizes>
    block ( Bases const& b
          , Sizes const& s
          , typename
            boost::enable_if_c<   (boost::mpl::size<Bases>::value == 1)
                              &&  (boost::mpl::size<Sizes>::value == 1)
                              >::type* =0
          )
          : mData ( boost::fusion::at_c<0>(b)
                  , boost::fusion::at_c<0>(s)
                  )
    {}

    ////////////////////////////////////////////////////////////////////////////
    // Destructor
    ////////////////////////////////////////////////////////////////////////////
    ~block() {}

    ////////////////////////////////////////////////////////////////////////////
    // Assignment
    ////////////////////////////////////////////////////////////////////////////
    block& operator=(block const& src) { mData = src.mData; return *this; }

    ////////////////////////////////////////////////////////////////////////////
    // Initialization taking a Base and a Size fusion random access sequence
    ////////////////////////////////////////////////////////////////////////////
    template<class Bases,class Sizes>
    typename boost::enable_if_c < (boost::mpl::size<Bases>::value == 1)
                               && (boost::mpl::size<Sizes>::value == 1)
                                >::type
    init ( Bases const& b , Sizes const& s )
    {
      mData.restructure ( boost::fusion::at_c<0>(b)
                        , boost::fusion::at_c<0>(s)
                        );
    }

    ////////////////////////////////////////////////////////////////////////////
    // Swapping
    ////////////////////////////////////////////////////////////////////////////
    void swap( block& src ) { swap(mData,src.mData); }

    ////////////////////////////////////////////////////////////////////////////
    // resize/rebase/restructure block
    ////////////////////////////////////////////////////////////////////////////
    template<class Diff>  void rebase(Diff b) { mData.rebase(b); }
    template<class Size>  void resize(Size s) { mData.resize(s); }

    template<class Base,class Size>
    void restructure( Base const& b, Size const& s )
    {
      mData.restructure(b,s);
    }

    ////////////////////////////////////////////////////////////////////////////
    // IndexedContainer Interface
    ////////////////////////////////////////////////////////////////////////////
    template<class Position>
    reference operator()(Position const& pos)
    {
      return mData[boost::fusion::at_c<0>(pos)];
    }

    template<class Position>
    const_reference operator()(Position const& pos) const
    {
      return mData[boost::fusion::at_c<0>(pos)];
    }

    private:
    ////////////////////////////////////////////////////////////////////////////
    // Data member
    ////////////////////////////////////////////////////////////////////////////
    data_type mData;
  };
} }

#endif
