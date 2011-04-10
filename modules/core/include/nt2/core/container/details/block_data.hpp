/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_CORE_CONTAINER_DETAILS_BLOCK_DATA_HPP_INCLUDED
#define NT2_CORE_CONTAINER_DETAILS_BLOCK_DATA_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Hoisted class for base index related block member functions
////////////////////////////////////////////////////////////////////////////////
#include <nt2/sdk/meta/mutable_zip.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <boost/fusion/include/for_each.hpp>
#include <nt2/core/container/details/forward.hpp>
#include <nt2/core/container/details/block_nrc.hpp>
#include <nt2/core/container/details/block_extent.hpp>

namespace nt2 { namespace details
{
  template<class Type,class StorageKind,class Extend>
  struct  block_data
  {
    typedef typename block_nrc<Type,StorageKind,Extend>::type  data_type;

    block_data() {}

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
    // 2D case composite - link inside the tuple with for_each - helper class
    ////////////////////////////////////////////////////////////////////////////
    struct composite_link_init
    {
      template<class T> void operator()(T const& e) const
      {
        boost::fusion::at_c<0>(e) = boost::fusion::at_c<1>(e).first();
      }     
    };

    struct composite_link
    {
      composite_link(std::size_t o) : offset(o) {}
      template<class U> void operator()(U const& e) const
      {
        boost::fusion::at_c<0>(e) = boost::fusion::at_c<1>(e) + offset;
      }     
      std::size_t offset;
    };
    ////////////////////////////////////////////////////////////////////////////
    // 2D case composite - link inside the tuple with for_each
    // Use for_each on a zip_view of both level to put daddy in mummy
    ////////////////////////////////////////////////////////////////////////////
    template<class Sz,class Padding>
    void link ( boost::mpl::int_<2> const&
              , Sz const& sz, Padding const& pdg, boost::mpl::true_ const&
              )
    {
      std::size_t offset = stride<1>(sz,pdg);
      std::size_t nbrow  = slice<2>(sz,pdg);
      
      boost::fusion::for_each ( meta::mutable_zip ( data<2>().begin()[0]
                                                  , data<1>()
                                                  )
                              , composite_link_init()
                              );
                              
      for(std::size_t i=1;i<nbrow;++i)
      { 
        boost::fusion::for_each ( meta::mutable_zip ( data<2>().begin()[i]
                                                    , data<2>().begin()[i-1]
                                                    )
                                , composite_link(offset)
                                );
      }
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

#endif
