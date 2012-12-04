//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 complex.exponential toolbox - sinh/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of exponential components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created by jt the 08/12/2010
///
#include <nt2/include/functions/sinh.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/mul_i.hpp>
#include <nt2/include/functions/mul_minus_i.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <boost/type_traits/is_same.hpp>
#include <nt2/sdk/functor/meta/call.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <nt2/sdk/meta/as_floating.hpp>
#include <nt2/sdk/meta/as_signed.hpp>
#include <nt2/sdk/meta/upgrade.hpp>
#include <nt2/sdk/meta/downgrade.hpp>
#include <nt2/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/type_traits/common_type.hpp>
#include <nt2/sdk/unit/tests.hpp>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/memory/buffer.hpp>
#include <nt2/toolbox/constant/constant.hpp>


NT2_TEST_CASE_TPL ( sinh_real__1_0,  (double))//NT2_REAL_TYPES)
{

  using nt2::sinh;
  using nt2::tag::sinh_;
  typedef std::complex<T> cT;
  typedef cT r_t;
  double ulpd;
  ulpd=0.0;
  const int N = 20;
  cT inputs[N] =
    { cT(nt2::Zero<T>(),nt2::Zero<T>()),cT(nt2::Inf<T>(),nt2::Zero<T>()),cT(nt2::Minf<T>(),nt2::Zero<T>()),cT(nt2::Nan<T>(),nt2::Zero<T>()),
      cT(nt2::Zero<T>(),nt2::Inf<T>()), cT(nt2::Inf<T>(),nt2::Inf<T>()), cT(nt2::Minf<T>(),nt2::Inf<T>()), cT(nt2::Nan<T>(),nt2::Inf<T>()),
      cT(nt2::Zero<T>(),nt2::Minf<T>()),cT(nt2::Inf<T>(),nt2::Minf<T>()),cT(nt2::Minf<T>(),nt2::Minf<T>()),cT(nt2::Nan<T>(),nt2::Minf<T>()),
      cT(nt2::Zero<T>(),nt2::Nan<T>()), cT(nt2::Inf<T>(),nt2::Nan<T>()), cT(nt2::Minf<T>(),nt2::Nan<T>()), cT(nt2::Nan<T>(),nt2::Nan<T>()),
      cT(nt2::Zero<T>(),nt2::Pi <T>()), cT(nt2::Inf<T>(),nt2::Pi <T>()), cT(nt2::Minf<T>(),nt2::Pi <T>()), cT(nt2::Nan<T>(),nt2::Pi <T>()),
    };

  cT results[N] =
    { cT(nt2::Zero<T>(),nt2::Zero<T>()),cT(nt2::Inf<T>(),nt2::Zero<T>()),cT(nt2::Minf<T>(),nt2::Zero<T>()),cT(nt2::Nan<T>(),nt2::Zero<T>()),
      cT(nt2::Zero<T>(),nt2::Nan<T>()),cT(nt2::Inf<T>(),nt2::Nan<T>()), cT(nt2::Minf<T>(),nt2::Nan<T>()), cT(nt2::Nan<T>(),nt2::Nan<T>()),
      cT(nt2::Zero<T>(),nt2::Nan<T>()),cT(nt2::Inf<T>(),nt2::Nan<T>()), cT(nt2::Minf<T>(),nt2::Nan<T>()), cT(nt2::Nan<T>(),nt2::Nan<T>()),
      cT(nt2::Zero<T>(),nt2::Nan<T>()), cT(nt2::Inf<T>(),nt2::Nan<T>()), cT(nt2::Minf<T>(),nt2::Nan<T>()),cT(nt2::Nan<T>(),nt2::Nan<T>()),
      cT(nt2::Zero<T>(),nt2::Zero<T>()),cT(nt2::Minf<T>(),nt2::Inf<T>()),cT(nt2::Inf<T>(),nt2::Inf<T>()),cT(nt2::Nan<T>(),nt2::Nan <T>()),
    };

  for(int i=0; i < N; i++)
   {
     std::cout << "input = " << inputs[i] << " -> " << results[i] << std::endl;
     NT2_TEST_ULP_EQUAL(nt2::sinh(inputs[i]), results[i], 1);
     //     NT2_TEST_ULP_EQUAL(nt2::sinh(inputs[i]), nt2::mul_minus_i(nt2::sin(nt2::mul_i(inputs[i]))), 1);
     NT2_TEST_ULP_EQUAL(nt2::sinh(-inputs[i]), -results[i], 1);
   }

} // end of test for floating_
