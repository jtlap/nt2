/*******************************************************************************
 *         Copyright 2003-2010 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2009-2010 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_SIMD_PACK_IO_HPP_INCLUDED
#define NT2_SDK_SIMD_PACK_IO_HPP_INCLUDED

#include <nt2/sdk/simd/io.hpp>

namespace nt2 { namespace simd
{
  ////////////////////////////////////////////////////////////////////////////
  // Stream insertion for vec<T,C> and SIMD expression
  ////////////////////////////////////////////////////////////////////////////
  template<class X,class T,class C> inline std::ostream&
  operator<<(std::ostream& os, expression<X,T,C> const& v )
  {
    // We want to display (u)int8_t as a number
    typedef typename
            boost::mpl::if_c< (sizeof(T)==1), int, T>::type display_type;

    os << "{";
    for(std::size_t i=0;i<C::value-1;++i)
      os << static_cast<display_type>(v[i]) << ",";
    os << static_cast<display_type>(v[C::value-1]) << "}";
    return os;
  }
} }

#endif
