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

////////////////////////////////////////////////////////////////////////////////
// Macro generating a chain of []
////////////////////////////////////////////////////////////////////////////////
#define NT2_ACCESS(z,n,t)                                                     \
[ boost::fusion::at_c <                                                       \
      boost::mpl::at_c<Storage,BOOST_PP_SUB(BOOST_PP_DEC(t),n)>::type::value  \
                      >(p)                                                    \
]                                                                             \
/**/

////////////////////////////////////////////////////////////////////////////////
// Macro generating a chain of [] for under-access
////////////////////////////////////////////////////////////////////////////////
#define NT2_UNDER_ACCESS(z,n,t)                                   \
template<class Position, class Sz>                                \
typename boost::enable_if_c<Sz::value == n,reference>::type       \
access( Position const& p, Sz const& )                            \
{                                                                 \
  return data<n>() BOOST_PP_REPEAT(n,NT2_ACCESS,n);               \
}                                                                 \
template<class Position, class Sz>                                \
typename boost::enable_if_c<Sz::value == n,const_reference>::type \
access( Position const& p, Sz const& ) const                      \
{                                                                 \
  return data<n>() BOOST_PP_REPEAT(n,NT2_ACCESS,n);               \
}                                                                 \
/**/

#define  BOOST_PP_FILENAME_1        "nt2/sdk/memory/block.hpp"
#define  BOOST_PP_ITERATION_LIMITS  (1, NT2_MAX_DIMENSIONS)
#include BOOST_PP_ITERATE()

