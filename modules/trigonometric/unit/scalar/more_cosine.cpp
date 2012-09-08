//////////////////////////////////////////////////////////////////////////////
///   Copyright 2003 and onward LASMEA UMR 6602 CNRS/U.B.P Clermont-Ferrand
///   Copyright 2009 and onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
///
///          Distributed under the Boost Software License, Version 1.0
///                 See accompanying file LICENSE.txt or copy at
///                     http://www.boost.org/LICENSE_1_0.txt
//////////////////////////////////////////////////////////////////////////////
#define NT2_UNIT_MODULE "nt2 trigonometric toolbox - more_cosine/scalar Mode"

//////////////////////////////////////////////////////////////////////////////
// unit test behavior of trigonometric components in scalar mode
//////////////////////////////////////////////////////////////////////////////
/// created  by jt the 11/02/2011
///
#include <nt2/toolbox/crlibm/include/functions/cos_rn.hpp>
#include <nt2/toolbox/crlibm/include/functions/sin_rn.hpp>
#include <nt2/toolbox/trigonometric/include/functions/sinecosine.hpp>
#include <nt2/toolbox/trigonometric/include/functions/fast_cos.hpp>
#include <nt2/toolbox/trigonometric/include/functions/cos.hpp>
#include <nt2/toolbox/trigonometric/include/functions/sincos.hpp>
#include <nt2/toolbox/trigonometric/include/functions/rem_pio2_medium.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/functions/successor.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/ceil.hpp>
#include <nt2/toolbox/trigonometric/constants.hpp>
extern "C" {extern long double cephes_cosl(long double);}

#include <iomanip>

const nt2::int32_t NB =  10;
nt2::int32_t h[NB] =  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
void histo(const float & val)
{
  nt2::int32_t n = nt2::min(nt2::ceil(val*2), NB-1);
  ++h[n];
}

float thresh_at[NB]  =  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
void get_thresh(const float & val, const float& arg)
{
  nt2::int32_t n = nt2::min(nt2::ceil(val*2), NB-1);
  if (!thresh_at[n]) thresh_at[n] = arg/nt2::Pi<float>();
}


int main()
{
  double maxdc = 0.0;
  double maxds = 0.0;
  double maxdca = 0.0;
  double maxdsa = 0.0;
  nt2::int32_t i = 0;
  nt2::int32_t j = 0;
  nt2::int32_t di = 0;
  float thresh = 0.0f;
  for(float a0 = nt2::Zero<float>(); a0 < 100*nt2::Pi<float>(); a0 = nt2::successor(a0, 1))
    {
      float s, c;
      nt2::sinecosine<nt2::direct_small>(a0, s, c);
      float scrm =  nt2::crlibm::sin_rn(a0);
      float ccrm =  nt2::crlibm::cos_rn(a0);
      double ds = nt2::ulpdist(s, scrm);
      maxds =  nt2::max(maxds, ds);
//       double dc = nt2::ulpdist(c, ccrm);
//       maxdc =  nt2::max(maxdc, dc);
//       histo(nt2::max(dc, ds));
//       get_thresh(nt2::max(dc, ds), a0);
      histo(ds);
      get_thresh(ds, a0);
      ++i;
    }
  std::cout << "nb values " << i << std::endl;
  std::cout << "ulp cos   " << maxdc << std::endl;
  std::cout << "ulp sin   " << maxds << std::endl;
  std::cout << std::setprecision(7) << "thresh    " << thresh<< std::endl;

  for(nt2::int32_t i=0; i < NB; i++)
   {
     std::cout << i << " -> " << h[i] << std::endl;
   }
  for(nt2::int32_t i=0; i < NB; i++)
   {
     std::cout << i << " -> " << thresh_at[i] << std::endl;
   }
  return 0;
}

// #include <boost/type_traits/is_same.hpp>
// #include <nt2/sdk/functor/meta/call.hpp>
// #include <nt2/sdk/unit/tests.hpp>
// #include <nt2/sdk/unit/module.hpp>
// #include <nt2/sdk/memory/buffer.hpp>
// #include <nt2/include/constants/real.hpp>
// #include <nt2/include/constants/infinites.hpp>


// NT2_TEST_CASE_TPL ( cosine_real__1_0, (float))
// {

//   using nt2::small_;
//   using nt2::cosine;
//   using nt2::tag::cosine_;
//   typedef typename nt2::meta::as_integer<T>::type iT;
//   typedef typename nt2::meta::call<cosine_<small_>(T)>::type r_t;
//   typedef typename nt2::meta::upgrade<T>::type u_t;
//   typedef typename boost::dispatch::meta::as_floating<T>::type wished_r_t;

