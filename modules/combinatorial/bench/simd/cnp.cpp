//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/combinatorial/include/cnp.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <nt2/sdk/simd/native.hpp>
#include <cmath>

typedef NT2_SIMD_DEFAULT_EXTENSION  ext_t;
typedef nt2::simd::native<int64_t,ext_t> vint64_t;
typedef nt2::simd::native<int32_t,ext_t> vint32_t;
typedef nt2::simd::native<uint64_t,ext_t> vuint64_t;
typedef nt2::simd::native<uint32_t,ext_t> vuint32_t;

//////////////////////////////////////////////////////////////////////////////
// Simd Runtime benchmark for functor<cnp_> from combinatorial
//////////////////////////////////////////////////////////////////////////////
using nt2::tag::cnp_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, V1 , V2)

NT2_TIMING(nt2::tag::cnp_,(RS(vint64_t,-10000,10000))(RS(vint64_t,-10000,10000)))
NT2_TIMING(nt2::tag::cnp_,(RS(vint32_t,-10000,10000))(RS(vint32_t,-10000,10000)))
NT2_TIMING(nt2::tag::cnp_,(RS(vuint64_t,0,65535))(RS(vuint64_t,0,65535)))
NT2_TIMING(nt2::tag::cnp_,(RS(vuint32_t,0,65535))(RS(vuint32_t,0,65535)))

#undef RS