#undef NT2_ACCESS
#undef NT2_UNDER_ACCESS

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
                      , BOOST_PP_CAT(BASES_EXTENT_SIZE_NOT_EQUAL_TO_,DIM)
                      , "Block base dimension mismatch."
                      );

    NT2_STATIC_ASSERT ( (boost::mpl::size<Sizes>::value == DIM)
                      , BOOST_PP_CAT(BASES_EXTENT_SIZE_NOT_EQUAL_TO_,DIM)
                      , "Block size dimension mismatch."
                      );

    NT2_STATIC_ASSERT ( (boost::mpl::size<Storage>::value == DIM)
                      , BOOST_PP_CAT(BASES_EXTENT_SIZE_NOT_EQUAL_TO_,DIM)
                      , "Block storage order dimension mismatch."
                      );

    ////////////////////////////////////////////////////////////////////////////
    // Public types
    ////////////////////////////////////////////////////////////////////////////
    typedef boost::mpl::int_<DIM> dimension_value_type;
    BOOST_STATIC_CONSTANT ( std::size_t, static_dimension_value = DIM );

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

    ////////////////////////////////////////////////////////////////////////////
    // If DIM > 1, compute the permuted bases and sizes type to take storage
    // order into account.
    // If DIM == 1, storage order makes no sense, so we save on compile time.
    ////////////////////////////////////////////////////////////////////////////
    #if (DIM > 1)
    template<class T> struct storage_helper
    {
      static T& s;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL
      ( nested
      , (boost::fusion::nview<T const,Storage>(s))
      );

      typedef typename nested::type type;
    };

    typedef typename storage_helper<Bases>::type  stored_bases_type;
    typedef typename storage_helper<Sizes>::type  stored_sizes_type;
    #else
    typedef Bases                                 stored_bases_type;
    typedef Sizes                                 stored_sizes_type;
    #endif

    ////////////////////////////////////////////////////////////////////////////
    // Aggregated buffers type
    ////////////////////////////////////////////////////////////////////////////
    typedef typename meta::make_buffers < Type, DIM
                                        , stored_bases_type
                                        , stored_sizes_type
                                        , Padding, Allocator>::type data_type;

    ////////////////////////////////////////////////////////////////////////////
    // Find out if the all buffers are static, triggering the static allocation
    ////////////////////////////////////////////////////////////////////////////
    template<class Buffer>  struct is_static : Buffer::is_static {};

    typedef typename
    boost::mpl::fold< data_type
                    , boost::mpl::true_
                    , boost::mpl::and_< boost::mpl::_1
                                      , is_static<boost::mpl::_2>
                                      >
                    >::type                                 static_status_type;

    ////////////////////////////////////////////////////////////////////////////
    // Default constructor
    ////////////////////////////////////////////////////////////////////////////
    block() : data_(), base_(), size_()
    {
      if(static_status_type::value) link(dimension_value_type());
    }

    ////////////////////////////////////////////////////////////////////////////
    // Constructor from {bases,sizes}
    ////////////////////////////////////////////////////////////////////////////
    block ( Bases const& bs, Sizes const& ss )  : base_(bs), size_(ss)
    {
      init( dimension_value_type() );
      link( dimension_value_type() );
    }

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
        data_ = src.data_; base_ = src.base_; size_ = src.size_;
        link( dimension_value_type() );
      }

      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Data accessor - proper case
    ////////////////////////////////////////////////////////////////////////////
    template<class Position>
    typename boost::enable_if_c < (boost::mpl::size<Position>::value >= DIM)
                                , reference
                                >::type
    operator()( Position const& p )
    {
      check_index(p,typename boost::mpl::size<Position>::type());
      return data<DIM>() BOOST_PP_REPEAT(DIM,NT2_ACCESS,DIM);
    }

    template<class Position>
    typename boost::enable_if_c < (boost::mpl::size<Position>::value >= DIM)
                                , const_reference
                                >::type
    operator()( Position const& p ) const
    {
      check_index(p,dimension_value_type());
      return  data<DIM>() BOOST_PP_REPEAT(DIM,NT2_ACCESS,DIM);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Smaller case for operator[] - Recompute toward 2D if 1D else snap data
    ////////////////////////////////////////////////////////////////////////////
    #if (DIM > 1)
    template<class Position>
    typename boost::enable_if_c < (boost::mpl::size<Position>::value < DIM)
                                , reference
                                >::type
    operator()( Position const& p )
    {
      return access(p, typename boost::mpl::size<Position>::type());
    }

    template<class Position>
    typename boost::enable_if_c < (boost::mpl::size<Position>::value < DIM)
                                , const_reference
                                >::type
    operator()( Position const& p ) const
    {
      return access(p, typename boost::mpl::size<Position>::type());
    }
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

    template<std::size_t N>
    typename boost::enable_if_c < (N>0 && N<=DIM)
                                , typename  boost::fusion::result_of
                                            ::at_c<data_type,N-1>::type
                                >::type
    data()
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
    // Check a position vlaue are in-bound
    ////////////////////////////////////////////////////////////////////////////
    template<class Position, class Sz>
    typename boost::enable_if_c<Sz::value>::type
    check_index( Position const& p, Sz const&) const
    {
      NT2_ASSERT(  boost::fusion::at_c<Sz::value-1>(p) >= lower<Sz::value>()
                && "Index below lowest valid value"
                );
      NT2_ASSERT( boost::fusion::at_c<Sz::value-1>(p) <= upper<Sz::value>()
                && "Index above greatest valid value"
                );
      check_index(p,boost::mpl::int_<Sz::value-1>() );
    }

    template<class Position, class Sz>
    typename boost::enable_if_c<!Sz::value>::type
    check_index( Position const& p, Sz const&) const {}

    ////////////////////////////////////////////////////////////////////////////
    // Access to a block with less index than needed
    // For 1D access, we reconstruct a padding aware 2D access
    // Other accesses are just starting form proper data bank instead of the
    // innermost one
    ////////////////////////////////////////////////////////////////////////////
    #if (DIM > 1)
    template<class Position,class Sz>
    typename boost::enable_if_c<Sz::value==1,reference>::type
    access( Position const& p, Sz const& )
    {
      NT2_ASSERT(  boost::fusion::at_c<0>(p) >= data<1>().lower()
                && "Index below lowest valid value"
                );
      NT2_ASSERT(  boost::fusion::at_c<0>(p) <= data<1>().upper()
                && "Index above greatest valid value"
                );

      typedef typename boost::fusion::result_of::value_at_c<Position,0>::type type;
      type idx = boost::fusion::at_c<0>(p) - data<1>().lower();
      type lead  = idx % data<1>().size()  + data<1>().lower();
      type outer = idx / data<1>().size()  + data<2>().lower();
      return data<2>()[outer][lead];
    }

    template<class Position, class Sz>
    typename boost::enable_if_c<Sz::value==1,const_reference>::type
    access( Position const& p, Sz const& ) const
    {
      NT2_ASSERT(  boost::fusion::at_c<0>(p) >= data<1>().lower()
                && "Index below lowest valid value"
                );
      NT2_ASSERT(  boost::fusion::at_c<0>(p) <= data<1>().upper()
                && "Index above greatest valid value"
                );

      typedef typename boost::fusion::result_of::value_at_c<Position,0>::type type;
      type idx = boost::fusion::at_c<0>(p) - data<1>().lower();
      type lead  = idx % data<1>().size()  + data<1>().lower();
      type outer = idx / data<1>().size()  + data<2>().lower();
      return data<2>()[outer][lead];
    }

    BOOST_PP_REPEAT_FROM_TO(2,DIM,NT2_UNDER_ACCESS,~)
    #endif

    ////////////////////////////////////////////////////////////////////////////
    // Recursively construct data buffers from Bases/Sizes sequence
    ////////////////////////////////////////////////////////////////////////////
    template<int N>
    void init( boost::mpl::int_<N> const& d )
    {
      boost::fusion::nview<Sizes const,Storage> sz(size_);
      boost::fusion::nview<Bases const,Storage> bz(base_);
      init(d,bz,sz);
    }

    template<class Bz, class Sz>
    void init( boost::mpl::int_<1> const&, Bz const& bz, Sz const& sz )
    {
      data<1>().restructure(boost::fusion::at_c<0>(bz),slice<1>(sz,Padding()));
    }

    template<class Bz, class Sz, int N>
    void init( boost::mpl::int_<N> const&, Bz const& bz, Sz const& sz )
    {
      data<N>().restructure(boost::fusion::at_c<N-1>(bz),slice<N>(sz,Padding()));
      init( boost::mpl::int_<N-1>() );
    }

    ////////////////////////////////////////////////////////////////////////////
    // Link indexes and data, NRC style and recursively
    //   _        _ _ _ _ _ _ _ _ _ _ _ _
    //  |_|----->|_|_|_|_|_|_|_|_|_|_|_|_|
    //  |_|-------------------^
    //
    ////////////////////////////////////////////////////////////////////////////
    template<int N>
    void link( boost::mpl::int_<N> const& d )
    {
      boost::fusion::nview<Sizes const,Storage> sz(size_);
      link( d, sz );
    }

    template<class Sz> void link( boost::mpl::int_<1> const&, Sz const&) {}

    template<int N,class Sz>
    void link( boost::mpl::int_<N> const&, Sz const& sz )
    {
      size_type offset = stride<N-1>(sz,Padding());
      size_type nbrow  = slice<N>(sz,Padding());

      data<N>().origin()[0] = data<N-1>().begin();
      for(size_type i=1;i<nbrow;++i)
        data<N>().origin()[i] = data<N>().origin()[i-1] + offset;
      link( boost::mpl::int_<N-1>(), sz );
    }

    private:
    data_type  data_;
    Bases      base_;
    Sizes      size_;
  };
} }

#undef DIM

#endif
