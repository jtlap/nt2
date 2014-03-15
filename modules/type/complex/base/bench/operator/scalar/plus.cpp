//==============================================================================
//         Copyright 2014 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/include/functions/plus.hpp>
#include <nt2/sdk/complex/complex.hpp>
#include <nt2/sdk/complex/dry.hpp>
#include <complex>

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/timing.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/valmin.hpp>

using nt2::tag::plus_;
using nt2::Valmin;
using nt2::Valmax;

namespace n1
{
  typedef float             sT;
  typedef std::complex<sT>  T;

  NT2_TIMING( plus_
            , ((T,T(Valmin<sT>()/2,Valmin<sT>()/2),T(Valmax<sT>()/2,Valmax<sT>()/2)))
              ((T,T(Valmin<sT>()/2,Valmin<sT>()/2),T(Valmax<sT>()/2,Valmax<sT>()/2)))
            )
}

namespace n2
{
  typedef double            sT;
  typedef std::complex<sT>  T;

  NT2_TIMING( plus_
            , ((T,T(Valmin<sT>()/2,Valmin<sT>()/2),T(Valmax<sT>()/2,Valmax<sT>()/2)))
              ((T,T(Valmin<sT>()/2,Valmin<sT>()/2),T(Valmax<sT>()/2,Valmax<sT>()/2)))
            )
}
