//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/reduction/include/sum.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <cmath>



//////////////////////////////////////////////////////////////////////////////
// Scalar Runtime benchmark for functor<sum_> from reduction
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::sum_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) , T(V2))

NT2_TIMING(nt2::tag::sum_,(RS(float,-10000.0f,10000.0f)))
NT2_TIMING(nt2::tag::sum_,(RS(double,-10000.0,10000.0)))
NT2_TIMING(nt2::tag::sum_,(RS(int64_t,-10000,10000)))
NT2_TIMING(nt2::tag::sum_,(RS(int32_t,-10000,10000)))
NT2_TIMING(nt2::tag::sum_,(RS(int16_t,-32768,32767)))
NT2_TIMING(nt2::tag::sum_,(RS(int8_t,-128,127)))
NT2_TIMING(nt2::tag::sum_,(RS(uint64_t,0,65535)))
NT2_TIMING(nt2::tag::sum_,(RS(uint32_t,0,65535)))
NT2_TIMING(nt2::tag::sum_,(RS(uint16_t,0,65535)))
NT2_TIMING(nt2::tag::sum_,(RS(uint8_t,0,255)))

#undef RS