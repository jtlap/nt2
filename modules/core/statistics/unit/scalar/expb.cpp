#include <nt2/sdk/unit/module.hpp>
#include <boost/simd/sdk/config.hpp>
#include <boost/simd/sdk/simd/io.hpp>
#include <nt2/table.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/tanh.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/unary_minus.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/bitofsign.hpp>
#include <nt2/include/functions/bitwise_or.hpp>
#include <nt2/include/functions/cf_sigmoid.hpp>
#include <nt2/include/functions/sigmoid.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/five.hpp>
#include <nt2/sdk/meta/as.hpp>

#include <Eigen/Dense>
#include <unsupported/Eigen/MatrixFunctions>

#include <chrono>
#include <iostream>

// template < class A0 > inline A0 lambert(const A0 & a0)
// {
//   A0 x = nt2::abs(a0)*nt2::Half<A0>();
//   A0 x2 = snt2::qr(x);
//   A0 tmp =  x/(nt2::One<A0>()+x2/(nt2::Three<A0>()+x2/nt2::Five<A0>()));

//   A0 z = nt2::if_else(nt2::le(tmp, nt2::One<A0>()
//                    , nt2::One<A0>()
//                    , tmp));
//   return nt2::bitwise_or(nt2::average(tmp, One<A0>()), nt2::bitofsign(a0));
// }


NT2_TEST_CASE_TPL ( expb,  (float))
{

  using namespace Eigen;
  nt2::table<T> a = nt2::rand(50,20,nt2::meta::as_<T>());
  nt2::table<T> b;

  MatrixXf m = MatrixXf::Random(50,20);
  MatrixXf mb;

  long total_e = 0, total_nt2 = 0, total_fast = 0, total_cf = 0;

  for (int ii=0;ii<100;ii++)
  {
    a = nt2::rand(500,200,nt2::meta::as_<T>());
    m = MatrixXf::Random(500,200);
    auto start = std::chrono::high_resolution_clock::now();

    mb = (T(1)+(-m).array().exp()).inverse();

    auto end = std::chrono::high_resolution_clock::now();

    total_e += (end-start).count();

    start = std::chrono::high_resolution_clock::now();

    b = nt2::sigmoid(a); //nt2::rec(T(1)+nt2::exp( -a) );

    end = std::chrono::high_resolution_clock::now();
    total_nt2 += (end-start).count();

    start = std::chrono::high_resolution_clock::now();

//    b = nt2::oneplus(nt2::tanh(a))*nt2::Half<T>();

//    b = nt2::oneplus(a/(nt2::oneplus(nt2::abs(a))))*nt2::Half<T>();

//    b =  if_else(a > 16.0f, 1.0f, nt2::rec(nt2::oneplus(nt2::sqr(nt2::sqr(nt2::sqr(nt2::sqr(oneminus(a*0.25f))))))));

    b =  if_else(a > 32.0f, 1.0f, nt2::rec(nt2::oneplus(nt2::sqr(nt2::sqr(nt2::sqr(nt2::sqr(nt2::sqr(oneminus(a*0.03125f)))))))));

    end = std::chrono::high_resolution_clock::now();

    total_fast += (end-start).count();

    start = std::chrono::high_resolution_clock::now();
    b =  cf_sigmoid(a);

    end = std::chrono::high_resolution_clock::now();
    total_cf += (end-start).count();
 }
  std::cout<<" nt2        " << total_nt2/100 <<std::endl
           <<" nt2 fast   " << total_fast/100 <<std::endl
           <<" ns eigen   " << total_e/100 <<std::endl
           <<" nt2 cf     " << total_cf/100 <<std::endl
           <<" ns "
           <<std::endl;
}



