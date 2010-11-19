//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#ifndef NT2_SDK_SIMD_DETAILS_IMPL_MAP_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_IMPL_MAP_HPP_INCLUDED

#include <nt2/sdk/simd/preprocessor/include.hpp>

namespace nt2 { namespace functors { struct map_ {}; } }

namespace nt2 { namespace meta
{
  template<class Info, class A0,class A1,class A2,class A3>
  struct  categorize<functors::map_,Info,A0,A1,A2,A3>
  {
    typedef typename meta::category_of<A1>::type::tag type;
  };
} }

namespace nt2 { namespace functors
{
  template<class C,class X, class Info>
  struct  dispatch<map_,tag::simd_(C,X),Info>
        : boost::mpl::lambda< meta::scalar_of<boost::mpl::_2> >::type
  {};
} }

namespace nt2
{
  NT2_FUNCTION_IMPLEMENTATION(functors::map_,map,2)
  NT2_FUNCTION_IMPLEMENTATION(functors::map_,map,3)
  NT2_FUNCTION_IMPLEMENTATION(functors::map_,map,4)
}

#include NT2_SIMD_INCLUDE(map.hpp)

#endif
