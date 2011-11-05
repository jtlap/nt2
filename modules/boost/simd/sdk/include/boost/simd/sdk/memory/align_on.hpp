/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef BOOST_SIMD_SDK_MEMORY_ALIGN_ON_HPP_INCLUDED
#define BOOST_SIMD_SDK_MEMORY_ALIGN_ON_HPP_INCLUDED

#include <boost/assert.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/simd/sdk/simd/extensions.hpp>
#include <boost/dispatch/functor/functor.hpp>
#include <boost/simd/sdk/memory/is_power_of_2.hpp>
#include <boost/dispatch/functor/preprocessor/function.hpp>

namespace boost { namespace simd
{
  namespace tag { struct align_on_ {}; }

  namespace memory
  {
    ////////////////////////////////////////////////////////////////////////////
    // align_on(a0) aligns a0 on the default alignement value
    ////////////////////////////////////////////////////////////////////////////
    BOOST_DISPATCH_FUNCTION_IMPLEMENTATION(tag::align_on_, align_on, 1);

    ////////////////////////////////////////////////////////////////////////////
    // align_on(a0,a1) aligns a0 on the first address multiple of a1
    ////////////////////////////////////////////////////////////////////////////
    template<class A0, class A1> inline
    typename boost::dispatch::meta::call<tag::align_on_(A0 const&, A1 const&)>::type
    align_on(A0 const& a0, A1 const& a1)
    {
      BOOST_ASSERT_MSG( is_power_of_2(a1)
                      , "Invalid alignment boundary. You tried to align an "
                        "address or a value on a non-power of 2 boundary."
                      );
      
      typename boost::dispatch::make_functor<tag::align_on_, A0>::type callee;
      return callee(a0,a1);
    }

    ////////////////////////////////////////////////////////////////////////////
    // align_on<N>(a0) aligns a0 on the first address multiple of N
    ////////////////////////////////////////////////////////////////////////////
    template<std::size_t N,class A0> inline
    typename boost::dispatch::meta::
    call<tag::align_on_(A0 const&,boost::mpl::int_<N> const&)>::type
    align_on(A0 const& a0)
    {
      //==========================================================================
      /*
       * Invalid alignment boundary. You tried to align an address or a value 
       * on a non-power of 2 boundary.
       */    
      //==========================================================================
      BOOST_MPL_ASSERT_MSG
      ( meta::is_power_of_2_c<N>::value 
      , INVALID_ALIGNMENT_BOUNDARY
      , (boost::mpl::int_<N>)
      );              

      typename boost::dispatch::make_functor<tag::align_on_, A0>::type callee;
      return callee(a0,boost::mpl::int_<N>());
    }
  }
} }

#include <boost/simd/sdk/memory/details/align_on.hpp>

#endif
