//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/combinatorial/include/anp.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <cmath>



//////////////////////////////////////////////////////////////////////////////
// Scalar Runtime benchmark for functor<anp_> from combinatorial
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::anp_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) , T(V2))

NT2_TIMING(nt2::tag::anp_,(RS(int64_t,-10000,10000))(RS(int64_t,-10000,10000)))
NT2_TIMING(nt2::tag::anp_,(RS(int32_t,-10000,10000))(RS(int32_t,-10000,10000)))
NT2_TIMING(nt2::tag::anp_,(RS(uint64_t,0,65535))(RS(uint64_t,0,65535)))
NT2_TIMING(nt2::tag::anp_,(RS(uint32_t,0,65535))(RS(uint32_t,0,65535)))

#undef RS