//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#define NT2_UNIT_MODULE "nt2 container fluid"

#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/toolbox/operator/operator.hpp>
#include <nt2/include/functions/function.hpp>
#include <nt2/include/functions/sum.hpp>

#include <nt2/sdk/timing/now.hpp>
#include <nt2/sdk/unit/details/helpers.hpp>
#include <nt2/sdk/unit/perform_benchmark.hpp>
#include <nt2/sdk/unit/module.hpp>

#include <nt2/table.hpp>

template<class T> struct Compute
{
  Compute(std::size_t m, std::size_t n, T const& min, T const& max )
    : M(m),N(n), dX(0.01), dY(0.01), traj_x(nt2::of_size(m,n)), traj_y(nt2::of_size(m,n))
    , j1(nt2::of_size(m-2, n-2)), j2(nt2::of_size(m-2, n-2)), j3(nt2::of_size(m-2, n-2))
    , j4(nt2::of_size(m-2, n-2)), jacob1(nt2::of_size(m-2, n-2)), jacob2(nt2::of_size(m-2, n-2))
    , jacob4(nt2::of_size(m-2, n-2)), sqrtdelta(nt2::of_size(m-2, n-2)), lambda(nt2::of_size(m-2, n-2,2))
    , res(nt2::of_size(m-2, n-2))
  {

    for(std::size_t j = 1; j <= N; ++j){
      for(std::size_t i = 1; i <= M; ++i){
        traj_y(i,j) = traj_x(i,j) = roll<T>(min,max);

      }
    }

  }

  void operator()()
  {
    j1 = (traj_x(nt2::_(2,M-1),nt2::_(3,N)) - traj_x(nt2::_(2,M-1),nt2::_(1,N-2)))/(2*dX);
    j2 = (traj_x(nt2::_(3,M),nt2::_(2,N-1)) - traj_x(nt2::_(1,M-2),nt2::_(2,N-1)))/(2*dY);
    j3 = (traj_y(nt2::_(2,M-1),nt2::_(3,N)) - traj_y(nt2::_(2,M-1),nt2::_(1,N-2)))/(2*dX);
    j4 = (traj_y(nt2::_(3,M),nt2::_(2,N-1)) - traj_y(nt2::_(1,M-2),nt2::_(2,N-1)))/(2*dY);

    jacob1 = nt2::sqr(j1) + nt2::sqr(j3);
    jacob2 = j1*j2 + j3*j4;
    jacob4 = nt2::sqr(j2) + nt2::sqr(j4);

    sqrtdelta = nt2::sqrt(nt2::sqr(jacob1+jacob4) - T(4)*(jacob1*jacob4-nt2::sqr(jacob2)));

    lambda(nt2::_,nt2::_,1) = T(0.5)*(jacob1 + jacob4 + sqrtdelta);
    lambda(nt2::_,nt2::_,2)= T(0.5)*(jacob1 + jacob4 - sqrtdelta);

    res= nt2::maximum(lambda,3);
  }

  void reset() {}

  std::size_t M;
  std::size_t N;
  T dX;
  T dY;
  nt2::table<T> traj_x;
  nt2::table<T> traj_y;

  nt2::table<T> j1,j2,j3,j4;
  nt2::table<T> jacob1, jacob2, jacob4;
  nt2::table<T> sqrtdelta;
  nt2::table<T> lambda;
  nt2::table<T> res;




};

