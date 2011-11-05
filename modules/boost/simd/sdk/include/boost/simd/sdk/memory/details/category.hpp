/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_MEMORY_DETAILS_CATEGORY_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_DETAILS_CATEGORY_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// Various memory hierarchy stuff
////////////////////////////////////////////////////////////////////////////////
#include <boost/pointee.hpp>
#include <boost/dispatch/meta/is_iterator.hpp>
#include <boost/dispatch/meta/hierarchy_of.hpp>
#include <boost/type_traits/is_pointer.hpp>

////////////////////////////////////////////////////////////////////////////////
// Some hierarchies
////////////////////////////////////////////////////////////////////////////////
BOOST_DISPATCH_REGISTER_HIERARCHY(iterator_)

namespace boost { namespace simd { namespace ext
{
  using boost::dispatch::meta::iterator_;
} } }

////////////////////////////////////////////////////////////////////////////////
// Specialize hierarchy for all iterator types
////////////////////////////////////////////////////////////////////////////////
namespace boost { namespace dispatch { namespace details
{
  template<class T>
  struct  value_of< T
                  , typename
                    boost::enable_if_c< meta::is_iterator<T>::value>::type
                  >
   : value_of< typename boost::pointee<T>::type >
  {
  };

  template<class T, class Origin>
  struct  hierarchy_of< T
                      , Origin
                      , typename
                        boost::enable_if_c< meta::is_iterator<T>::value>::type
                      >
  {
    typedef typename boost::pointee<T>::type                        pointee_type;
    typedef meta::iterator_ < typename
                              meta::hierarchy_of<pointee_type,Origin>::type > type;
  };
}

namespace meta
{
  template<class Origin>
  struct  hierarchy_of<void*, Origin>
  {
    typedef meta::iterator_<meta::generic_<meta::void_<Origin> > >  type;
  };
} } }

#endif
