/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_DISPATCH_CONCEPT_CATEGORY_HPP_INCLUDED
#define BOOST_DISPATCH_CONCEPT_CATEGORY_HPP_INCLUDED

#include <boost/dispatch/meta/unknown.hpp>
#include <boost/dispatch/error/concepts.hpp>

////////////////////////////////////////////////////////////////////////////////
// Categorizy concept: defines types usbale as Boost.Dispatch category tag
// Documentation: http://nt2.lri.fr/sdk/concept/category.html
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch
{
  //////////////////////////////////////////////////////////////////////////////
  // Category concept
  //////////////////////////////////////////////////////////////////////////////
  template< class T > struct Category
  {
    typedef typename T::tag tag_type;
    BOOST_STATIC_CONSTANT( boost::uint32_t rank = T::rank );

    BOOST_CONCEPT_USAGE(Category) {}
  };

  //////////////////////////////////////////////////////////////////////////////
  // Category archetype
  //////////////////////////////////////////////////////////////////////////////
  struct category_archetype
  {
    typedef struct tag_type {} tag;
    BOOST_STATIC_CONSTANT( boost::uint32_t rank = 0 );
  }
} }

#endif