#define X(i,j) traj_x[(i)+(j)*(M-2)]
#define Y(i,j) traj_y[(i)+(j)*(M-2)]
#define max(a,b)(a<b)? b: a
template<class T> struct Compute_scalar
{
  Compute_scalar(std::size_t m, std::size_t n, T const& min, T const& max )
    : M(m),N(n), dX(0.01), dY(0.01), traj_x(m*n), traj_y(m*n)
    , j1((m-2)* (n-2)), j2((m-2)* (n-2)), j3((m-2)* (n-2))
    , j4((m-2)* (n-2)), jacob1((m-2)* (n-2)), jacob2((m-2)* (n-2))
    , jacob4((m-2)* (n-2)), sqrtdelta((m-2)* (n-2)), lambda1((m-2)*(n-2)), lambda2((m-2)*(n-2))
    , res((m-2)* (n-2))
    {

      for(std::size_t i = 0; i < N * M; ++i){
        traj_y[i] = traj_x[i] = roll<T>(min,max);
      }


    }

  void operator()()
    {

      for(int j = 0, j_ = 0; j < N-2; ++j, j_+=(M-2)){
        for(int i = 0; i < M-2; ++i){
          j1[i+j_] = (X(i+1,j+2) - X(i+1,j))/(2*dX);
          j2[i+j_] = (X(i+2,j+1) - X(i,j+1))/(2*dY);
          j3[i+j_] = (Y(i+1,j+2) - Y(i+1,j))/(2*dX);
          j4[i+j_] = (Y(i+2,j+1) - Y(i,j+1))/(2*dY);

          jacob1[i+j_] = j1[i+j_]*j1[i+j_] + j3[i+j_]*j3[i+j_];
          jacob2[i+j_] = j1[i+j_]*j2[i+j_] + j3[i+j_]*j4[i+j_];
          jacob4[i+j_] = j2[i+j_]*j2[i+j_] + j4[i+j_]*j4[i+j_];

          sqrtdelta[i+j_] = std::sqrt((jacob1[i+j_]+jacob4[i+j_])*(jacob1[i+j_]+jacob4[i+j_]) - T(4)*(jacob1[i+j_]*jacob4[i+j_]-(jacob2[i+j_])*(jacob2[i+j_])));

          lambda1[i+j_] = T(0.5)*(jacob1[i+j_] + jacob4[i+j_] + sqrtdelta[i+j_]);
          lambda2[i+j_] = T(0.5)*(jacob1[i+j_] + jacob4[i+j_] - sqrtdelta[i+j_]);

          res[i+j_] = max(lambda1[i+j_], lambda2[i+j_]);
        }
      }

    }


  void reset() {}

  std::size_t M;
  std::size_t N;
  T dX;
  T dY;
  std::vector<T> traj_x;
  std::vector<T> traj_y;

  std::vector<T> j1,j2,j3,j4;
  std::vector<T> jacob1, jacob2, jacob4;
  std::vector<T> sqrtdelta;
  std::vector<T> lambda1;
  std::vector<T> lambda2;
  std::vector<T> res;




};

template<class T> void do_test_fluid()
{
  std::cout << "Size\ttable (c/e)\ttable (s)\tvector (c/e)\tvector (s)\tG(c/e)\tG(s)\n";

  for(int N=4;N<=2048;N*=2)
    //std::size_t N = 6;
  {
    std::cout.precision(3);
    std::cout << N*2*N << "\t";
    Compute<T> tt(N,2*N,-.28319, .28319);
    nt2::unit::benchmark_result<nt2::details::cycles_t> dv;
    nt2::unit::perform_benchmark( tt, 1., dv);
    nt2::unit::benchmark_result<double> tv;
    nt2::unit::perform_benchmark( tt, 1., tv);
    std::cout << std::scientific << dv.median/(double)(N*2*N) << "\t";
    std::cout << std::scientific << tv.median << "\t";

    Compute_scalar<T> vv(N,2*N,-.28319, .28319);
    nt2::unit::benchmark_result<nt2::details::cycles_t> dw;
    nt2::unit::perform_benchmark( vv, 1., dw);
    nt2::unit::benchmark_result<double> tw;
    nt2::unit::perform_benchmark( vv, 1., tw);
    std::cout << std::scientific << dw.median/(double)(N*N) << "\t";
    std::cout << std::scientific << tw.median << "\t";

    std::cout << std::fixed << (double)dw.median/dv.median << "\t";
    std::cout << std::fixed << (double)tw.median/tv.median << "\n";

  }
}


NT2_TEST_CASE_TPL( fluid, (float) (double))
{
  do_test_fluid<T>();
}
