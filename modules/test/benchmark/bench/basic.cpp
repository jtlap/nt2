//==============================================================================
//         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/bench/benchmark.hpp>

NT2_EXPERIMENT(some_test, second)
{
  public:
  some_test (std::size_t n, double d = 2.5)
            : NT2_EXPERIMENT_CTOR( some_test, second, d ), a(n), b(n)
  {}

  void call() const
  {
    for(std::size_t i=0;i<size();++i) a[i] = b[i] + b[i]*b[i];
  }

  void reset() const {}

  std::size_t size() const { return a.size(); }

  private:
  mutable std::vector<float> a,b;
};

some_test const some_test_bench2(100);
some_test const some_test_bench3(1000);
some_test const some_test_bench4(10000);
some_test const some_test_bench5(100000);
some_test const some_test_bench6(1000000);
