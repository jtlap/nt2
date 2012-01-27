/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_SDK_COMPLEX_IO_HPP_INCLUDED
#define NT2_SDK_COMPLEX_IO_HPP_INCLUDED
#include <boost/simd/sdk/simd/native.hpp>

namespace boost { namespace simd
{
  template<class T>
  BOOST_DISPATCH_FORCE_INLINE
  std::ostream& operator<<(std::ostream& os, std::complex<T> const& v )
  {
    return os << "(" << real(v) << ", " << imag(v) << ")";
  }
  

  template<class T, class Ext>
  BOOST_DISPATCH_FORCE_INLINE
  std::ostream& operator<<(std::ostream& os, boost::simd::native<std::complex<T>,Ext> const& v )
  {
    typedef boost::simd::native<std::complex<T>, Ext> cvtype;
    const std::size_t size = meta::cardinal_of<boost::simd::native<T, Ext> > ::value;
    os << "{"; 
    for(std::size_t i = 0;  i < size; ++i)
      {
        os << v[i] << ((i+1 == size) ? "}" :", ");
      }
    return os; 
  }
} }

#endif
