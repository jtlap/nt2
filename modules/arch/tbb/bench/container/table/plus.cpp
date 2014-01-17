//==============================================================================
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/unit/details/prng.hpp>
#include <nt2/sdk/bench/metric/cycles_per_element.hpp>
#include <nt2/sdk/bench/metric/speedup.hpp>
#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/stats/median.hpp>

#include <nt2/include/functions/plus.hpp>
#include <nt2/table.hpp>

#include <vector>
#include <cmath>

using nt2::table;
using nt2::of_size;
using namespace nt2::bench;

//==============================================================================
// std::vector based plus benchmark
//==============================================================================
template<typename T>
struct vector_plus
{
  vector_plus() {}
  vector_plus( std::size_t n ) : size_(n*n), a(size_),b(size_),y(size_)
  {
    nt2::roll(a,-10.,10.);
    nt2::roll(b,-10.,10.);
  }

  void operator()()
  {
    for(std::size_t i = 0; i < size_; ++i)
    {
      y[i] = a[i] + b[i];
    }
  }

  std::size_t size() const { return size_; }

  friend std::ostream& operator<<(std::ostream& os, vector_plus<T> const& p)
  {
    return os << "(" << p.size_ << ")";
  }

  private:
  std::size_t size_;
  std::vector<T> a,b,y;
};

NT2_REGISTER_BENCHMARK_TPL( vector_plus, (float)(double) )
{
  std::size_t mn = args("min", 64);
  std::size_t mx = args("max", 1024);
  std::size_t s  = args("step", 4);

  run_during_with< vector_plus<T> >( 1.
                                    , geometric(mn,mx,s)
                                    , cycles_per_element<stats::median_>()
                                    );
}

//==============================================================================
// nt2::table based plus benchmark
//==============================================================================
template<typename T>
struct table_plus
{
  table_plus() {}
  table_plus ( std::size_t n )
              : size_(n*n)
              , a(nt2::_2D(n,n)),b(nt2::_2D(n,n)),y(nt2::_2D(n,n))
  {
    nt2::roll(a,-10.,10.);
    nt2::roll(b,-10.,10.);
  }

  void operator()() { y = a + b; }

  std::size_t size() const { return size_; }

  friend std::ostream& operator<<(std::ostream& os, table_plus<T> const& p)
  {
    return os << p.y.extent();
  }

  private:
  std::size_t size_;
  nt2::table<T,nt2::_2D> a,b,y;
};


NT2_REGISTER_BENCHMARK_TPL( table_plus, (float)(double) )
{
  std::size_t mn = args("min", 64);
  std::size_t mx = args("max", 1024);
  std::size_t s  = args("step", 4);

  run_during_with< table_plus<T> >( 1.
                                  , geometric(mn,mx,s)
                                  , cycles_per_element<stats::median_>()
                                  , speedup < vector_plus<T>
                                            , cycles_per_element<stats::median_>
                                            >()
                                  );
}
