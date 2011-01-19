//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/standard/include/sqrt.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <nt2/sdk/simd/native.hpp>
#include <cmath>

typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
typedef nt2::simd::native<float,ext_t> vfloat;
typedef nt2::simd::native<double,ext_t> vdouble;

//////////////////////////////////////////////////////////////////////////////
// Simd Runtime benchmark for functor<sqrt_> from standard
//////////////////////////////////////////////////////////////////////////////
using nt2::standard::tag::sqrt_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, V1 , V2)

NT2_TIMING(nt2::standard::tag::sqrt_,(RS(vfloat,-10000.0f,10000.0f)))
NT2_TIMING(nt2::standard::tag::sqrt_,(RS(vdouble,-10000.0,10000.0)))

#undef RS