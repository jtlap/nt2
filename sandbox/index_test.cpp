/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container fluctus"

#include <nt2/core/container/table/table.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/toolbox/operator/operator.hpp>
#include <nt2/include/functions/function.hpp>
#include <nt2/include/functions/sum.hpp>

#include <nt2/sdk/timing/now.hpp>
#include <nt2/sdk/unit/details/helpers.hpp>
#include <nt2/sdk/unit/perform_benchmark.hpp>
//#include <nt2/sdk/unit/module.hpp>

#include <nt2/table.hpp>

template<class T> struct Compute_FTLE
{
  Compute_FTLE(std::size_t m, std::size_t n, T const& min, T const& max )
    : M(m),N(n), dX(0.01), dY(0.01), traj_x(nt2::of_size(m,n)), traj_y(nt2::of_size(m,n)), lambda(nt2::of_size(m-2, n-2,2))
  {

    for(std::size_t j = 1; j <= N; ++j)
        for(std::size_t i = 1; i <= M; ++i)
            traj_y(i,j) = traj_x(i,j) = roll<T>(min,max);;

  }

  void reset() {}

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

    FTLE= nt2::maximum(lambda,3);
  }

  std::size_t M;
  std::size_t N;
  T dX;
  T dY;
  nt2::table<T> traj_x;
  nt2::table<T> traj_y;
  nt2::table<T> lambda;

  nt2::table<T> j1,j2,j3,j4;
  nt2::table<T> jacob1, jacob2, jacob4;
  nt2::table<T> sqrtdelta;
  nt2::table<T> FTLE;




};

template<class T> void do_test_fluctus()
{
  std::cout << "Size\ttable (c/e)\ttable (s)\n";

//  for(int N=4;N<=64;N*=2)
  std::size_t N = 6;
  {
    std::cout.precision(3);
    std::cout << N*2*N << "\t";
    Compute_FTLE<T> tt(N,2*N,-.28319, .28319);
    nt2::unit::benchmark_result<nt2::details::cycles_t> dv;
    nt2::unit::perform_benchmark( tt, 1., dv);
    nt2::unit::benchmark_result<double> tv;
    nt2::unit::perform_benchmark( tt, 1., tv);
    std::cout << std::scientific << dv.median/(double)(N*2*N) << "\t";
    std::cout << std::scientific << tv.median << "\n";

  }
}

int main()
{
  do_test_fluctus<float>();
}
