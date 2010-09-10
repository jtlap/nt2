/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#include <nt2/toolbox/gmp/add.hpp>
#include <nt2/sdk/unit/benchmark.hpp>

////////////////////////////////////////////////////////////////////////////////
// Runtime benchmark for functor<add_> from gmp
////////////////////////////////////////////////////////////////////////////////
using nt2::functors::add_;

////////////////////////////////////////////////////////////////////////////////
// Scalar benchmark
// E.G:
// NT2_TIMING( add_ , ((nt2::uint32_t, -10, 10))((nt2::uint32_t, -10, 10)) )
////////////////////////////////////////////////////////////////////////////////

