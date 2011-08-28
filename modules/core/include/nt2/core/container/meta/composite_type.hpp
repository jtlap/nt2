//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_CONTAINER_META_IS_COMPOSITE_HPP_INCLUDED
#define NT2_CORE_CONTAINER_META_IS_COMPOSITE_HPP_INCLUDED

#include <boost/mpl/apply.hpp>
#include <boost/mpl/transform.hpp>
#include <nt2/core/container/meta/is_composite.hpp>

////////////////////////////////////////////////////////////////////////////////
// Build a type from a composite by applying a lambda function on it or on
// all its components
////////////////////////////////////////////////////////////////////////////////
namespace nt2 { namespace meta
{
  template< typename Type
          , typename Transform
          , bool IsComposite = is_composite<T>::value          
          >
  struct  make_composite 
        : boost::mpl::apply<Transform,T> 
  {};

  template< typename Type
          , typename Transform
          >
  struct  make_composite<Type,Transform,true> 
        : boost::mpl::transform<T,Transform> 
  {};
} }

#endif
