//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/euler/include/digamma.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <cmath>



//////////////////////////////////////////////////////////////////////////////
// Scalar Runtime benchmark for functor<digamma_> from euler
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::digamma_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) , T(V2))

NT2_TIMING(nt2::tag::digamma_,(RS(float,-30.0f,30.0f)))
NT2_TIMING(nt2::tag::digamma_,(RS(double,-30.0,30.0)))
NT2_TIMING(nt2::tag::digamma_,(RS(int32_t,-30.0,30.0)))

#undef RS