//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_MEMORY_DETAILS_CONTAINER_BASE_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_CONTAINER_BASE_HPP_INCLUDED

#include <nt2/core/settings/size.hpp>
#include <nt2/core/settings/shape.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/sdk/memory/block_facade.hpp>
#include <nt2/core/utility/of_size/pad.hpp>
#include <nt2/include/functions/deflate.hpp>
#include <nt2/include/functions/inflate.hpp>
#include <nt2/core/container/dsl/forward.hpp>
#include <nt2/sdk/memory/adapted/container.hpp>
#include <nt2/core/settings/normalize_settings.hpp>

namespace nt2 { namespace details
{
  //============================================================================
  // Defines the base shared elements of container class specifications
  //============================================================================
  template<class Tag, class T, class S> struct container_base
  {
    //==========================================================================
    // Builds the block from the normalizedd settings
    //==========================================================================
    typedef typename meta::normalize_settings<Tag,T,S>::type        settings_type;
    typedef typename meta::option<settings_type, tag::shape_>::type shape_t;
    typedef memory::block<shape_t,T,settings_type>                  block_t;

    //==========================================================================
    // Public type interface
    //==========================================================================
    typedef typename block_t::allocator_type        allocator_type;
    typedef typename block_t::value_type            value_type;
    typedef typename block_t::iterator              iterator;
    typedef typename block_t::const_iterator        const_iterator;
    typedef typename block_t::reference             reference;
    typedef typename block_t::const_reference       const_reference;
    typedef typename block_t::size_type             size_type;
    typedef typename block_t::difference_type       difference_type;
    typedef typename allocator_type::pointer        pointer;
    typedef typename allocator_type::const_pointer  const_pointer;

    //==========================================================================
    // container is handling the size/base storage for the proto terminal
    //==========================================================================
    typedef typename meta::option<settings_type, tag::of_size_>::type sizes_type;
    typedef typename meta::option<settings_type, tag::index_>::type   index_type;
    typedef sizes_type const&                                         extent_type;

    //==========================================================================
    // Potential container lead padding value
    //==========================================================================
    typedef typename meta::option<settings_type,tag::lead_padding_>::type lead_t;

    //==========================================================================
    // container knows if its size is statically defined or not
    //==========================================================================
    typedef boost::mpl::bool_<sizes_type::static_status>  is_static_sized;

    //==========================================================================
    // If size is static, perform allocation from default constructor
    //==========================================================================
    template<class Size>
    inline void init( block_t& block, Size const& sz, boost::mpl::true_ const& )
    {
      block.resize( pad(sz,lead_t::value) );
    }

    template<class Size>
    inline void init( block_t&, Size const&, boost::mpl::false_ const& ) {}

    //==========================================================================
    // Resize inner block if resizing is allowed
    //==========================================================================
    template<class Size> inline
    void resize ( block_t& block, Size const& new_sz, sizes_type& old_sz
                , boost::mpl::false_ const&
                )
    {
      if( new_sz != old_sz )
      {
        old_sz = sizes_type(new_sz);
        block.resize( pad(old_sz,lead_t::value) );
      }
    }

    //==========================================================================
    // Force a static assert if a statically sized container is resized
    //==========================================================================
    template<class Size> inline
    void resize( block_t&, Size const&, sizes_type&, boost::mpl::true_ const&)
    {
      BOOST_MPL_ASSERT_MSG
      ( (sizeof(Size) == 0)
      , STATICALLY_SIZED_CONTAINER_CANT_BE_RESIZED_DYNAMICALLY
      , (Size)
      );
    }

    //==========================================================================
    // Multidimensionnal access handling
    // Various cases to take care of to optimize access to storage:
    //==========================================================================
    template<class Position>
    BOOST_FORCEINLINE reference
    access( Position const& p, block_t& b, sizes_type const& s)
    {
      typedef typename boost::fusion::result_of::size<Position>::type ps_t;

      return access ( p , b , s
                    , boost::mpl::size_t<sizes_type::static_size>()
                    , boost::mpl::size_t<ps_t::value>()
                    );
    }

    template<class Position>
    BOOST_FORCEINLINE const_reference
    access( Position const& p, block_t const& b, sizes_type const& s) const
    {
      typedef typename boost::fusion::result_of::size<Position>::type ps_t;

      return access ( p , b , s
                    , boost::mpl::size_t<sizes_type::static_size>()
                    , boost::mpl::size_t<ps_t::value>()
                    );
    }

    //==========================================================================
    // Access a 1D Block with a nD position -> go directly to the block
    // Access a nD Block with a 2D position -> go directly to the block
    //==========================================================================
    template<class Position, std::size_t N>
    BOOST_FORCEINLINE reference
    access( Position const& p, block_t& b, sizes_type const&
          , boost::mpl::size_t<1> const&, boost::mpl::size_t<N> const&
          )
    {
      return b[boost::fusion::at_c<0>(p)];
    }

    template<class Position, std::size_t N>
    BOOST_FORCEINLINE const_reference
    access( Position const& p, block_t const& b, sizes_type const&
          , boost::mpl::size_t<1> const&, boost::mpl::size_t<N> const&
          ) const
    {
      return b[boost::fusion::at_c<0>(p)];
    }

    template<class Position, std::size_t N>
    BOOST_FORCEINLINE reference
    access( Position const& p, block_t& b, sizes_type const&
          , boost::mpl::size_t<N> const&, boost::mpl::size_t<2> const&
          )
    {
      return b[p];
    }

    template<class Position, std::size_t N>
    BOOST_FORCEINLINE const_reference
    access( Position const& p, block_t const& b, sizes_type const&
          , boost::mpl::size_t<N> const&, boost::mpl::size_t<2> const&
          ) const
    {
      return b[p];
    }

    //==========================================================================
    // Access a nD Block with a 1D or 0D position -> unpack if needed and go 2D
    //==========================================================================
    template<class Position, std::size_t N>
    BOOST_FORCEINLINE reference
    access( Position const& p, block_t& b, sizes_type const& s
          , boost::mpl::size_t<N> const&, boost::mpl::size_t<1> const&
          )
    {
      return b[unpack(p,s,lead_t())];
    }

    template<class Position, std::size_t N>
    BOOST_FORCEINLINE const_reference
    access( Position const& p, block_t const& b, sizes_type const& s
          , boost::mpl::size_t<N> const&, boost::mpl::size_t<1> const&
          ) const
    {
      return b[unpack(p,s,lead_t())];
    }

    template<class Position, std::size_t N>
    BOOST_FORCEINLINE reference
    access( Position const& p, block_t& b, sizes_type const& s
          , boost::mpl::size_t<N> const& n, boost::mpl::size_t<0> const&
          )
    {
      return access(p, b, s, n, boost::mpl::size_t<1>() );
    }

    template<class Position, std::size_t N>
    BOOST_FORCEINLINE const_reference
    access( Position const& p, block_t const& b, sizes_type const& s
          , boost::mpl::size_t<N> const& n, boost::mpl::size_t<0> const&
          ) const
    {
      return access(p, b, s, n, boost::mpl::size_t<1>() );
    }

    //==========================================================================
    // Access a nD Block with a mD position -> deflate
    //==========================================================================
    template<class Position, std::size_t N, std::size_t M>
    BOOST_FORCEINLINE reference
    access( Position const& p, block_t& b, sizes_type const& s
          , boost::mpl::size_t<N> const&, boost::mpl::size_t<M> const&
          )
    {
      return b[deflate(s,p,typename index_type::type())];
    }

    template<class Position, std::size_t N, std::size_t M>
    BOOST_FORCEINLINE const_reference
    access( Position const& p, block_t const& b, sizes_type const& s
          , boost::mpl::size_t<N> const&, boost::mpl::size_t<M> const&
          ) const
    {
      return b[deflate(s,p,typename index_type::type())];
    }

    //==========================================================================
    // Unpack 1D position if lead padding is present
    //==========================================================================
    template<class Pos> BOOST_FORCEINLINE
    Pos const&
    unpack( Pos const& p, sizes_type const&
          , lead_padding_strategy_<1> const&
          ) const
    {
      return p;
    }

    template<class Pos,std::ptrdiff_t N> BOOST_FORCEINLINE
    boost::fusion::vector<difference_type,difference_type>
    unpack( Pos const& p, sizes_type const& sz
          , lead_padding_strategy_<N> const&
          ) const
    {
      return nt2::inflate(sz,p,typename index_type::type());
    }
  };
} }

namespace nt2 { namespace memory
{
  template<class Tag, class ID, class T, class S> struct container;

  //============================================================================
  // Generic swap for container of any kind
  //============================================================================
  template<class Tag, class ID, class T, class S>
  void swap(container<Tag,ID,T,S>& a,container<Tag,ID,T,S>& b)
  {
    a.swap(b);
  }
} }

#endif
