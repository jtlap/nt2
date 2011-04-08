#include <iostream>
#include <nt2/sdk/details/type_id.hpp>

#include <boost/fusion/adapted/array.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/nview.hpp>

#include <nt2/core/container/details/forward.hpp>
#include <nt2/core/container/details/block_data.hpp>

#include <nt2/sdk/memory/stride.hpp>
#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/memory/lead_padding.hpp>
#include <nt2/sdk/memory/global_padding.hpp>
#include <boost/fusion/include/for_each.hpp>

using namespace std;

namespace nt2 { namespace details
{
  //////////////////////////////////////////////////////////////////////////////
  // Hoisted class for size related block member functions
  //////////////////////////////////////////////////////////////////////////////
  template<class Sizes>
  struct block_size
  {
    block_size(Sizes const& sz) : mSize(sz) {}

    ////////////////////////////////////////////////////////////////////////////
    // size_type is the type holding the reuslt of the std like size() function
    ////////////////////////////////////////////////////////////////////////////
    typedef
    typename meta::call < tag::slice_ ( Sizes const&
                                      , memory::no_padding const&
                                      , boost::mpl::size_t<1> const&
                                      )
                        >::type                                       size_type;

    ////////////////////////////////////////////////////////////////////////////
    // Return the total number of effective elements in a block
    ////////////////////////////////////////////////////////////////////////////
    inline size_type size()  const
    {
      return slice<1>(mSize,memory::no_padding());
    }

    ////////////////////////////////////////////////////////////////////////////
    // Return if a block is empty
    ////////////////////////////////////////////////////////////////////////////
    bool empty() const { return this->size() != 0; }

    ////////////////////////////////////////////////////////////////////////////
    // Return the number of element on the Nth dimension
    ////////////////////////////////////////////////////////////////////////////
    template<std::size_t N>
    typename boost::enable_if_c < (N<=boost::mpl::size<Sizes>::value)
                                , typename boost::fusion::result_of
                                                ::at_c<Sizes const,N-1>::type
                                >::type
    size() const
    {
      return boost::fusion::at_c<N-1>(mSize);
    }

    template<std::size_t N>
    typename boost::disable_if_c< (N<=boost::mpl::size<Sizes>::value)
                                , int
                                >::type
    size() const
    {
      return 1;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Stored size informations - we can't rely on retrieving them from the
    // data block sequence as each buffer contains its fully required space.
    ////////////////////////////////////////////////////////////////////////////
    Sizes mSize;
  };

  //////////////////////////////////////////////////////////////////////////////
  // Hoisted class for base related block member functions
  //////////////////////////////////////////////////////////////////////////////
  template<class Bases>
  struct block_base
  {
    block_base(Bases const& bs) : mBase(bs) {}

    ////////////////////////////////////////////////////////////////////////////
    // Return the starting index on the Nth dimension
    ////////////////////////////////////////////////////////////////////////////
    template<std::size_t N>
    typename boost::enable_if_c < (N<=boost::mpl::size<Bases>::value)
                                , typename boost::fusion::result_of
                                                ::at_c<Bases const,N-1>::type
                                >::type
    lower() const
    {
      return boost::fusion::at_c<N-1>(mBase);
    }

    template<std::size_t N>
    typename boost::disable_if_c< (N<=boost::mpl::size<Bases>::value)
                                , int
                                >::type
    lower() const
    {
      return 1;
    }

    Bases mBase;
  };


  template<class Bases,class Sizes>
  struct block_extent : block_base<Bases>, block_size<Sizes>
  {
    ////////////////////////////////////////////////////////////////////////////
    // Check that Bases adn Sizes have correct size
    ////////////////////////////////////////////////////////////////////////////
    typedef typename
    boost::fusion::result_of::value_at_c<Bases const,0>::type base_index_type;

    typedef typename
    boost::fusion::result_of::value_at_c<Sizes const,0>::type size_index_type;

