#if !BOOST_PP_IS_ITERATING
/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_BLOCK_HPP_INCLUDED
#define NT2_SDK_MEMORY_BLOCK_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Multidimensional memory block with NRC style allocation
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/stride.hpp>
#include <boost/fusion/include/at.hpp>
#include <nt2/extension/parameters.hpp>
#include <boost/fusion/include/nview.hpp>
#include <nt2/sdk/error/static_assert.hpp>
#include <boost/fusion/include/make_vector.hpp>
#include <nt2/sdk/memory/details/make_buffer.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>

namespace nt2 { namespace memory
{
  //////////////////////////////////////////////////////////////////////////////
  // block is a multidimensionnal buffer using NRC model and bearing all the
  // related options in its parameters
  //////////////////////////////////////////////////////////////////////////////
  template< class Type
          , std::size_t Dimensions
          , class Bases
          , class Sizes
          , class Storage
          , class Padding
          , class Allocator
          >
  class block;
} }

/*
////////////////////////////////////////////////////////////////////////////////
// Macro generating the list of inner buffer members constructor
////////////////////////////////////////////////////////////////////////////////
#define NT2_MAKE_CTOR(z,n,t)                                                \
NT2_DATA_MEMBER(BOOST_PP_INC(n))( boost::fusion::at_c<BOOST_PP_INC(n)>(bs)  \
                                , boost::fusion::at_c<BOOST_PP_INC(n)>(ss)  \
                                )                                           \

////////////////////////////////////////////////////////////////////////////////
// Macro generating a chain of []
////////////////////////////////////////////////////////////////////////////////
#define NT2_ACCESS(z,n,t)                                   \
[ boost::fusion::at_c<BOOST_PP_SUB(BOOST_PP_DEC(t),n)>(p) ] \

////////////////////////////////////////////////////////////////////////////////
// Macro generating a chain of [] for under-access
////////////////////////////////////////////////////////////////////////////////
#define NT2_OVERACCESS(z,n,t)                                             \
template<class Position> const_reference                                  \
access( Position const& p, boost::mpl::int_<n> const& )                   \
{                                                                         \
  return NT2_DATA_MEMBER(BOOST_PP_DEC(n))BOOST_PP_REPEAT(n,NT2_ACCESS,n); \
}                                                                         \
template<class Position> const_reference                                  \
access( Position const& p, boost::mpl::int_<n> const& ) const             \
{                                                                         \
  return NT2_DATA_MEMBER(BOOST_PP_DEC(n))BOOST_PP_REPEAT(n,NT2_ACCESS,n); \
}                                                                         \

////////////////////////////////////////////////////////////////////////////////
// Macro generating a chain of resize
////////////////////////////////////////////////////////////////////////////////
#define NT2_RESIZE(z,n,t)                                 \
NT2_DATA_MEMBER(n).resize ( boost::fusion::at_c<n>(base_) \
                          , boost::fusion::at_c<n>(size_) \
                          );                              \

*/

#define  BOOST_PP_FILENAME_1        "nt2/sdk/memory/block.hpp"
#define  BOOST_PP_ITERATION_LIMITS  (1, NT2_MAX_ARITY)
#include BOOST_PP_ITERATE()

#endif

#else
////////////////////////////////////////////////////////////////////////////////
// Current specialization being compiled
////////////////////////////////////////////////////////////////////////////////
#define DIM  BOOST_PP_ITERATION()

namespace nt2 { namespace memory
{
  template< class Type
	  , class Bases, class Sizes, class Storage, class Padding
	  , class Allocator
          >
  class block<Type,DIM,Bases,Sizes,Storage,Padding,Allocator>
  {
    public:

    ////////////////////////////////////////////////////////////////////////////
    // Check that we don't pass incorrect Base/Size/Storage containers
    ////////////////////////////////////////////////////////////////////////////
    NT2_STATIC_ASSERT ( (boost::mpl::size<Bases>::value == DIM)
                      , BOOST_PP_CAT(BASES_EXTENT_IS_NOT_,DIM)
                      , (Bases)
                      );

    NT2_STATIC_ASSERT ( (boost::mpl::size<Sizes>::value == DIM)
                      , BOOST_PP_CAT(SIZES_EXTENT_IS_NOT_,DIM)
                      , (Sizes)
                      );

    NT2_STATIC_ASSERT ( (boost::mpl::size<Storage>::value == DIM)
                      , BOOST_PP_CAT(STORAGE_EXTENT_IS_NOT_,DIM)
                      , (Sizes)
                      );

    NT2_STATIC_ASSERT ( (   boost::mpl::size<Bases>::value
                        ==  boost::mpl::size<Sizes>::value
                        )
                      , BASES_AND_SIZES_EXTENTS_MISMATCH
                      , (Bases,Sizes)
                      );

