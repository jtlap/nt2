//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/trigonometric/include/cos.hpp>
#include <nt2/toolbox/trigonometric/include/fast_cos.hpp>
#include <nt2/toolbox/libc/include/cos.hpp>    
#include <nt2/sdk/unit/benchmark.hpp>
#include <nt2/sdk/simd/native.hpp>
#include <cmath>

typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
typedef nt2::simd::native<float,ext_t> vfloat;
typedef nt2::simd::native<double,ext_t> vdouble;

//////////////////////////////////////////////////////////////////////////////
// Simd Runtime benchmark for functor<cos_> from trigonometric
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::cos_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, V1 , V2)

NT2_TIMING(nt2::tag::fast_cos_,(RS(vfloat,-0.785398f,-0.785398f)))
NT2_TIMING(nt2::tag::fast_cos_,(RS(vdouble,-0.785398,-0.785398)))
NT2_TIMING(nt2::tag::fast_cos_,(RS(float,-0.785398f,-0.785398f)))
NT2_TIMING(nt2::tag::fast_cos_,(RS(double,-0.785398,-0.785398)))
NT2_TIMING(nt2::tag::cos_,(RS(vfloat,-31.4f,31.4f)))
NT2_TIMING(nt2::tag::cos_,(RS(vdouble,-31.4,31.4)))
NT2_TIMING(nt2::tag::cos_,(RS(float,-31.4f,31.4f)))
NT2_TIMING(nt2::tag::cos_,(RS(double,-31.4,31.4)))
NT2_TIMING(nt2::tag::cos_,(RS(vfloat,-0.785398f,-0.785398f)))
NT2_TIMING(nt2::tag::cos_,(RS(vdouble,-0.785398,-0.785398)))
NT2_TIMING(nt2::tag::cos_,(RS(float,-0.785398f,-0.785398f)))
NT2_TIMING(nt2::tag::cos_,(RS(double,-0.785398,-0.785398)))
// NT2_TIMING(nt2::libc::tag::cos_,(RS,float,-31.4f,31.4f)))
// NT2_TIMING(nt2::libc::tag::cos_,(RS(double,-31.4,31.4)))
// NT2_TIMING(nt2::libc::tag::cos_,(RS(float,-0.785398f,-0.785398f)))
// NT2_TIMING(nt2::libc::tag::cos_,(RS(double,-0.785398,-0.785398)))

#undef RS
