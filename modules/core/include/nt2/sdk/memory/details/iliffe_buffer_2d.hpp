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
  template< typename T, std::size_t S
          , std::ptrdiff_t BI , std::ptrdiff_t BO
          >
  struct  iliffe_buffer < boost::mpl::size_t<2>
                        , array_buffer<T ,S,BI>
                        , array_buffer<T*,S,BO>
                        >
        : public array_buffer<T,S,BI>
  {
    typedef array_buffer<T,S,BI>                      parent;
    typedef array_buffer<T*,S,BO>                     index_parent;
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
      return access ( meta::as_sequence(pos)
                    , boost::fusion::size(meta::as_sequence(pos))
                    );
    }
    
    template<class Position>
    BOOST_FORCEINLINE const_reference operator[]( Position const& pos ) const
    {
      return access ( meta::as_sequence(pos)
                    , boost::fusion::size(meta::as_sequence(pos))
                    );
    }

    //==========================================================================
    /**
      * Return the lowest indices of the iliffe_buffer
     **/
    //==========================================================================
    boost::fusion::
    vector< typename parent::difference_type
          , typename index_parent::difference_type
          >
    lower() const
    {
      boost::fusion::
      vector< typename parent::difference_type
            , typename index_parent::difference_type
            >
      that(BI,BO);
      return that;
    }

    //==========================================================================
    /**
      * Return the upper indices of the iliffe_buffer
     **/
    //==========================================================================
    boost::fusion::
    vector< typename parent::difference_type
          , typename index_parent::difference_type
          >
    upper() const
    {
    boost::fusion::
    vector< typename parent::difference_type
          , typename index_parent::difference_type
          > that(BI,array_buffer<T*,S,BO>::upper());
      return that;
    }

    //==========================================================================
    /**
      * Return the sizes of the iliffe_buffer
     **/
    //==========================================================================
    boost::fusion::
    vector< typename parent::size_type
          , typename index_parent::size_type
          >
    size() const
    {
      boost::fusion::
      vector< typename parent::size_type
            , typename index_parent::size_type
            > that(1,S);
      return that;
    }

    protected:
    
    //==========================================================================
    // Access for 1D Position
    //==========================================================================
    template<class Position> BOOST_FORCEINLINE
    reference access(Position const& p, boost::mpl::int_<1> const& )
    {
      return parent::operator[] ( boost::fusion::at_c<0>(p) );
    }

    template<class Position> BOOST_FORCEINLINE
    const_reference access(Position const& p, boost::mpl::int_<1> const& ) const
    {
      return parent::operator[] ( boost::fusion::at_c<0>(p) );
    }

    //==========================================================================
    // Access for 2D Position
    //==========================================================================
    template<class Position> BOOST_FORCEINLINE
    reference access(Position const& p, boost::mpl::int_<2> const& )
    {
      return parent::operator[] ( boost::fusion::at_c<1>(p) );
    }

    template<class Position> BOOST_FORCEINLINE
    const_reference access(Position const& p, boost::mpl::int_<2> const& ) const
    {
      return parent::operator[] ( boost::fusion::at_c<1>(p) );
    }
  };
} }

#endif
