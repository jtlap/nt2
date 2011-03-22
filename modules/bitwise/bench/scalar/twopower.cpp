//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/bitwise/include/twopower.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <cmath>



//////////////////////////////////////////////////////////////////////////////
// Scalar Runtime benchmark for functor<twopower_> from bitwise
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::twopower_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) , T(V2))

NT2_TIMING(nt2::tag::twopower_,(RS(int32_t,-10,30)))
NT2_TIMING(nt2::tag::twopower_,(RS(uint32_t,0,31)))

NT2_TIMING(nt2::tag::twopower_,(RS(int64_t,-10,62)))
NT2_TIMING(nt2::tag::twopower_,(RS(uint64_t,0,63)))

#undef RS
