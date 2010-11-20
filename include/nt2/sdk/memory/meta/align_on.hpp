/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_MEMORY_META_ALIGN_ON_HPP_INCLUDED
#define NT2_SDK_MEMORY_META_ALIGN_ON_HPP_INCLUDED

#include <cstddef>
#include <boost/mpl/size_t.hpp>
#include <boost/mpl/integral_c.hpp>
#include <nt2/sdk/memory/parameters.hpp>
#include <nt2/sdk/error/static_assert.hpp>
#include <nt2/sdk/memory/meta/is_power_of_2.hpp>

namespace nt2 { namespace meta
{
  //////////////////////////////////////////////////////////////////////////////
  // Compute an aligned value of an integral constant on a power of 2 boundary.
  // Documentation: align_on_c.rst
  //////////////////////////////////////////////////////////////////////////////
  template<std::size_t V, std::size_t N = NT2_CONFIG_ALIGNMENT>
  struct align_on_c
       : boost::mpl::integral_c< std::size_t
                               , (V+N-1) & ~(N-1)
                               >
  {
    NT2_STATIC_ASSERT ( (meta::is_power_of_2_c<N>::value)
                      , INVALID_ALIGNMENT_VALUE
                      , "Alignment done on a non-power of two boundary."
                      );
  };

  //////////////////////////////////////////////////////////////////////////////
  // Compute an aligned value of an Integral Constant on a power of 2 boundary.
  // Documentation: align_on.rst
  //////////////////////////////////////////////////////////////////////////////
  template<class V, class N = boost::mpl::size_t<NT2_CONFIG_ALIGNMENT> >
  struct align_on
       : boost::mpl::integral_c< typename V::value_type
                               , align_on_c<V::value,N::value>::value
                               >
  {};
} }

#endif
