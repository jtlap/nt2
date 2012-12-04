//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_META_DEREFERENCE_HPP_INCLUDED
#define NT2_SDK_META_DEREFERENCE_HPP_INCLUDED

#include <boost/mpl/bool.hpp>

////////////////////////////////////////////////////////////////////////////////
// Helper for derefrenceing containers
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace details
{
  template<typename Container, std::size_t Level>
  struct dereference_container
  {
    typedef typename Container::value_type  base;
    typedef typename dereference_container<base,Level-1>::type type;
  };

  template<typename Container, std::size_t Level>
  struct dereference_container<Container&,Level>
  {
    typedef typename Container::reference  base;
    typedef typename dereference_container<base,Level-1>::type type;
  };

  template<typename Container, std::size_t Level>
  struct dereference_container<Container const&,Level>
  {
    typedef typename Container::const_reference  base;
    typedef typename dereference_container<base,Level-1>::type type;
  };

  template<typename Container>
  struct dereference_container<Container&,0UL> { typedef Container& type; };

  template<typename Container>
  struct dereference_container<Container const&,0UL> { typedef Container const& type; };

  template<typename Container>
  struct dereference_container<Container,0UL> { typedef Container type; };
} }

////////////////////////////////////////////////////////////////////////////////
// For a given type, return a reference or const reference type that can be
// returned after Level dereferencing
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  template<typename Buffer, std::size_t Level>
  struct  dereference_
        : details::dereference_container<Buffer,Level>
  {};
} }

#endif
