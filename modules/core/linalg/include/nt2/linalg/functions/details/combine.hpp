//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_LINALG_FUNCTIONS_DETAILS_COMBINE_HPP_INCLUDED
#define NT2_LINALG_FUNCTIONS_DETAILS_COMBINE_HPP_INCLUDED

#include <nt2/include/functions/tocomplex.hpp>


namespace nt2 { namespace details
{
  template < class T, class A0 >
  BOOST_FORCEINLINE void
  combine_eigens(const T& wr,  const T& wi, A0& w)
  {
    int n = height(wr);
    w.resize(of_size(n, 1));
    for(int i=0; i < n; ++i)
    {
      w.raw()[i] = std::complex<float>(wr.raw()[i], wi.raw()[i]);
    }
  }
  template < class T1, class T2, class A0 >
  BOOST_FORCEINLINE void
  combine_vects(const T1& rv, const T2& wi, A0& v)
  {
    int n = height(rv);
    v.resize(of_size(n, n));
    for(int j=0; j < n; ++j)
    {
      if(wi.raw()[j])
      {
        for(int i = 0; i < n; ++i)
        {
          int ij = i+n*j;
          v.raw()[ij] = tocomplex(rv.raw()[ij],rv.raw()[ij+n]);
          v.raw()[ij+n] = conj(v.raw()[ij]);
        }
        ++j;
      }
      else
        for(int i = 0; i < n; ++i)
        {
          int ij = i+n*j;
          v.raw()[ij] = rv.raw()[ij];
        }
    }
  }
} }

#endif