    NT2_STATIC_ASSERT ( (   boost::mpl::size<Bases>::value
                        ==  boost::mpl::size<Storage>::value
                        )
                      , BASES_AND_STORAGE_EXTENTS_MISMATCH
                      , (Bases,Sizes)
                      );

    NT2_STATIC_ASSERT ( (   boost::mpl::size<Storage>::value
                        ==  boost::mpl::size<Sizes>::value
                        )
                      , STORAGE_AND_SIZES_EXTENTS_MISMATCH
                      , (Bases,Sizes)
                      );

    ////////////////////////////////////////////////////////////////////////////
    // Public types
    ////////////////////////////////////////////////////////////////////////////
    typedef boost::mpl::int_<DIM> dimension_value_type;

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
    // Typedefs for real Bases and Sizes and their Storage counterpart
    ////////////////////////////////////////////////////////////////////////////
    typedef Bases   bases_type;
    typedef Sizes   sizes_type;
    typedef Storage storage_order_type;
    
    struct storage_helper
    {
      static Sizes& s;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL
      ( nested
      , (boost::fusion::nview<Sizes const,Storage>(s))
      );

      typedef typename nested::type type;
    };

    typedef typename storage_helper::type stored_sizes_type;

    ////////////////////////////////////////////////////////////////////////////
    // Aggregated buffers type
    ////////////////////////////////////////////////////////////////////////////
    typedef  typename meta
	   ::make_buffers<Type,DIM,Bases,Sizes,Padding,Allocator>::type data_type;

    ////////////////////////////////////////////////////////////////////////////
    // Default constructor
    ////////////////////////////////////////////////////////////////////////////
    block() : data_(), base_(), size_()
    {
//      if(buffer0_type::is_static::value) link(dimension_value_type());
    }

/*
    ////////////////////////////////////////////////////////////////////////////
    // Constructor from {bases,sizes}
    ////////////////////////////////////////////////////////////////////////////
    block ( Bases const& bs, Sizes const& ss )
        : data0_( boost::fusion::at_c<0>(bs), typename Padding::size()(ss) )
        BOOST_PP_COMMA_IF(BOOST_PP_GREATER(DIM,1))
        BOOST_PP_ENUM(BOOST_PP_DEC(DIM), NT2_MAKE_CTOR,~)
        , base_(bs)
        , size_(ss)
    {
      link( dimension_value_type() );
    }
*/
    ////////////////////////////////////////////////////////////////////////////
    // Destructor
    ////////////////////////////////////////////////////////////////////////////
    ~block() {}

    ////////////////////////////////////////////////////////////////////////////
    // Assignement from same block type
    ////////////////////////////////////////////////////////////////////////////
    block& operator=( block const& src )
    {
      if( this != &src)
      {
				data_ = src.data_;
        base_ = src.base_;
        size_ = src.size_;
        link( boost::mpl::int_<DIM>() );
      }

      return *this;
    }
/*
    ////////////////////////////////////////////////////////////////////////////
    // Data accessor - proper case
    ////////////////////////////////////////////////////////////////////////////
    template<class Position>
    typename boost::enable_if_c < (boost::mpl::size<Position>::value >= DIM)
                                , reference
                                >::type
    operator()( Position const& p )
    {
      return  NT2_DATA_MEMBER(BOOST_PP_DEC(DIM))
              BOOST_PP_REPEAT(DIM,NT2_ACCESS,DIM);
    }

    template<class Position>
    typename boost::enable_if_c < (boost::mpl::size<Position>::value >= DIM)
                                , const_reference
                                >::type
    operator()( Position const& p ) const
    {
      return  NT2_DATA_MEMBER(BOOST_PP_DEC(DIM))
              BOOST_PP_REPEAT(DIM,NT2_ACCESS,DIM);
    }
*/
    ////////////////////////////////////////////////////////////////////////////
    // Data accessor : smaller case
    ////////////////////////////////////////////////////////////////////////////
    #if (DIM > 1)
/*  template<class Position>
    typename boost::enable_if_c < (boost::mpl::size<Position>::value < CURRENT_DIM)
                                , reference
                                >::type
    operator()( Position const& p )
    {
      return access(p, boost::mpl::int_<boost::mpl::size<Position>::value>());
    }

    template<class Position>
    typename boost::enable_if_c < (boost::mpl::size<Position>::value < CURRENT_DIM)
                                , const_reference
                                >::type
    operator()( Position const& p ) const
    {
      return access(p, boost::mpl::int_<boost::mpl::size<Position>::value>());
    }
*/
    #endif