    BOOST_TYPEOF_NESTED_TYPEDEF_TPL
    (nested
    ,base_index_type() + size_index_type() -1
    )

    typedef typename nested::type difference_type;

   ////////////////////////////////////////////////////////////////////////////
   // Check that Bases adn Sizes have correct size
   ////////////////////////////////////////////////////////////////////////////

   block_extent( Bases const& b, Sizes const& s)
                : block_size<Sizes>(s),block_base<Bases>(b)
    {}

    ////////////////////////////////////////////////////////////////////////////
    // Return the ending index on the Nth dimension
    ////////////////////////////////////////////////////////////////////////////
    template<std::size_t N>
    typename boost::enable_if_c < (N<=boost::mpl::size<Sizes>::value)
                                , difference_type
                                >::type
    upper() const
    {
      return    block_size<Sizes>::template  size<N>()
              + block_base<Bases>::template lower<N>() - 1;
    }

    template<std::size_t N>
    typename boost::disable_if_c< (N<=boost::mpl::size<Sizes>::value)
                                , difference_type
                                >::type
    upper() const
    {
      return 1;
    }
  };

  template<class Type,class StorageKind,class Extend>
  struct  block_data
  {
    typedef
    typename block_data_impl<Type,StorageKind,Extend>::type  data_type;

    block_data()
    {

    }

    ////////////////////////////////////////////////////////////////////////////
    // Buffer on dimension N
    ////////////////////////////////////////////////////////////////////////////
    template<std::size_t N>
    typename boost::fusion::result_of::at_c<data_type const,N-1>::type
    data() const
    {
      return boost::fusion::at_c<N-1>(mData);
    }

