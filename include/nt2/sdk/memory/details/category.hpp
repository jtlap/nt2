/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_DETAILS_CATEGORY_HPP_INCLUDED
#define NT2_SDK_MEMORY_DETAILS_CATEGORY_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Various memory hierarchy stuff
////////////////////////////////////////////////////////////////////////////////
#include <boost/pointee.hpp>
#include <nt2/sdk/meta/is_iterator.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>
#include <boost/type_traits/is_pointer.hpp>

////////////////////////////////////////////////////////////////////////////////
// Some hierarchies
////////////////////////////////////////////////////////////////////////////////
NT2_REGISTER_HIERARCHY(iterator_)

////////////////////////////////////////////////////////////////////////////////
// Specialize hierarchy for all iterator types
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace details
{
  template<class T>
  struct  hierarchy_of< T
                      , typename
                        boost::enable_if_c< meta::is_iterator<T>::value>::type
                      >
  {
    typedef typename boost::pointee<T>::type                        pointee_type;
    typedef meta::iterator_ < typename
                              meta::hierarchy_of<pointee_type>::type > type;
  };

  template<> struct  hierarchy_of<void*>
  {
    typedef meta::iterator_< meta::hierarchy_of<void>::type > type;
  };
} }

#endif
