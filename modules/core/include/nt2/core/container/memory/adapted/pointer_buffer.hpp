//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_ADAPTED_POINTER_BUFFER_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_ADAPTED_POINTER_BUFFER_HPP_INCLUDED

#include <boost/mpl/apply.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/size.hpp>
#include <boost/fusion/include/at_c.hpp>
#include <nt2/sdk/meta/remove_pointers.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <nt2/core/container/meta/dereference.hpp>
#include <nt2/core/container/meta/dimensions_of.hpp>
#include <nt2/core/container/meta/as_buffer.hpp>
#include <boost/simd/sdk/memory/details/category.hpp>


namespace nt2 { namespace memory
{
  //============================================================================
  // Forward declaration
  //============================================================================
  template <class Type>
  struct pointer_buffer;


  //============================================================================
  // pointer_buffer are dereferencable
  //============================================================================

  template<typename T, typename Position>
  typename pointer_buffer<T>::reference
  dereference( pointer_buffer<T>& b, Position const& pos )
  {
    BOOST_MPL_ASSERT_MSG( (boost::mpl::size<Position>::value == 1)
                    , POSITION_SIZE_MISMATCH_IN_POINTER_BUFFER_ACCESS
                    , (Position)
                    );
    return b[boost::fusion::at_c<0>(pos)];
  }
  
  template<typename T, typename Position>
  typename pointer_buffer<T>::const_reference
  dereference( pointer_buffer<T> const& b, Position const& pos )
  {
    BOOST_MPL_ASSERT_MSG( (boost::mpl::size<Position>::value == 1)
                    , POSITION_SIZE_MISMATCH_IN_POINTER_BUFFER_ACCESS
                    , (Position)
                    );
    return b[boost::fusion::at_c<0>(pos)];
  }

  //============================================================================
  // pointer_buffer resize - Part of Buffer Concept
  //============================================================================

  template< typename Type
            , typename Sizes, typename Bases
            >
  inline void resize( pointer_buffer<Type>& b
                      , Sizes const& s
                      )
  {
    b.resize(s);
  }

  //============================================================================
  // pointer_buffer rebase - Part of Buffer Concept
  //============================================================================

  template< typename Type
            , typename Sizes, typename Bases
            >
  inline void rebase( pointer_buffer<Type>& b 
                      , Bases const& bs
                      )
  {
    b.rebase(bs);
  }

  //============================================================================
  // pointer_buffer restructure - Part of Buffer Concept
  //============================================================================

  template< typename Type
            , typename Sizes, typename Bases
            >
  inline void restructure( pointer_buffer<Type>& b
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
  template< class Type>
  struct  dimensions_of< memory::pointer_buffer<Type> >
        : boost::mpl::size_t<1>
  {};


  //============================================================================
  // as_buffer specialization
  //============================================================================

  template< typename Type >
  struct  as_buffer <Type*>
  {
    typedef nt2::memory::pointer_buffer<Type> result_type;

    template <typename Sizes, typename Bases>
    result_type
    operator()(Type* d, Sizes const& s, Bases const& b)
    {
      return nt2::memory::pointer_buffer<Type>(d,s,b);
    }

  };


} }


namespace boost { namespace dispatch { namespace meta
{

  //============================================================================
  // value_of specialization
  //============================================================================

  template<typename T>
  struct value_of< nt2::memory::pointer_buffer<T> > : value_of<T>
  {};


  //============================================================================
  // model_of specialization
  //============================================================================
  template<typename T>
  struct model_of< nt2::memory::pointer_buffer<T> >
  {
    struct type
    {
      template<class X> struct apply
      {
        typedef typename  boost::mpl::
                          apply<typename model_of<T>::type,X>::type base;
        typedef nt2::memory::pointer_buffer<base>  type;
      };
    };
  };


} } }


#endif