    template<std::size_t N>
    typename boost::fusion::result_of::at_c<data_type,N-1>::type
    data()
    {
      return boost::fusion::at_c<N-1>(mData);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Recursively construct data buffers from Bases/Sizes sequence
    //  - non composite 1D case
    ////////////////////////////////////////////////////////////////////////////
    template<class Bases, class Sz,class Padding>
    void init ( boost::mpl::int_<1> const&
              , Bases const& bs   , Sz const& sz
              , Padding const& pdg, boost::mpl::false_ const&
              )
    {
      data<1>().restructure(boost::fusion::at_c<0>(bs),slice<1>(sz,pdg));
    }

    ////////////////////////////////////////////////////////////////////////////
    // Recursively construct data buffers from Bases/Sizes sequence
    //  - composite 1D case require a small helper
    ////////////////////////////////////////////////////////////////////////////
    template<class Base,class Size> struct restruct_
    {
      restruct_(Base const& b,Size const& s) : base(b),size(s) {};
      template<class T>
      inline void operator()(T& t) const { t.restructure(base,size); }
      Base base;
      Size size;
    };

    template<class Bases, class Size,class Padding>
    void init ( boost::mpl::int_<1> const&
              , Bases const& bs   , Size const& sz
              , Padding const& pdg, boost::mpl::true_ const&
              )
    {
      // We compute these types so they are correct in huge memory setup
      restruct_ < typename boost::fusion::result_of::at_c<Bases const,0>::type
                , typename meta::call < tag::slice_ ( Size const&
                                                    , Padding const&
                                                    , boost::mpl::int_<1> const&
                                                    )
                                      >::type
                > callee ( boost::fusion::at_c<0>(bs), slice<1>(sz,pdg) );
       boost::fusion::for_each(data<1>(), callee );
    }

    ////////////////////////////////////////////////////////////////////////////
    // Recursively construct data buffers from Bases/Sizes sequence
    //  - general nD case
    ////////////////////////////////////////////////////////////////////////////
    template<class Index, class Bases, class Size,class Padding, class Composite>
    void init ( Index const&  , Bases const& bs
              , Size const& sz, Padding const& pdg
              , Composite const& c
              )
    {
      data<Index::value>().restructure( boost::fusion::at_c<Index::value-1>(bs)
                                      , slice<Index::value>(sz,pdg)
                                      );
      init( typename boost::mpl::prior<Index>::type(),bs, sz, pdg, c );
    }

    ////////////////////////////////////////////////////////////////////////////
    // Link indexes and data, NRC style and recursively
    //   _        _ _ _ _ _ _ _ _ _ _ _ _
    //  |_|----->|_|_|_|_|_|_|_|_|_|_|_|_|
    //  |_|-------------------^
    //
    ////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////
    // 1D case - do nothing
    ////////////////////////////////////////////////////////////////////////////
    template<class Sz,class Padding,class Composite>
    void link ( boost::mpl::int_<1> const&
              , Sz const&, Padding const&, Composite const&
              )
    {}

    ////////////////////////////////////////////////////////////////////////////
    // 2D case composite - link inside the tuple
    ////////////////////////////////////////////////////////////////////////////
    template<class Sz,class Padding>
    void link ( boost::mpl::int_<2> const&
              , Sz const&, Padding const&, boost::mpl::true_ const&
              )
    {
//      // switch if it is composite or not
    }

    ////////////////////////////////////////////////////////////////////////////
    // General case - loop over sub block
    ////////////////////////////////////////////////////////////////////////////
    template<int N,class Sz, class Padding, class Composite>
    void link ( boost::mpl::int_<N> const&
              , Sz const& sz, Padding const& pdg, Composite const& c
              )
    {
      std::size_t offset = stride<N-1>(sz,pdg);
      std::size_t nbrow  = slice<N>(sz,pdg);

      data<N>().begin()[0]  = data<N-1>().first();
      for(std::size_t i=1;i<nbrow;++i)
        data<N>().begin()[i]  = data<N>().begin()[i-1] + offset;
      link( boost::mpl::int_<N-1>(), sz, pdg, c );
    }

    ////////////////////////////////////////////////////////////////////////////
    // Data holding block buffers sequence
    ////////////////////////////////////////////////////////////////////////////
    data_type mData;
  };
} }

namespace nt2 { namespace container
{
  // CPU Heap based block
  template< class Type
          , class Extend
          , class Bases
          , class Sizes
          , class StorageOrder
          , class Allocator
          , class Padding
          >
  struct  block<Type,Extend,Bases,Sizes,StorageOrder,heap_(Allocator),Padding>
        : details::block_extent<Bases,Sizes>
        , details::block_data<Type,heap_(Allocator),Extend>
  {

    ////////////////////////////////////////////////////////////////////////////
    // block is a RandonAccessSequence
    ////////////////////////////////////////////////////////////////////////////
    typedef Type       value_type;
//    typedef typename buffer_type::pointer          iterator;
//    typedef typename buffer_type::const_pointer    const_iterator;
//    typedef typename allocator_type::reference        reference;
//    typedef typename allocator_type::const_reference  const_reference;
    typedef typename details::block_extent<Bases,Sizes>::size_type        size_type;
    typedef typename details::block_extent<Bases,Sizes>::difference_type  difference_type;
    typedef typename details::block_extent<Bases,Sizes>::difference_type  index_type;

    ////////////////////////////////////////////////////////////////////////////
    // Constructors and stuff
    ////////////////////////////////////////////////////////////////////////////
    block(Bases const& bs, Sizes const& sz, Allocator const& a = Allocator())
          : details::block_extent<Bases,Sizes>(bs,sz)
    {
      init();
      link();
    }

    block& operator=( block const& src )
    {
      details::block_data<Type,heap_(Allocator),Extend>::mData  = src.mData;
      details::block_extent<Bases,Sizes>::mSize                 = src.mSize;
      details::block_extent<Bases,Sizes>::mBase                 = src.mBase;
      link();
      return *this;
    };

    ~block() {}

    protected:
    ////////////////////////////////////////////////////////////////////////////
    // Return the total number of effective elements in a block
    ////////////////////////////////////////////////////////////////////////////
    using details::block_data<Type,heap_(Allocator),Extend>::init;

    void init()
    {
      boost::fusion::nview<Sizes const,StorageOrder>  sz(details::block_extent<Bases,Sizes>::mSize);
      boost::fusion::nview<Bases const,StorageOrder>  bz(details::block_extent<Bases,Sizes>::mBase);
      init( Extend(), bz, sz, Padding()
          , typename meta::is_composite<Type>::type()
          );
    }

    ////////////////////////////////////////////////////////////////////////////
    // Link indexes and data, NRC style and recursively
    ////////////////////////////////////////////////////////////////////////////
    using details::block_data<Type,heap_(Allocator),Extend>::link;
    void link()
    {
      boost::fusion::nview<Sizes const,StorageOrder>  sz(details::block_extent<Bases,Sizes>::mSize);
      link(Extend(), sz, Padding(), typename meta::is_composite<Type>::type());
    }
  };
} }

struct foo {float x; double y; };

NT2_ADAPT_COMPOSITE(foo, (float, x)(double, y));

using nt2::container::block;

int main()
{
  {
    typedef block < float
                  , boost::mpl::int_<1>
                  , boost::mpl::vector_c<int,9>
                  , boost::array<int,1>
                  , boost::mpl::vector_c<int,0>
                  , nt2::heap_(nt2::memory::allocator<float>)
                  , nt2::memory::lead_padding
                  > t_t;

    boost::array<int,1> sz= {{5}};
    boost::mpl::vector_c<int,9> bz;
    t_t  t(bz,sz);

    cout << t.size() << "\n";
    cout  << t.lower<1>()
          << " " << t.upper<1>()
          << " " << t.size<1>()
          << "\n";
  }

  {
    typedef block < float
                  , boost::mpl::int_<2>
                  , boost::mpl::vector_c<int,3,1>
                  , boost::array<int,2>
                  , boost::mpl::vector_c<int,0,1>
                  , nt2::heap_(nt2::memory::allocator<float>)
                  , nt2::memory::lead_padding
                  > t_t;
    boost::array<int,2> sz= {{5,3}};
    boost::mpl::vector_c<int,3,1> bz;
    t_t  t(bz,sz);

    cout << t.size() << "\n";
    cout  << t.lower<1>()
          << " " << t.upper<1>()
          << " " << t.size<1>()
          << "\n";
    cout  << t.lower<2>()
          << " " << t.upper<2>()
          << " " << t.size<2>()
          << "\n";
  }

  {
    typedef block < foo
                  , boost::mpl::int_<1>
                  , boost::mpl::vector_c<int,0>
                  , boost::array<int,1>
                  , boost::mpl::vector_c<int,0>
                  , nt2::heap_(nt2::memory::allocator<foo>)
                  , nt2::memory::lead_padding
                  > t_t;
    boost::array<int,1> sz= {{5}};
    boost::mpl::vector_c<int,0> bz;
    t_t  t(bz,sz);

    cout << t.size() << "\n";
    cout  << t.lower<1>()
          << " " << t.upper<1>()
          << " " << t.size<1>()
          << "\n";
  }
/*
  typedef block < float
                , boost::mpl::int_<4>
                , boost::array<int,4>
                , boost::mpl::vector_c<int,0,1,2,3>
                , nt2::heap_(nt2::memory::allocator<float>)
                , nt2::memory::lead_padding
                > t_t;
  boost::array<int,4> sz= {{2,2,2,2}};
  boost::array<int,4> bz= {{1,2,3,4}};
  t_t  t(bz,sz);

  cout << t.size() << "\n";
*/
  /*
  cout  << t.lower<4>() << " " << t.upper<4>() << " " << t.size<4>() << "\n";
  cout  << t.lower<3>() << " " << t.upper<3>() << " " << t.size<3>() << "\n";
  cout  << t.lower<2>() << " " << t.upper<2>() << " " << t.size<2>() <<  "\n";
  cout  << t.lower<1>() << " " << t.upper<1>() << " " << t.size<1>() << "\n";
  */

}
