/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_LINEAR_BLOCK_HPP_INCLUDED
#define NT2_SDK_MEMORY_LINEAR_BLOCK_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Linear allocation memory block
////////////////////////////////////////////////////////////////////////////////
#include <boost/typeof/typeof.hpp>
#include <nt2/sdk/memory/slice.hpp>
#include <nt2/sdk/memory/stride.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <boost/fusion/include/at.hpp>

namespace nt2 { namespace memory
{
  template< int Dims
          , class Type
          , class Bases, class Sizes
          , class Padding
          , class Allocator
          >
  class linear_block
  {
    public:

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
    // Type related to internal buffer
    // A linear_block holds a single [0,slice<1>(size)[ buffer
    ////////////////////////////////////////////////////////////////////////////
    struct size_helper
    {
      static Sizes& s; static Padding& p;
      BOOST_TYPEOF_NESTED_TYPEDEF_TPL(nested , ( slice<1>(s,p) ));
      typedef typename nested::type type;
    };

    typedef typename size_helper::type                  size_value_type;
    typedef boost::mpl::int_<0>                         base_value_type;
    typedef buffer< value_type      , base_value_type
                  , size_value_type , allocator_type  > data_type;

    ////////////////////////////////////////////////////////////////////////////
    // Constructors
    ////////////////////////////////////////////////////////////////////////////
    linear_block() : data_(), bases_(), sizes_(), padding_() {}

    linear_block( Bases const& b, Sizes const& s, Padding const& p )
                : data_(base_value_type(),slice<1>(s,p))
                , bases_(b), sizes_(s), padding_(p)
    {}

    linear_block( linear_block const& src )
                : data_(src.data_)
                , bases_(src.bases_), sizes_(src.sizes_)
                , padding_(src.padding_)
    {}

    template<class T2,class B2,class P2,class A2>
    linear_block( linear_block<Dims,T2,B2,Sizes,P2,A2> const& src )
    {
      sizes_ = src.sizes_;
      // same   padding == simple copy
      // diff.  padding == copy by access via (2D)
    }

    ////////////////////////////////////////////////////////////////////////////
    // Assignment
    ////////////////////////////////////////////////////////////////////////////
    linear_block& operator=( linear_block const& src )
    {
      if(this != &src)
      {
        data_     = src.data_;
        bases_    = src.bases_;
        sizes_    = src.sizes_;
        padding_  = src.padding_;
      }
      return *this;
    }

    template<class T2,class B2,class S2,class P2,class A2>
    linear_block& operator=( linear_block<Dims,T2,B2,S2,P2,A2> const& src )
    {

      return *this;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Swap
    ////////////////////////////////////////////////////////////////////////////
    void swap( linear_block& src )
    {
      boost::swap(data_   , src.data_   );
      boost::swap(bases_  , src.bases_  );
      boost::swap(sizes_  , src.sizes_  );
      boost::swap(padding_, src.padding_);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Element access
    ////////////////////////////////////////////////////////////////////////////
    template<class Position>
    const_reference operator()(Position const& p ) const
    {
      return data_[ linearize(p) ];
    }

    template<class Position>
    reference operator()(Position const& p )
    {
      return data_[ linearize(p) ];
    }

    ////////////////////////////////////////////////////////////////////////////
    // Size manipulation
    ////////////////////////////////////////////////////////////////////////////
    void rebase( Bases const& b ) { data_.rebase(b); }
    void resize( Sizes const& s ) { data_.resize(s); }
    void restructure( Bases const& b, Sizes const& s )
    {
      data_.restructure(b,s);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Size informations
    ////////////////////////////////////////////////////////////////////////////
    template<std::size_t N>
    typename boost::enable_if_c< (N>=1) && (N<=Dims), size_type>::type
    size() const
    {
      return boost::fusion::at_c<N-1>(sizes_);
    }

    template<std::size_t N>
    typename boost::disable_if_c< (N>=1) && (N<=Dims), size_type>::type
    size() const
    {
      return 1;
    }

    template<std::size_t N>
    typename boost::enable_if_c< (N>=1) && (N<=Dims), difference_type>::type
    lower() const
    {
      return boost::fusion::at_c<N-1>(bases_);
    }

    template<std::size_t N>
    typename boost::disable_if_c< (N>=1) && (N<=Dims), difference_type>::type
    lower() const
    {
      return 1;
    }

    template<std::size_t N> difference_type upper() const
    {
      return size<N>() + lower<N>() - 1;
    }

    //protected:

    template<class Position>
    difference_type linearize(Position const p) const
    {
      return  boost::fusion::at_c<0>(p) - boost::fusion::at_c<0>(bases_)
            + linearize ( p , boost::mpl::long_<1>()
                            , typename  boost::fusion
                                      ::result_of::size<Position>::type()
                        );
    }

    template<class Position, class N, class S>
    typename boost::enable_if_c<(N::value != S::value),difference_type>::type
    linearize(Position const p, N const&, S const& s) const
    {
      difference_type i = boost::fusion::at<N>(p) - boost::fusion::at<N>(bases_);
      return  boost::fusion::at_c<N::value-1>(sizes_)
            * ( i + linearize(p,typename boost::mpl::next<N>::type(),s) );
    }

    template<class Position, class N, class S>
    typename boost::enable_if_c<(N::value == S::value),difference_type>::type
    linearize(Position const p, N const&, S const&  ) const
    {
      return 0;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Data members : sizes,bases, buffer and padder
    ////////////////////////////////////////////////////////////////////////////
    private:
    data_type   data_;
    Bases       bases_;
    Sizes       sizes_;
    Padding     padding_;
  };

  //////////////////////////////////////////////////////////////////////////////
  // ADL swap
  //////////////////////////////////////////////////////////////////////////////
  template< int Dims, class Type, class Bases, class Sizes
          , class Padding, class Allocator
          >
  void swap ( linear_block<Dims,Type,Bases,Sizes,Padding,Allocator>& a
            , linear_block<Dims,Type,Bases,Sizes,Padding,Allocator>& b
            )
  {
    a.swap(b);
  }

} }

#endif
