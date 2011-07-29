//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_CONSTANTS_HPP_INCLUDED
#define BOOST_SIMD_SDK_SIMD_DETAILS_NATIVE_CONSTANTS_HPP_INCLUDED

#include <boost/dispatch/meta/as.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/simd/include/functions/splat.hpp>
#include <boost/dispatch/details/ignore_unused.hpp>

//==============================================================================
// Forward all constant call to the simd version of themselves that splat
// the appropriate scalar constants into a proper SIMD vector.
//==============================================================================
namespace boost { namespace dispatch { namespace meta
{
  BOOST_DISPATCH_FUNCTOR_IMPLEMENTATION( Tag, tag::cpu_, (Tag)(A0)(X)
                            , ((target_< simd_< arithmetic_<A0>,X> >))
                            )
  {
    typedef typename A0::type                                     target;
    typedef typename meta::scalar_of<target>::type                base;
    typedef typename meta::call<Tag(boost::dispatch::meta::as_<base>)>::type  value;
    typedef boost::simd::native<value,X>                          result_type;

    inline result_type operator()(A0 const&) const
    {
      functor<Tag> callee;
      return boost::simd::splat<result_type>( callee( meta::as_<base>()) );
    }
  };
} } }

#endif
