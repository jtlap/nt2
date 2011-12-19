//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_DETAILS_ILIFFE_BUFFER_2D_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_DETAILS_ILIFFE_BUFFER_2D_HPP_INCLUDED

//==============================================================================
// 2D iliffe_buffer specialization
//==============================================================================
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/fold.hpp>
#include <nt2/include/functions/multiplies.hpp>

namespace nt2 { namespace memory
{
  template<typename Data, typename Index>
  struct iliffe_buffer<boost::mpl::size_t<2>,Data,Index>
  {
    typedef typename Data::allocator_type               allocator_type;
    typedef typename Data::value_type                   value_type;
    typedef typename Data::iterator                     iterator;
    typedef typename Data::const_iterator               const_iterator;
    typedef typename Data::reference                    reference;
    typedef typename Data::const_reference              const_reference;
    typedef typename Data::size_type                    size_type;
    typedef typename Data::difference_type              difference_type;

    iliffe_buffer ( allocator_type const& a = allocator_type() ) : data_(a) {}

    template<typename Sizes, typename Bases>
    iliffe_buffer( Sizes const& sz, Bases const& bs )
      : data_ ( data_size(sz) , boost::fusion::at_c<0>(bs) )
      , index_( index_size(sz), boost::fusion::at_c<1>(bs) )
      , inner_( boost::fusion::at_c<0>(sz) )
    {
      make_links();
    }

    template<typename Sizes, typename Bases>
    iliffe_buffer ( Sizes const& sz
                  , Bases const& bs
                  , allocator_type const& a
                  )
      : data_ ( data_size(sz) , boost::fusion::at_c<0>(bs), a )
      , index_( index_size(sz), boost::fusion::at_c<1>(bs) )
      , inner_( boost::fusion::at_c<0>(sz) )
    {
      make_links();
    }

    iterator        begin()       { return data_.begin(); }
    const_iterator  begin() const { return data_.begin(); }
    iterator        end()         { return data_.end(); }
    const_iterator  end() const   { return data_.end(); }

    template<typename Sizes> inline void resize( Sizes const& szs )
    {
      data_.resize(data_size(szs));
      index_.resize(index_size(szs));
      inner_ = boost::fusion::at_c<0>(szs);
      make_links();
    }

    template<typename Bases> inline void rebase( Bases const& bss )
    {
      data_.rebase(boost::fusion::at_c<0>(bss));
      index_.rebase(boost::fusion::at_c<1>(bss));
      make_links();
    }

    template<typename Sizes, typename Bases> inline void
    restructure( Sizes const& szs, Bases const& bss )
    {
      data_.resize(data_size(szs));
      data_.rebase(boost::fusion::at_c<0>(bss));

      index_.resize(index_size(szs));
      index_.rebase(boost::fusion::at_c<1>(bss));

      inner_ = boost::fusion::at_c<0>(szs);

      make_links();
    }

    template<class Position> BOOST_FORCEINLINE
    reference operator[]( Position const& pos )
    {
      return access ( meta::as_sequence(pos)
                    , boost::fusion::size(meta::as_sequence(pos))
                    );
    }

    template<class Position> BOOST_FORCEINLINE
    const_reference operator[]( Position const& pos ) const
    {
      return access ( meta::as_sequence(pos)
                    , boost::fusion::size(meta::as_sequence(pos))
                    );
    }

    protected:
    template<class Seq> inline std::size_t
    data_size(Seq const& s) const
    {
      return boost::fusion::fold( s
                                , boost::mpl::size_t<1>()
                                , boost::dispatch::functor<tag::multiplies_>()
                                );
    }

    template<class Seq> inline std::size_t
    index_size(Seq const& s) const
    {
      return boost::fusion::fold( boost::fusion::pop_front(s)
                                , boost::mpl::size_t<1>()
                                , boost::dispatch::functor<tag::multiplies_>()
                                );
    }

    template<class Position> BOOST_FORCEINLINE
    reference access(Position const& p, boost::mpl::int_<1> const& )
    {
      return data_[boost::fusion::at_c<0>(p)];
    }

    template<class Position> BOOST_FORCEINLINE
    const_reference access(Position const& p, boost::mpl::int_<1> const& ) const
    {
      return data_[boost::fusion::at_c<0>(p)];
    }

    template<class Position> BOOST_FORCEINLINE
    reference access(Position const& p, boost::mpl::int_<2> const& )
    {
      return index_[boost::fusion::at_c<1>(p)][boost::fusion::at_c<0>(p)];
    }

    template<class Position> BOOST_FORCEINLINE
    const_reference access(Position const& p, boost::mpl::int_<2> const& ) const
    {
      return index_[boost::fusion::at_c<1>(p)][boost::fusion::at_c<0>(p)];
    }

    void make_links()
    {
      typename Index::difference_type i = index_.lower();
      typename Index::difference_type u = index_.upper();

      index_[i++] = data_.origin();
      for(; i <= u; ++i) index_[i] = index_[i-1] + inner_;
    }

    private:
    Data        data_;
    Index       index_;
    std::size_t inner_;
  };
} }

#endif
