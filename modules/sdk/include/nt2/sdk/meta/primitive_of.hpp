/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_META_PRIMITIVE_OF_HPP_INCLUDED
#define NT2_SDK_META_PRIMITIVE_OF_HPP_INCLUDED

#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/meta/hierarchy_of.hpp>
#include <nt2/sdk/error/static_assert.hpp>

////////////////////////////////////////////////////////////////////////////////
// Extract the "primitive" type of a Hierarchized type
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  template<class Hierarchized>
  struct primitive_of
  {
    NT2_STATIC_ASSERT ( ( !boost::is_same < typename
                                            hierarchy_of<Hierarchized>::type
                                          , unspecified_<Hierarchized>
                                          >::value
                        )
                      , NT2_UNDEFINED_PRIMITIVE_TYPE
                      , "The primitive of a non hierarchized type is undefined."
                      );
    typedef Hierarchized type;
  };
} }

#endif
