/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_ALIGN_ON_HPP_INCLUDED
#define NT2_SDK_MEMORY_ALIGN_ON_HPP_INCLUDED

#include <nt2/sdk/error/assert.hpp>
#include <nt2/sdk/functor/functor.hpp>
#include <nt2/sdk/memory/is_power_of_2.hpp>
#include <nt2/sdk/functor/preprocessor/function.hpp>

namespace nt2
{
  namespace tag { struct align_on_ {}; }

  namespace memory
  {
    ////////////////////////////////////////////////////////////////////////////
    // align_on(a0) aligns a0 on the default alignement value
    ////////////////////////////////////////////////////////////////////////////
    NT2_FUNCTION_IMPLEMENTATION(tag::align_on_, align_on, 1);

    ////////////////////////////////////////////////////////////////////////////
    // align_on(a0,a1) aligns a0 on the first address multiple of a1
    ////////////////////////////////////////////////////////////////////////////
    template<class A0, class A1> inline
    typename meta::enable_call<tag::align_on_(A0 const&, A1 const&)>::type
    align_on(A0 const& a0, A1 const& a1)
    {
      NT2_ASSERT(   is_power_of_2(a1)
                &&  "Invalid alignment boundary. You tried to align an "
                    "address or a value on a non-power of 2 boundary."
                );
      functor<tag::align_on_> callee;
      return callee(a0,a1);
    }

    ////////////////////////////////////////////////////////////////////////////
    // align_on<N>(a0) aligns a0 on the first address multiple of N
    ////////////////////////////////////////////////////////////////////////////
    template<std::size_t N,class A0> inline
    typename
    meta::enable_call<tag::align_on_(A0 const&,boost::mpl::int_<N> const&)>::type
    align_on(A0 const& a0)
    {
      NT2_STATIC_ASSERT ( meta::is_power_of_2_c<N>::value
                        , INVALID_ALIGNMENT_BOUNDARY
                        , "Invalid alignment boundary. You tried to align an "
                          "address or a value on a non-power of 2 boundary."
                        );

      functor<tag::align_on_> callee;
      return callee(a0,boost::mpl::int_<N>());
    }
  }
}

#include <nt2/sdk/memory/details/align_on.hpp>

#endif
