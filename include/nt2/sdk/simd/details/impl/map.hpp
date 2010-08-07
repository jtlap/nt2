/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_DETAILS_FUNCTION_MAP_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_FUNCTION_MAP_HPP_INCLUDED

#include <nt2/sdk/meta/irrelevant.hpp>
#include <nt2/sdk/simd/preprocessor/include.hpp>

namespace nt2 { namespace functors { struct map_ {}; } }

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Registers functor to be irrelevant in category computation
  //////////////////////////////////////////////////////////////////////////////
  template<class T, class I>
  struct category_of< functors::functor<T,I> > { typedef tag::irrelevant type; };

  //////////////////////////////////////////////////////////////////////////////
  // Registers function type and function pointer to be irrelevant
  // This prevent us to specialize functor especially for map
  //////////////////////////////////////////////////////////////////////////////
  template<class R, class A0>
  struct category_of<R(*)(A0)>        { typedef tag::irrelevant type; };
  template<class R, class A0>
  struct category_of<R(A0)>           { typedef tag::irrelevant type; };
  template<class R, class A0, class A1>
  struct category_of<R(*)(A0,A1)>     { typedef tag::irrelevant type; };
  template<class R, class A0, class A1>
  struct category_of<R(A0,A1)>        { typedef tag::irrelevant type; };
  template<class R, class A0, class A1, class A2>
  struct category_of<R(*)(A0,A1,A2)>  { typedef tag::irrelevant type; };
  template<class R, class A0, class A1, class A2>
  struct category_of<R(A0,A1,A2)>     { typedef tag::irrelevant type; };
} }

namespace nt2
{
  NT2_FUNCTION_IMPLEMENTATION(functors::map_,map,2)
  NT2_FUNCTION_IMPLEMENTATION(functors::map_,map,3)
  NT2_FUNCTION_IMPLEMENTATION(functors::map_,map,4)
}

#include NT2_SIMD_INCLUDE(map.hpp)

#endif
