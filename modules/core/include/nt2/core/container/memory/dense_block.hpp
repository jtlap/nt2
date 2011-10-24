//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_DENSE_BLOCK_HPP
#define NT2_CORE_CONTAINER_MEMORY_DENSE_BLOCK_HPP

//==============================================================================
/**
  * \file
  * \brief Defines and implements the \c nt2::memory::dense_block class
  **/
//==============================================================================

#include <boost/mpl/at.hpp>
#include <boost/mpl/assert.hpp>
#include <nt2/core/settings/size.hpp>
#include <nt2/core/settings/index.hpp>
#include <nt2/core/settings/shape.hpp>
#include <nt2/core/settings/option.hpp>
#include <nt2/sdk/memory/allocator.hpp>
#include <nt2/sdk/memory/lead_padding.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <boost/simd/sdk/simd/meta/is_native.hpp>
//#include <nt2/core/container/functions/expr/load.hpp>
#include <nt2/include/functions/store.hpp>
#include <nt2/core/container/functions/expr/store.hpp>
#include <nt2/core/container/memory/iliffe_buffer.hpp>

namespace nt2 { namespace memory
{
  template<class Type, class Layout> struct dense_block
  {
    //==========================================================================
    // Retrieve size & number of dimensions from Layout
    //==========================================================================
    typedef typename meta::option<Layout, tag::of_size_>::type extent_type;
    static const std::size_t  dimensions  = extent_type::static_size;
    static const bool         is_static   = extent_type::static_status;

    //==========================================================================
    // Retrieve base indices
    //==========================================================================
    typedef typename meta::option<Layout, tag::index_>::type::type index_type;

    //==========================================================================
    // Retrieve padding strategy
    //==========================================================================

    //==========================================================================
    // Retrieve allocator
    //==========================================================================

    //==========================================================================
    // Simply builds a iliffe_buffer from gathered informations
    //==========================================================================
    typedef iliffe_buffer < dimensions
                          , Type
                          , lead_padding
                          , allocator<Type>
                          >                       buffer_type;

    //==========================================================================
    /** Type of the allocator used to handle memory                           */
    //==========================================================================
    typedef allocator<Type>                                      allocator_type;

    //==========================================================================
    /** Type of the value stored in current buffer                            */
    //==========================================================================
    typedef typename allocator_type::value_type                      value_type;

    //==========================================================================
    /** Type of the pointer giving access to the stored values                */
    //==========================================================================
    typedef typename allocator_type::pointer                            pointer;

    //==========================================================================
    /** Type of the pointer giving access to the stored values as constants   */
    //==========================================================================
    typedef typename allocator_type::const_pointer                const_pointer;

    //==========================================================================
    /** Type of the iterator to the iliffe_buffer values                      */
    //==========================================================================
    typedef typename allocator_type::pointer                           iterator;

    //==========================================================================
    /** Type of the const_iterator to the iliffe_buffer values                */
    //==========================================================================
    typedef typename allocator_type::const_pointer               const_iterator;

    //==========================================================================
    /** Type of reference to a value                                          */
    //==========================================================================
    typedef typename allocator_type::reference                        reference;

    //==========================================================================
    /** Type of reference to a constant value                                 */
    //==========================================================================
    typedef typename allocator_type::const_reference            const_reference;

    //==========================================================================
    /** Type representing an amount of values                                 */
    //==========================================================================
    typedef typename allocator_type::size_type                        size_type;

    //==========================================================================
    /** Type representing an offset between values                            */
    //==========================================================================
    typedef typename allocator_type::difference_type            difference_type;

    //==========================================================================
    // dense_block default construct - initialize statically sized buffer
    //==========================================================================
    dense_block() { init( boost::mpl::bool_<is_static>() ); }

    //==========================================================================
    // dense_block sized construct - initialize only dynamic buffer
    //==========================================================================
    dense_block( extent_type const& sz )
    {
      BOOST_MPL_ASSERT_MSG( !is_static
                          , CANT_RESIZE_STATIC_BLOCK
                          , (dense_block)
                          );

      initialize( data_, sz.data(), index_type(), lead_padding() );
    }

    //==========================================================================
    // dense_block destructor
    //==========================================================================
    ~dense_block() {}

    //==========================================================================
    // Random Access operators -- TODO REMOVE later
    //==========================================================================
    template<class Position> BOOST_DISPATCH_FORCE_INLINE
    reference operator()(Position const& pos)
    {
      return dereference<dimensions>(data_,pos);
    }
    
    template<class Position> BOOST_DISPATCH_FORCE_INLINE
    const_reference operator()(Position const& pos) const
    {
      return dereference<dimensions>(data_,pos);
    }

    //==========================================================================
    // Resize a dense_block
    //==========================================================================
    void resize( extent_type const& sz ) 
    { 
      memory::resize( data_, sz.data(), index_type(), lead_padding() );
    }

    //==========================================================================
    // Externally store a value in dense_block
    //==========================================================================
    template<class Position, class Value> BOOST_DISPATCH_FORCE_INLINE 
    Value store( Position const& pos, Value const& value )
    {
      //========================================================================
      // In SIMD mode, actual bounds on the inner-most loop are off by the
      // scalar-based base index. This value compute the shift to apply to the
      // scalar address and to the local position in order to access the proper
      // set of SIMD data in memory.
      //========================================================================
      static  const std::size_t 
              local_shift = boost::simd::meta::is_native<Value>::value 
                          ? boost::mpl::at_c<index_type,0>::type::value 
                          : 0;

      return nt2::store ( value
                        , dereference<dimensions-1>(data_,pos) + local_shift
                        , pos[0] - local_shift
                        );
    }

    //==========================================================================
    // Externally load a value from dense_block
    //==========================================================================
/*
    template<class Position, class Target> BOOST_DISPATCH_FORCE_INLINE 
    typename Target::type load( Position const& pos, Target const& )
    {
      typedef typename Target::type that_type;

      //========================================================================
      // In SIMD mode, actual bounds on the inner-most loop are off by the
      // scalar-based base index. This value compute the shift to apply to the
      // scalar address and to the local position in order to access the proper
      // set of SIMD data in memory.
      //========================================================================
      static  const std::size_t 
              local_shift = boost::simd::meta::is_native<that_type>::value 
                          ? boost::mpl::at_c<index_type,0>::value 
                          : 0;

      return 
      nt2::load<that_type> ( dereference<dimensions-1>(data_,pos) + local_shift
                           , pos[0] - local_shift
                           );
    }
*/
    private:
    void init( boost::mpl::true_ const& )
    {
      extent_type e;
      initialize( data_, e.data(), index_type(), lead_padding() );
    }

    void init( boost::mpl::false_ const& ) {}

    buffer_type data_;
  };
} }

namespace nt2 
{ 
  //============================================================================
  // Tie dense_ shape to dense_block
  //============================================================================
  struct dense_
  {
    template<class Type, class Settings> struct apply
    {
      typedef memory::dense_block<Type,Settings> type;
    };
  };
}

namespace boost { namespace dispatch { namespace meta
{
  template<class Type, class Settings>
  struct value_of< nt2::memory::dense_block<Type, Settings> >
  {
    typedef Type type;
  };
} } }


#endif
