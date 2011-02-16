/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_META_FACTORY_OF_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_META_FACTORY_OF_HPP_INCLUDED

#include <nt2/sdk/meta/factory_of.hpp>
#include <nt2/sdk/simd/pack/forward.hpp>

namespace nt2 { namespace meta
{
  template< class Type
          , std::size_t Cardinal
          , class Dummy 
          >
  struct factory_of< simd::pack<Type, Cardinal, Dummy> >
  {
      typedef factory_of< simd::pack<Type, Cardinal, Dummy> > type;
      
      template<typename T>
      struct apply
      {
          typedef simd::pack<T, Cardinal, Dummy> type;
      };      
  };
} }

#endif