//   // return type conformity test
//   NT2_TEST( (boost::is_same < r_t, wished_r_t >::value) );
//   std::cout << std::endl;


//   // specific values tests
//   NT2_TEST_ULP_EQUAL(                  nt2::cos(nt2::Hundred<T>()), nt2::crlibm::cos_rn(nt2::Hundred<T>()), 0.5);
//   NT2_TEST_ULP_EQUAL(             nt2::fast_cos(nt2::Hundred<T>()), nt2::Nan<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL( cosine<nt2::clipped_pio4_>(nt2::Hundred<T>()), nt2::Nan<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL(cosine<nt2::clipped_small>(nt2::Hundred<T>()), nt2::Nan<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL( cosine<nt2::direct_small>(nt2::Hundred<T>()), nt2::crlibm::cos_rn(nt2::Hundred<T>()), 0.5);
//   NT2_TEST_ULP_EQUAL(        cosine<nt2::small_>(nt2::Hundred<T>()), nt2::crlibm::cos_rn(nt2::Hundred<T>()), 0.5);

//   NT2_TEST_ULP_EQUAL(                  nt2::cos(41*nt2::Pi<T>()),   nt2::Mone<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL(             nt2::fast_cos(41*nt2::Pi<T>()),   nt2::Nan<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL( cosine<nt2::clipped_pio4_>(41*nt2::Pi<T>()),   nt2::Nan<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL(cosine<nt2::clipped_small>(41*nt2::Pi<T>()),   nt2::Nan<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL( cosine<nt2::direct_small>(41*nt2::Pi<T>()),   nt2::Mone<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL(        cosine<nt2::small_>(41*nt2::Pi<T>()),   nt2::Mone<r_t>(), 0.5);

//   NT2_TEST_ULP_EQUAL(                  nt2::cos(nt2::Pi<T>()),      nt2::Mone<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL(             nt2::fast_cos(nt2::Pi<T>()),      nt2::Nan<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL( cosine<nt2::clipped_pio4_>(nt2::Pi<T>()),      nt2::Nan<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL(cosine<nt2::clipped_small>(nt2::Pi<T>()),      nt2::Mone<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL( cosine<nt2::direct_small>(nt2::Pi<T>()),      nt2::Mone<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL(        cosine<nt2::small_>(nt2::Pi<T>()),      nt2::Mone<r_t>(), 0.5);

//   NT2_TEST_ULP_EQUAL(                  nt2::cos(nt2::Pi<T>()/T(2)), nt2::Zero<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL(             nt2::fast_cos(nt2::Pi<T>()/T(2)), nt2::Nan<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL( cosine<nt2::clipped_pio4_>(nt2::Pi<T>()/T(2)), nt2::Nan<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL(cosine<nt2::clipped_small>(nt2::Pi<T>()/T(2)), nt2::Zero<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL( cosine<nt2::direct_small>(nt2::Pi<T>()/T(2)), nt2::Zero<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL(        cosine<nt2::small_>(nt2::Pi<T>()/T(2)), nt2::Zero<r_t>(), 0.5);

//   NT2_TEST_ULP_EQUAL(                  nt2::cos(nt2::Pi<T>()/T(4)), nt2::Sqrt_2o_2<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL(             nt2::fast_cos(nt2::Pi<T>()/T(4)), nt2::Sqrt_2o_2<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL( cosine<nt2::clipped_pio4_>(nt2::Pi<T>()/T(4)), nt2::Sqrt_2o_2<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL(cosine<nt2::clipped_small>(nt2::Pi<T>()/T(4)), nt2::Sqrt_2o_2<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL( cosine<nt2::direct_small>(nt2::Pi<T>()/T(4)), nt2::Sqrt_2o_2<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL(        cosine<nt2::small_>(nt2::Pi<T>()/T(4)), nt2::Sqrt_2o_2<r_t>(), 0.5);

//   NT2_TEST_ULP_EQUAL(                  nt2::cos(nt2::Zero<T>()),    nt2::One<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL(             nt2::fast_cos(nt2::Zero<T>()),    nt2::One<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL( cosine<nt2::clipped_pio4_>(nt2::Zero<T>()),    nt2::One<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL(cosine<nt2::clipped_small>(nt2::Zero<T>()),    nt2::One<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL( cosine<nt2::direct_small>(nt2::Zero<T>()),    nt2::One<r_t>(), 0.5);
//   NT2_TEST_ULP_EQUAL(        cosine<nt2::small_>(nt2::Zero<T>()),    nt2::One<r_t>(), 0.5);

// } // end of test for floating_
