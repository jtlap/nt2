//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/bench/timing.hpp>

#include <boost/simd/include/native.hpp>
#include <nt2/include/functions/cos.hpp>
#include <boost/simd/include/functions/abs.hpp>
#include <boost/simd/include/functions/plus.hpp>

using boost::simd::native;

using boost::simd::tag::abs_;
using boost::simd::tag::plus_;
using nt2::tag::cos_;

typedef BOOST_SIMD_DEFAULT_EXTENSION ext_t;

#define RS(T,V1,V2) (T, V1, V2)

NT2_TIMING(abs_, (RS(float  , -100, 100)) );
NT2_TIMING(abs_, (RS(double , -100, 100)) );

NT2_TIMING(plus_, (RS(float, -100, 100))(RS(float, -100, 100)) );
NT2_TIMING(plus_, (RS(double, -100, 100))(RS(double, -100, 100)) );

NT2_TIMING(cos_, (RS(float  , -3.14/4, 3.14/4)) );
NT2_TIMING(cos_, (RS(double , -3.14/4, 3.14/4)) );

NT2_TIMING(abs_, (RS((native<float ,ext_t>) , -100, 100)) );
NT2_TIMING(abs_, (RS((native<double,ext_t>) , -100, 100)) );

NT2_TIMING(plus_, (RS((native<float ,ext_t>), -100, 100))
                  (RS((native<float ,ext_t>), -100, 100))
          );

NT2_TIMING(plus_, (RS((native<double,ext_t>), -100, 100))
                  (RS((native<double,ext_t>), -100, 100))
          );

NT2_TIMING(cos_, (RS((native<float ,ext_t>) , -3.14159/4, 3.14159/4)) );
NT2_TIMING(cos_, (RS((native<double,ext_t>) , -3.14159/4, 3.14159/4)) );
