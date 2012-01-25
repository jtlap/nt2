//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_DISPATCH_META_COMBINE_HPP_INCLUDED
#define BOOST_DISPATCH_META_COMBINE_HPP_INCLUDED

namespace boost { namespace dispatch
{
  // TODO: simplify
  namespace details
  {
    template<class T, class U, int N, bool B>
    struct combine_impl;
        
    template<template<class> class Outer, class T, class U, int N>
    struct combine_impl<Outer<T>, U, N, true>
    {
      typedef Outer<typename combine_impl<T, U, N-1, true>::type> type;
    };
    
    template<template<class> class Outer, class T, class U, int N>
    struct combine_impl<Outer<T>, U, N, false>
    {
      typedef U type;
    };
    
    template<template<class> class New, class T, class U, int N>
    struct combine_impl<T, New<U>, N, true>
    {
      typedef New<T> type;
    };
    
    template<template<class> class New, class T, class U, int N>
    struct combine_impl<T, New<U>, N, false>
    {
      typedef New<typename combine_impl<T, U, N+1, false>::type> type;
    };
    
    template<template<class> class Outer, template<class> class New, class T, class U, int N>
    struct combine_impl<Outer<T>, New<U>, N, true>
    {
      typedef Outer<typename combine_impl<T, New<U>, N-1, true>::type> type;
    };
    
    template<template<class> class Outer, template<class> class New, class T, class U, int N>
    struct combine_impl<Outer<T>, New<U>, N, false>
    {
      typedef New<typename combine_impl<Outer<T>, U, N+1, false>::type> type;
    };
    
    template<template<class> class Outer, class T, template<class> class New, class U>
    struct combine_impl<Outer<T>, New<U>, 0, true>
    {
      typedef New<T> type;
    };
    
    template<template<class> class Outer, class T, template<class> class New, class U>
    struct combine_impl<Outer<T>, New<U>, 0, false>
    {
      typedef Outer<T> type;
    };
    
    template<template<class> class Outer, class T, class U>
    struct combine_impl<Outer<T>, U, 0, true>
    {
      typedef U type;
    };
    
    template<template<class> class Outer, class T, class U>
    struct combine_impl<Outer<T>, U, 0, false>
    {
      typedef T type;
    };
    
    template<class T, template<class> class New, class U>
    struct combine_impl<T, New<U>, 0, true>
    {
      typedef New<T> type;
    };
    
    template<class T, template<class> class New, class U>
    struct combine_impl<T, New<U>, 0, false>
    {
      typedef T type;
    };
    
    template<class T, class U>
    struct combine_impl<T, U, 0, true>
    {
      typedef U type;
    };
    
    template<class T, class U>
    struct combine_impl<T, U, 0, false>
    {
      typedef T type;
    };
    
    template<class T>
    struct outer_count
    {
      static const int value = 0;
    };
    
    template<template<class> class T, class U>
    struct outer_count< T<U> >
    {
      static const int value = 1 + outer_count<U>::value;
    };
  }
  
  namespace meta
  {
    /** \brief Combines two nested template types by inserting the top-most node of \c U at the same height in \c T */
    template<class T, class U, int N = details::outer_count<U>::value>
    struct combine
     : details::combine_impl<T, U, details::outer_count<T>::value - N, !(details::outer_count<T>::value < N)>
    {
    };
  }
  
} }

#endif
