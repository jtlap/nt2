//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/crlibm/include/atan_rz.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <cmath>



//////////////////////////////////////////////////////////////////////////////
// Scalar Runtime benchmark for functor<atan_rz_> from crlibm
//////////////////////////////////////////////////////////////////////////////
using nt2::crlibm::tag::atan_rz_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) , T(V2))

NT2_TIMING(nt2::crlibm::tag::atan_rz_,(RS(float,-10000.0f,10000.0f)))
NT2_TIMING(nt2::crlibm::tag::atan_rz_,(RS(double,-10000.0,10000.0)))

#undef RS