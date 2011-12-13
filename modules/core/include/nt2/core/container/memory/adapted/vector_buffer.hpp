//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_ADAPTED_VECTOR_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_ADAPTED_VECTOR_HPP_INCLUDED

#include <vector>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/size.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <nt2/core/container/meta/dimensions_of.hpp>
#include <nt2/core/container/meta/as_buffer.hpp>
#include <nt2/core/container/meta/dereference.hpp>


namespace nt2 {  namespace memory
{

  //============================================================================
  // Forward declaration
  //============================================================================
  template<typename Type, typename Allocator>
  struct vector_buffer;

  //============================================================================
  // vector_buffer are dereferencable
  //============================================================================

  template<typename T, typename A, typename Position>
  typename vector_buffer<T,A>::reference
  dereference( vector_buffer<T,A>& b, Position const& pos )
  {
    BOOST_MPL_ASSERT_MSG( (boost::mpl::size<Position>::value == 1)
                    , POSITION_SIZE_MISMATCH_IN_VECTOR_BUFFER_ACCESS
                    , (Position)
                    );
    return b[boost::fusion::at_c<0>(pos)];
  }
  
  template<typename T, typename A, typename Position>
  typename vector_buffer<T,A>::const_reference
  dereference( vector_buffer<T,A> const& b, Position const& pos )
  {
    BOOST_MPL_ASSERT_MSG( (boost::mpl::size<Position>::value == 1)
                    , POSITION_SIZE_MISMATCH_IN_VECTOR_BUFFER_ACCESS
                    , (Position)
                    );
    return b[boost::fusion::at_c<0>(pos)];
  }

  //============================================================================
  // vector_buffer resize - Part of Buffer Concept
  //============================================================================

  template<   typename Type, typename Allocator
            , typename Sizes
            >
  inline void resize( vector_buffer<Type, Allocator >& b
                      , Sizes const& s
                      )
  {
    b.resize(s);
  }

  //============================================================================
  // vector_buffer rebase - Part of Buffer Concept
  //============================================================================

  template<   typename Type, typename Allocator
            , typename Bases
            >
  inline void rebase( vector_buffer<Type, Allocator >& b 
                      , Bases const& bs
                      )
  {
    b.rebase(bs);
  }


  //============================================================================
  // vector_buffer restructure - Part of Buffer Concept
  //============================================================================

  template<   typename Type, typename Allocator
            , typename Sizes, typename Bases
            >
  inline void restructure( vector_buffer<Type, Allocator>& b
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
  template< class Type, class Alloc >
  struct  dimensions_of< memory::vector_buffer<Type,Alloc> >
        : boost::mpl::size_t<1>
  {};

  //============================================================================
  // as_buffer specialization
  //============================================================================

  template< typename Type , typename Alloc>
  struct  as_buffer <std::vector<Type, Alloc> >
  {
    typedef nt2::memory::vector_buffer<Type,Alloc> result_type;

    template <typename Sizes, typename Bases>
    result_type
    operator()(std::vector<Type,Alloc> d, Sizes const& s, Bases const& b)
    {
      return nt2::memory::vector_buffer<Type,Alloc>(d,s,b);
    }

  };



} }


namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // value_of specialization
  //============================================================================
  template<typename T, typename A>
  struct value_of< nt2::memory::vector_buffer<T,A > > : value_of<T>
  {};

  //============================================================================
  // model_of specialization
  //============================================================================

  template<  class Type, class Allocator >
  struct model_of< nt2::memory::vector_buffer<Type, Allocator> >
  {
    struct type
    {
      template<class X> struct apply
      {
        // This recursive build is required to properly handle vector of vector
        // cases and other similar recursive structure
        typedef typename  boost::mpl::
                          apply<typename model_of<Type>::type,X>::type base;
        typedef typename Allocator::template rebind<base>::other       alloc;
        typedef nt2::memory::vector_buffer<base,alloc >  type;
      };
    };
  };


} } }



#endif
