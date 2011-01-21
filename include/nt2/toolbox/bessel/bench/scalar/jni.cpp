//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/bessel/include/jni.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <cmath>



//////////////////////////////////////////////////////////////////////////////
// Scalar Runtime benchmark for functor<jni_> from bessel
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::jni_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) , T(V2))



NT2_TIMING(nt2::tag::jni_,(RS(int64_t,0,63))(RS(double,-10000.0,10000.0)))
NT2_TIMING(nt2::tag::jni_,(RS(int32_t,0,31))(RS(float,-10000.0f,10000.0f)))

#undef RS