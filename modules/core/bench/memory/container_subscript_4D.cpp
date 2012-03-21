/*******************************************************************************
 *         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#define NT2_UNIT_MODULE "nt2 container via 4D subscript bench"

#include <nt2/sdk/memory/container.hpp>
#include <nt2/core/functions/of_size.hpp>
#include <nt2/core/container/table/semantic.hpp>
#include <nt2/core/utility/position/alignment.hpp>

#include <iostream>
#include <nt2/sdk/unit/module.hpp>
#include <nt2/sdk/unit/details/helpers.hpp>
#include <nt2/sdk/unit/perform_benchmark.hpp>
#include <boost/fusion/include/vector_tie.hpp>

template<class T> struct container_4D_test
{
  typedef nt2::memory::container<T,nt2::settings()>  buffer_t;

  container_4D_test ( std::size_t s0 )
                    : data(boost::fusion::vector_tie(s0,s0,s0,s0))
                    , data2(boost::fusion::vector_tie(s0,s0,s0,s0))
                    , s0_(s0)
  {}

  void operator()()
  {
    using boost::fusion::vector_tie;
    for(std::size_t l = 1; l <= s0_; ++l)
      for(std::size_t k = 1; k <= s0_; ++k)
        for(std::size_t j = 1; j <= s0_; ++j)
          for(std::size_t i = 1; i <= s0_; ++i)
            data(nt2::as_aligned( vector_tie(i,j,k,l)))
          = data2(nt2::as_aligned( vector_tie(i,j,k,l)));
  }

  buffer_t     data,data2;
  std::size_t  s0_;
};

template<class T> struct std_4D_test
{
  std_4D_test(std::size_t n) : s0_(n),data(n*n*n*n),data2(n*n*n*n) {}

  void operator()()
  {
    for(std::size_t l = 0; l < s0_; ++l)
      for(std::size_t k = 0; k < s0_; ++k)
        for(std::size_t j = 0; j < s0_; ++j)
          for(std::size_t i = 0; i < s0_; ++i)
            data[i+s0_*(j+s0_*(k+s0_*l))] = data2[i+s0_*(j+s0_*(k+s0_*l))];
  }

  std::size_t  s0_;
  std::vector<T,boost::simd::memory::allocator<T> > data,data2;
};

NT2_TEST_CASE_TPL( buffer_access_4D, NT2_TYPES )
{
  std::cout << "Size\tnt2::container\tstd::vector\tover\tover \%\n";
  std::cout.precision(2);

  for(int i=1;i<64;i*=2)
  {
    container_4D_test<T>  w(i);
    std_4D_test<T>        y(i);

    nt2::unit::benchmark_result<nt2::details::cycles_t> dy;
    nt2::unit::perform_benchmark( y, 1., dy);
    double f = dy.median / 2.;

    nt2::unit::benchmark_result<nt2::details::cycles_t> dw;
    nt2::unit::perform_benchmark( w, 1., dw);
    double d = dw.median / 2.;

    std::cout << i << "^4\t"
              << std::scientific << d/(i*i*i*i) << "\t"
              << std::scientific << f/(i*i*i*i) << "\t"
              << std::fixed << (d-f)/(i*i*i*i) << "\t"
              << std::fixed << ((d-f)/f)*100 << "\t"
              << "\n";
  }
}