    ////////////////////////////////////////////////////////////////////////////
    // Access to bases and sizes
    ////////////////////////////////////////////////////////////////////////////
    Bases bases()  const { return base_;  }
    Sizes sizes()  const { return size_;  }

    ////////////////////////////////////////////////////////////////////////////
    // Buffer on dimension N
    ////////////////////////////////////////////////////////////////////////////
    template<std::size_t N>
    typename boost::enable_if_c < (N>0 && N<=DIM)
				, typename  boost::fusion::result_of
					  ::at_c<data_type const,N-1>::type
				>::type
    data() const
    {
      return boost::fusion::at_c<N-1>(data_);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Size on dimension N
    ////////////////////////////////////////////////////////////////////////////
    template<std::size_t N>
    typename boost::enable_if_c<(N>0 && N<=DIM),size_type>::type
    size() const
    {
      return boost::fusion::at_c<N-1>(size_);
    }

    template<std::size_t N>
    typename boost::disable_if_c<(N>0 && N<=DIM),size_type>::type
    size() const
    {
      return 1;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Lower bound of valid index on dimension N
    ////////////////////////////////////////////////////////////////////////////
    template<std::size_t N>
    typename boost::enable_if_c<(N>0 && N<=DIM),difference_type>::type
    lower() const
    {
      return boost::fusion::at_c<N-1>(base_);
    }

    template<std::size_t N>
    typename boost::disable_if_c<(N>0 && N<=DIM),difference_type>::type
    lower() const
    {
      return 1;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Upper bound of valid index on dimension N
    ////////////////////////////////////////////////////////////////////////////
    template<std::size_t N>
    typename boost::enable_if_c<(N>0 && N<=DIM),difference_type>::type
    upper() const
    {
      return size<N>()+lower<N>()-1;
    }

    template<std::size_t N>
    typename boost::disable_if_c<(N>0 && N<=DIM),difference_type>::type
    upper() const
    {
      return 1;
    }
		
    protected:
    ////////////////////////////////////////////////////////////////////////////
    // Access to a block with less index than needed
    ////////////////////////////////////////////////////////////////////////////
/*
    #if (CURRENT_DIM > 1)
    template<class Position> reference
    access( Position const& p, boost::mpl::int_<1> const& )
    {
      typedef typename boost::fusion::result_of::value_at_c<Position,0>::type type;
      type idx = boost::fusion::at_c<0>(p) - boost::fusion::at_c<0>(base_);
      type lead  = idx % boost::fusion::at_c<0>(size_);
      type outer = idx / boost::fusion::at_c<0>(size_);
      return data1_[outer][lead];
    }

    template<class Position> const_reference
    access( Position const& p, boost::mpl::int_<1> const& ) const
    {
      typedef typename boost::fusion::result_of::value_at_c<Position,0>::type type;
      type idx = boost::fusion::at_c<0>(p) - boost::fusion::at_c<0>(base_);
      type lead  = idx % boost::fusion::at_c<0>(size_);
      type outer = idx / boost::fusion::at_c<0>(size_);
      return data1_[outer][lead];
    }

    BOOST_PP_REPEAT_FROM_TO(2,CURRENT_DIM,NT2_OVERACCESS,~)
    #endif
*/

    ////////////////////////////////////////////////////////////////////////////
    // Link indexes and data
    ////////////////////////////////////////////////////////////////////////////
    void link( boost::mpl::int_<1> const& ) {}

    #if (CURRENT_DIM > 1)
/*   
    void link( boost::mpl::int_<2> const& )
    {
      data1_.origin()[0] = data0_.begin();
      for(size_type i=1;i<data1_.size();++i)
        data1_.origin()[i]  = data1_.origin()[i-1]
                            + stride<Padding,1>(size_);
    }

void link( boost::mpl::int_<n> const&, size_type prev = 1)                  \
{                                                                           \
  size_type       sz = NT2_DATA_MEMBER(BOOST_PP_DEC(n)).size()*prev;        \
  NT2_DATA_MEMBER(BOOST_PP_DEC(n)).origin()[0]                              \
                              = NT2_DATA_MEMBER(BOOST_PP_SUB(n,2)).begin(); \
  for(size_type i=1;i<sz;++i)                                               \
  {                                                                         \
    NT2_DATA_MEMBER(BOOST_PP_DEC(n)).origin()[i]                            \
          = NT2_DATA_MEMBER(BOOST_PP_DEC(n)).origin()[i-1]                  \
          + boost::fusion::at_c<BOOST_PP_SUB(n,2)>(size_);                  \
  }                                                                         \
  link( boost::mpl::int_<n-1>(), sz);                                       \
}                                                                           \

*/
    #endif

    private:
    data_type  data_;
    Bases      base_;
    Sizes      size_;
  };
} }

#endif
