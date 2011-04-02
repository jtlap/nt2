//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#include <nt2/toolbox/boost_math/include/ellint_3.hpp>
#include <nt2/sdk/unit/benchmark.hpp>

//////////////////////////////////////////////////////////////////////////////
// Runtime benchmark for functor<ellint_3_> from boost_math
//////////////////////////////////////////////////////////////////////////////
using nt2::boost_math::tag::ellint_3_;

//////////////////////////////////////////////////////////////////////////////
// bench/simd
// E.G:
// NT2_TIMING( ellint_3_ , ((nt2::simd::native<float,nt2::tag::sse_>, -10, 10))
//                         ((nt2::simd::native<float,nt2::tag::sse_>, -10, 10))
//                         ((nt2::simd::native<float,nt2::tag::sse_>, -10, 10)) ) 
//           )
//////////////////////////////////////////////////////////////////////////////
