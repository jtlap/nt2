//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/gsl_specfun/include/gsl_sf_lndoublefact.hpp>
#include <nt2/sdk/unit/benchmark.hpp>
#include <cmath>

//////////////////////////////////////////////////////////////////////////////
// Scalar Runtime benchmark for functor<gsl_sf_lndoublefact_> from gsl_specfun
//////////////////////////////////////////////////////////////////////////////
using nt2::gsl_specfun::tag::gsl_sf_lndoublefact_;

//////////////////////////////////////////////////////////////////////////////
// range macro
//////////////////////////////////////////////////////////////////////////////
#define RS(T,V1,V2) (T, T(V1) , T(V2))

// TO DO Check ranges
NT2_TIMING(nt2::gsl_specfun::tag::gsl_sf_lndoublefact_,(RS(double,-1.0,1.0)))

#undef RS