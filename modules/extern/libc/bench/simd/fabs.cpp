//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/toolbox/libc/include/functions/fabs.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/sdk/bench/benchmark.hpp>
#include <cmath>

//////////////////////////////////////////////////////////////////////////////
// Scalar Runtime benchmark for functor<fabs_> from libc
//////////////////////////////////////////////////////////////////////////////
using nt2::libc::tag::fabs_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) , T(V2))

// TO DO Check ranges
NT2_TIMING(nt2::libc::tag::fabs_,(RS(float,-1.0f,1.0f)))
NT2_TIMING(nt2::libc::tag::fabs_,(RS(double,-1.0f,1.0f)))
NT2_TIMING(nt2::libc::tag::fabs_,(RS(int32_t,-1,1)))

#undef RS
