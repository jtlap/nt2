#include <iostream>
#include <boost/array.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <boost/fusion/include/sequence_facade.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <nt2/sdk/memory/linear_block.hpp>
#include <nt2/sdk/memory/allocator.hpp>
#include <nt2/sdk/memory/no_padding.hpp>
#include <nt2/sdk/memory/global_padding.hpp>

using namespace std;

struct fixed_base_tag {};


template<typename Seq, int N>
struct  fixed_iterator
      : boost::fusion::iterator_facade<fixed_iterator<Seq, N>, boost::fusion::random_access_traversal_tag>
{
    typedef boost::mpl::int_<N> index;
    typedef Seq                 sequence_type;

    fixed_iterator(Seq& seq): seq_(seq) {}
    Seq& seq_;

    template<class T> struct value_of
    {
      typedef typename T::value_type type;
    };

    template<class T> struct deref
    {
      typedef typename Seq::value_type type;
      static type call(T const& ) { return type(); }
    };

    template<class It> struct next
    {
      typedef fixed_iterator< typename It::sequence_type
                            , It::index::value + 1
                            > type;

      static type call(It const& it) { return type(it.seq_); }
    };

    template<typename It> struct prior
    {
      typedef fixed_iterator< typename It::sequence_type
                            , It::index::value - 1
                            > type;

      static type call(It const& it) { return type(it.seq_); }
    };

/*
    template<typename It1, typename It2>
    struct distance
    {
        typedef typename mpl::minus<typename It2::index, typename It1::index>::type type;

        static type call(It1 const& it1, It2 const& it2)
        {
            return type();
        }
    };
*/
    template<class It,class M>
    struct advance
    {
      typedef fixed_iterator< typename It::sequence_type
                            , It::index::value + M::value
                            > type;

      static type call(It const& it) { return type(it.seq_); }
    };


};

template<int Size, int Value>
struct fixed_base : boost::fusion::sequence_facade<fixed_base<Size,Value>, boost::fusion::random_access_traversal_tag>
{
  typedef boost::mpl::int_<Value> value_type;

  template<class Sq> struct begin
  {
    typedef fixed_iterator<Sq, 0> type;
    static type call(Sq& sq) { return type(sq); }
  };

  template<class Sq> struct end
  {
    typedef fixed_iterator<Sq, Size> type;
    static type call(Sq& sq) { return type(sq); }
  };

  template<class S>           struct size     : boost::mpl::int_<Size>  {};
  template<class S, class N>  struct value_at : value_type {};

  template<typename Sq, typename N>
  struct at
  {
    typedef value_type type;
    static type call(Sq&) { return type(); }
  };
};

int main()
{
  {
    typedef nt2::memory::linear_block<3, float
                                       , fixed_base<3,1>
                                       , boost::mpl::vector_c<int,2,3,2>
                                       , boost::mpl::vector_c<int,1,0,2>
                                       , nt2::memory::global_padding
                                       , nt2::memory::allocator<float>
                                        > t;

    typedef nt2::memory::linear_block<3, float
                                       , boost::array<int,3>
                                       , boost::mpl::vector_c<int,2,3,2>
                                       , boost::mpl::vector_c<int,0,1,2>
                                       , nt2::memory::global_padding
                                       , nt2::memory::allocator<float>
                                       > st;
    boost::array<int,3> b = {{1,1,1}};

    fixed_base<3,1> fb;
    boost::mpl::vector_c<int,2,3,2> ss;

    t  u(fb,ss,nt2::memory::global_padding());
    st v(b,ss,nt2::memory::global_padding());

    int l(0),n(0);
    for(int k=u.lower<3>();k<=u.upper<3>();++k)
    for(int i=u.lower<2>();i<=u.upper<2>();++i)
     for(int j=u.lower<1>();j<=u.upper<1>();++j)
    {
      boost::array<int,3> p = {{j,i,k}};
      u(p) = n++;
      v(p) = l++;
    }

    for(int i=0;i<12;++i)
    {
      cout << "RAW u["<< i << "] = " << u.data_[i] << " -- v[" << i << "] = " << v.data_[i] << "\n";
    }
    for(int k=u.lower<3>();k<=u.upper<3>();++k)
    for(int i=u.lower<2>();i<=u.upper<2>();++i)
     for(int j=u.lower<1>();j<=u.upper<1>();++j)
    {
      boost::array<int,3> p = {{j,i,k}};
      cout << "u("<< j << "," << i << "," << k << ")" << " = " << u(p) << "\n";
      cout << "v("<< j << "," << i << "," << k << ")" << " = " << v(p) << "\n";
    }
  }
}
