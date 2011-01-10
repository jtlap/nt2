//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/predicates/include/is_not_finite.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <cmath>



//////////////////////////////////////////////////////////////////////////////
// Scalar Runtime benchmark for functor<is_not_finite_> from predicates
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::is_not_finite_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) , T(V2))

NT2_TIMING(nt2::tag::is_not_finite_,(RS(float,-10000.0f,10000.0f)))
NT2_TIMING(nt2::tag::is_not_finite_,(RS(double,-10000.0,10000.0)))
NT2_TIMING(nt2::tag::is_not_finite_,(RS(int64_t,-10000,10000)))
NT2_TIMING(nt2::tag::is_not_finite_,(RS(int32_t,-10000,10000)))
NT2_TIMING(nt2::tag::is_not_finite_,(RS(int16_t,-32768,32767)))
NT2_TIMING(nt2::tag::is_not_finite_,(RS(int8_t,-128,127)))
NT2_TIMING(nt2::tag::is_not_finite_,(RS(uint64_t,0,65535)))
NT2_TIMING(nt2::tag::is_not_finite_,(RS(uint32_t,0,65535)))
NT2_TIMING(nt2::tag::is_not_finite_,(RS(uint16_t,0,65535)))
NT2_TIMING(nt2::tag::is_not_finite_,(RS(uint8_t,0,255)))

#undef RS