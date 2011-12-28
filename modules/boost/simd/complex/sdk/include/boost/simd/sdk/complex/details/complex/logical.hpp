//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_COMPLEX_DETAILS_COMPLEX_LOGICAL_HPP_INCLUDED
#define BOOST_SIMD_SDK_COMPLEX_DETAILS_COMPLEX_LOGICAL_HPP_INCLUDED
#include <boost/simd/sdk/simd/logical.hpp>
// A priori there is no need for a logical<complex<T> >
// every predicate function on complex<T> must return a  logical<T> not a logical< complex<T> >
// So this file is to be deleted some day

namespace boost { namespace simd
{
  //  template<typename T> struct logical<std::complex<T> > : logical<T>{}; 
} }

#endif
