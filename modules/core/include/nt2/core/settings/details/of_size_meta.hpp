//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_SETTINGS_DETAILS_OF_SIZE_META_HPP_INCLUDED
#define NT2_CORE_SETTINGS_DETAILS_OF_SIZE_META_HPP_INCLUDED

#include <cstddef>
#include <boost/dispatch/meta/fusion.hpp>
#include <nt2/core/container/category.hpp>
#include <boost/dispatch/meta/value_of.hpp>
#include <nt2/core/container/meta/is_container.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  // value_of a of_size_ is simply ptrdiff_t
  //============================================================================
  template< BOOST_PP_ENUM_PARAMS( NT2_MAX_DIMENSIONS, std::ptrdiff_t D) >
  struct value_of< nt2::of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D)> >
  {
    typedef std::size_t type;
  };
} } }

namespace nt2 { namespace container
{
  //============================================================================
  // of_size_ is a container
  //============================================================================
  template< BOOST_PP_ENUM_PARAMS( NT2_MAX_DIMENSIONS, std::ptrdiff_t D) >
  struct is_container< nt2::of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D)> >
    : boost::mpl::true_
  {};
} }

namespace boost { namespace dispatch { namespace meta
{
  //============================================================================
  /*!
   * extent_ is the hierarchy type used by of_size_ container
   */
  //============================================================================
  template<class Type, class Size> 
  struct extent_ : table_< typename property_of<Type>::type, Size>
  {
    typedef table_<typename property_of<Type>::type, Size> parent;
  };

  //============================================================================
  // hierarchy of a of_size container is :
  //   container_< extent_<Origin, of_size_<1,N> > >
  //============================================================================
  template< BOOST_PP_ENUM_PARAMS( NT2_MAX_DIMENSIONS, std::ptrdiff_t D)
          , typename Origin
          >
  struct hierarchy_of < nt2::of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D)>
                      , Origin
                      >
  {
    typedef nt2::of_size_<BOOST_PP_ENUM_PARAMS(NT2_MAX_DIMENSIONS, D)> base;
    static const std::size_t size = base::static_size ? base::static_size : 1;
    typedef extent_< Origin, nt2::of_size_<1, size> > type;
  };
} } }

#endif
