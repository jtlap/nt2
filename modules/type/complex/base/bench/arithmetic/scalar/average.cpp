//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/average.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <complex>

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>

using nt2::tag::average_;

namespace n1 {
  typedef float             sT;
  typedef std::complex<sT>  T;

  NT2_TIMING( average_
            , ((T,T(-100,-100),T(100,100)))
              ((T,T(-100,-100),T(100,100)))
            )
    }

namespace n2 {
  typedef double            sT;
  typedef std::complex<sT>  T;

  NT2_TIMING( average_
            , ((T,T(-100,-100),T(100,100)))
              ((T,T(-100,-100),T(100,100)))
            )
    }


