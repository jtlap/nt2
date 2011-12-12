//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_ADAPTED_ARRAY_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_ADAPTED_ARRAY_HPP_INCLUDED

#include <vector>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/size.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <nt2/core/container/meta/dimensions_of.hpp>
#include <nt2/core/container/meta/dereference.hpp>


namespace nt2 {  namespace memory
{

  //============================================================================
  // Forward declaration
  //============================================================================
  template<typename Type, std::size_t N>
  struct array_buffer;

  //============================================================================
  // array_buffer are dereferencable
  //============================================================================

  template<typename T, std::size_t N, typename Position>
  typename array_buffer<T,N>::reference
  dereference( array_buffer<T,N>& b, Position const& pos )
  {
    BOOST_MPL_ASSERT_MSG( (boost::mpl::size<Position>::value == 1)
                    , POSITION_SIZE_MISMATCH_IN_ARRAY_BUFFER_ACCESS
                    , (Position)
                    );
    return b[boost::fusion::at_c<0>(pos)];
  }
  
  template<typename T, std::size_t N, typename Position>
  typename array_buffer<T,N>::const_reference
  dereference( array_buffer<T,N> const& b, Position const& pos )
  {
    BOOST_MPL_ASSERT_MSG( (boost::mpl::size<Position>::value == 1)
                    , POSITION_SIZE_MISMATCH_IN_ARRAY_BUFFER_ACCESS
                    , (Position)
                    );
    return b[boost::fusion::at_c<0>(pos)];
  }

  //============================================================================
  // array_buffer resize - Part of Buffer Concept
  //============================================================================

  template<   typename Type, std::size_t N
            , typename Sizes
            >
  inline void resize( array_buffer<Type, N >& b
                      , Sizes const& s
                      )
  {
    b.resize(s);
  }

  //============================================================================
  // array_buffer rebase - Part of Buffer Concept
  //============================================================================

  template<   typename Type, std::size_t N
            , typename Bases
            >
  inline void rebase( array_buffer<Type, N >& b 
                      , Bases const& bs
                      )
  {
    b.rebase(bs);
  }


  //============================================================================
  // array_buffer restructure - Part of Buffer Concept
  //============================================================================

  template<   typename Type, std::size_t N
            , typename Sizes, typename Bases
            >
  inline void restructure( array_buffer<Type, N>& b
                           , Sizes const& sz, Bases const& bs
                           )
  {
    b.restructure(sz,bs);
  }




} } 


namespace nt2 { namespace meta
{
  //============================================================================
  // dimensions_of specialization
  //============================================================================
  template< class Type, std::size_t N>
  struct  dimensions_of< memory::array_buffer<Type,N> >
        : boost::mpl::size_t<1>
  {};


} }


namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // value_of specialization
  //============================================================================
  template<typename T, std::size_t N>
  struct value_of< nt2::memory::array_buffer<T,N > > : value_of<T>
  {};

  //============================================================================
  // model_of specialization
  //============================================================================

  template<  class Type, std::size_t N >
  struct model_of< nt2::memory::array_buffer<Type, N> >
  {
    struct type
    {
      template<class X> struct apply
      {
        // This recursive build is required to properly handle vector of vector
        // cases and other similar recursive structure
        typedef typename  boost::mpl::
                          apply<typename model_of<Type>::type,X>::type base;
        typedef nt2::memory::array_buffer<base,N >  type;
      };
    };
  };


} } }



#endif
