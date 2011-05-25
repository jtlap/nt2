/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_META_TERMINAL_OF_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_META_TERMINAL_OF_HPP_INCLUDED

#include <boost/mpl/always.hpp>
#include <nt2/sdk/simd/pack/pack.hpp>
#include <nt2/sdk/dsl/terminal_of.hpp>
#include <nt2/sdk/simd/pack/domain.hpp>

namespace nt2 { namespace ext
{
  //////////////////////////////////////////////////////////////////////////////
  // For simd domain, we return the proper pack
  //////////////////////////////////////////////////////////////////////////////
  template< class Expression,class Type,class Cardinal>
  struct  terminal_of_impl< Expression, simd::domain<Type,Cardinal> >
        : boost::mpl::always< simd::pack<Type,Cardinal::value> >
  {};
} }

#endif
