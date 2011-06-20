//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_SIMD_DETAILS_NATIVE_CONSTANTS_HPP_INCLUDED
#define NT2_SDK_SIMD_DETAILS_NATIVE_CONSTANTS_HPP_INCLUDED

#include <nt2/sdk/meta/as.hpp>
#include <nt2/sdk/simd/category.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/sdk/details/ignore_unused.hpp>

//==============================================================================
// Forward all constant call to the simd version of themselves that splat
// the appropriate scalar constants into a proper SIMD vector.
//==============================================================================
namespace nt2 { namespace meta
{
  NT2_FUNCTOR_IMPLEMENTATION( Tag, tag::cpu_, (Tag)(A0)(X)
                            , ((target_< simd_< arithmetic_<A0>,X> >))
                            )
  {
    typedef typename meta::strip<A0>::type::type                  target;
    typedef typename meta::scalar_of<target>::type                base;
    typedef typename meta::call<Tag(nt2::meta::as_<base>)>::type  result;
    typedef typename target::template cast<result>::type          result_type;

    inline result_type operator()(A0 const&) const
    {
      functor<Tag> callee;
      return splat<result_type>( callee( nt2::meta::as_<base>()) );
    }
  };
} }

#endif
