#include <iostream>
#include <nt2/sdk/details/type_id.hpp>
#include <nt2/sdk/memory/lead_padding.hpp>

#include <boost/fusion/include/nview.hpp>
#include <nt2/core/container/details/block_data.hpp>

using namespace std;

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
    typedef details::block_extent<Bases,Sizes>                extent_parent;
    typedef details::block_data<Type,heap_(Allocator),Extend> data_parent;

    ////////////////////////////////////////////////////////////////////////////
    // block is a RandonAccessSequence
    ////////////////////////////////////////////////////////////////////////////
    typedef Type       value_type;
//    typedef typename buffer_type::pointer          iterator;
//    typedef typename buffer_type::const_pointer    const_iterator;
//    typedef typename allocator_type::reference        reference;
//    typedef typename allocator_type::const_reference  const_reference;
    typedef typename extent_parent::size_type        size_type;
    typedef typename extent_parent::difference_type  difference_type;
    typedef typename extent_parent::difference_type  index_type;

    ////////////////////////////////////////////////////////////////////////////
    // Constructors and stuff
    ////////////////////////////////////////////////////////////////////////////
    block(Bases const& bs, Sizes const& sz, Allocator const& a = Allocator())
          : extent_parent(bs,sz)
    {
      init();
      link();
    }

    protected:
    ////////////////////////////////////////////////////////////////////////////
    // Initialize a NRC block
    ////////////////////////////////////////////////////////////////////////////
    using data_parent::init;

    void init()
    {
      boost::fusion::nview<Sizes const,StorageOrder>  sz(extent_parent::mSize);
      boost::fusion::nview<Bases const,StorageOrder>  bz(extent_parent::mBase);
      init( Extend(), bz, sz, Padding()
          , typename meta::is_composite<Type>::type()
          );
    }

    ////////////////////////////////////////////////////////////////////////////
    // Link indexes and data, NRC style and recursively
    ////////////////////////////////////////////////////////////////////////////
    using data_parent::link;
    void link()
    {
      boost::fusion::nview<Sizes const,StorageOrder>  sz(extent_parent::mSize);
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

  {
    typedef block < foo
                   , boost::mpl::int_<2>
                   , boost::mpl::vector_c<int,0,0>
                   , boost::array<int,2>
                   , boost::mpl::vector_c<int,0,1>
                   , nt2::heap_(nt2::memory::allocator<foo>)
                   , nt2::memory::lead_padding
                   > t_t;
     boost::array<int,2> sz= {{5,7}};
     boost::mpl::vector_c<int,0,0> bz;
     t_t  t(bz,sz);

     cout << t.size() << "\n";
     cout  << t.lower<1>()
           << " " << t.upper<1>()
           << " " << t.size<1>()
           << "\n";
  }
}
