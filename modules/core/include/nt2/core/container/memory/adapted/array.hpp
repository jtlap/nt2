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

#include <boost/mpl/size.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <boost/fusion/adapted/array.hpp>
#include <nt2/core/settings/sharing.hpp>
#include <boost/dispatch/meta/model_of.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <nt2/core/container/meta/dereference.hpp>





namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // value_of specialization
  //============================================================================
  // template<typename T, std::size_t N>
  // struct value_of< boost::array<T,N> > : value_of<T>
  // {};


  //============================================================================
  // model_of specialization
  //============================================================================
  // template<typename T, typename A>
  // struct model_of< std::vector<T,A> >
  // {
  //   struct type
  //   {
  //     template<class X> struct apply
  //     {
  //       // This recursive build is required to properly handle vector of vector
  //       // cases and other similar recursive structure
  //       typedef typename  boost::mpl::
  //                         apply<typename model_of<T>::type,X>::type base;
  //       typedef typename A::template rebind<base>::other            alloc;
  //       typedef std::vector<base,alloc>                             type;
  //     };
  //   };
  // };
} } }

//==============================================================================
// Forward declaration
//==============================================================================
//namespace boost { template<class T, std::size_t N> class array; }



// namespace nt2 { namespace memory
// {

//   //============================================================================
//   // boost::array resize - Part of Buffer Concept
//   //============================================================================
//   template< typename T, std::size_t N
//           , typename Sizes, typename Bases, typename Padding
//           >
//   inline void resize( boost::array<T,N>&
//                         , Sizes const&, Bases const&, Padding const&
//                         )
//   {
//     //TODO: embeded std::array in a buffer
//   }


//   //============================================================================
//   // boost::array rebase - Part of Buffer Concept
//   //============================================================================
//   template< typename T, std::size_t N
//           , typename Sizes, typename Bases, typename Padding
//           >
//   inline void rebase( boost::array<T,N>&
//                         , Sizes const&, Bases const&, Padding const&
//                         )
//   {
//     //TODO: embeded std::array in a buffer
//   }


//   //============================================================================
//   // boost::array restructure - Part of Buffer Concept
//   //============================================================================
//   template< typename T, std::size_t N
//           , typename Sizes, typename Bases, typename Padding
//           >
//   inline void restructure( boost::array<T,N>&
//                         , Sizes const&, Bases const&, Padding const&
//                         )
//   {
//     //TODO: embeded std::array in a buffer
//   }

// } }




#endif
