//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_MEMORY_DETAILS_COMPOSITE_TRAITS_HPP_INCLUDED
#define NT2_CORE_CONTAINER_MEMORY_DETAILS_COMPOSITE_TRAITS_HPP_INCLUDED

//==============================================================================
// Helper metafunctions for building composite_buffer types
//==============================================================================
namespace nt2 { namespace details
{
  struct composite_ref
  {
    template<class T> struct apply { typedef typename T::reference type; };
  };

  struct composite_cref
  {
    template<class T> struct apply { typedef typename T::const_reference type; };
  };

  struct composite_iterator
  {
    template<class T> struct apply { typedef typename T::iterator type; };
  };

  struct composite_citerator
  {
    template<class T> struct apply { typedef typename T::const_iterator type; };
  };

  struct composite_riterator
  {
    template<class T> struct apply
    {
      typedef typename T::reverse_iterator type;
    };
  };

  struct composite_criterator
  {
    template<class T> struct apply
    {
      typedef typename T::const_reverse_iterator type;
    };
  };
} }

#endif
