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
#include <nt2/sdk/bench/metric/absolute_time.hpp>
#include <nt2/sdk/bench/metric/speedup.hpp>
#include <nt2/sdk/bench/setup/fixed.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/stats/median.hpp>
#include <nt2/sdk/bench/stats/min.hpp>

#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/table.hpp>

#include <vector>
#include <cmath>

using namespace nt2::bench;

//==============================================================================
// Basic C++ code using std vector and std math
//==============================================================================
struct raw_C
{
  raw_C ( std::size_t n = 1 ) : size_(n), a(n),b(n),y(n)
  {
    nt2::roll(a,0.,10.);
    nt2::roll(b,0.,10.);
  }

  void operator()()
  {
    for(std::size_t i = 0; i < size_; ++i)
    {
      double v = a[i] - b[i];
      y[i] = std::exp( (v * v) * 0.5 );
    }
  }

  std::size_t size() const { return size_; }

  friend std::ostream& operator<<(std::ostream& os, raw_C const& p)
  {
    return os << "(" << p.size_ << ")";
  }

  private:
  std::size_t size_;
  std::vector<double> a,b,y;
};

NT2_REGISTER_BENCHMARK( raw_C )
{
  std::size_t n = args("size", 2e3);

  run_during_with<raw_C>( 3., fixed(n*n)
                        , absolute_time<stats::median_>()
                        );
}

//==============================================================================
// Basic NT2 code using element-wise data access
//==============================================================================
struct per_element
{
  per_element ( std::size_t n = 1)
              : size_(n)
              , a(nt2::of_size(n,n)), b(nt2::of_size(n,n)), y(nt2::of_size(n,n))
  {
    nt2::roll(a,0.,10.);
    nt2::roll(b,0.,10.);
  }

  void operator()()
  {
    for(std::size_t j = 1; j <= size_; ++j)
    {
      for(std::size_t i = 1; i <= size_; ++i)
      {
        double v = a(i, j) - b(i, j);
        y(i, j) = std::exp( (v * v) * 0.5 );
      }
    }
  }

  std::size_t size() const { return size_*size_; }

  friend std::ostream& operator<<(std::ostream& os, per_element const& p)
  {
    return os << "(" << p.y.extent() << ")";
  }

  private:
  std::size_t size_;
  nt2::table<double,nt2::_2D> a,b,y;
};

NT2_REGISTER_BENCHMARK( per_element )
{
  std::size_t n = args("size", 2e3);

  run_during_with<per_element>( 3., fixed(n)
                              , absolute_time<stats::median_>()
                              , speedup < raw_C
                                        , absolute_time<stats::median_>
                                        >()
                              );
}

//==============================================================================
// Basic NT2 code using table operations
//==============================================================================
struct per_table
{
  per_table ( std::size_t n = 1)
            : size_(n)
            , a(nt2::of_size(n,n)), b(nt2::of_size(n,n)), y(nt2::of_size(n,n))
  {
    nt2::roll(a,0.,10.);
    nt2::roll(b,0.,10.);
  }

  void operator()()
  {
    y = exp(sqr(a - b) * 0.5);
  }

  std::size_t size() const { return size_*size_; }

  friend std::ostream& operator<<(std::ostream& os, per_table const& p)
  {
    return os << "(" << p.y.extent() << ")";
  }

  private:
  std::size_t size_;
  nt2::table<double,nt2::_2D> a,b,y;
};

NT2_REGISTER_BENCHMARK( per_table )
{
  std::size_t n = args("size", 2e3);

  run_during_with<per_table>( 3., fixed(n)
                            , absolute_time<stats::median_>()
                            , speedup < raw_C
                                      , absolute_time<stats::median_>
                                      >()
                            );
}

//==============================================================================
// Basic NT2 code using table operations per column
//==============================================================================
struct per_column
{
  per_column( std::size_t n = 1 )
            : size_(n)
            , a(nt2::of_size(n,n)), b(nt2::of_size(n,n)), y(nt2::of_size(n,n))
  {
    nt2::roll(a,0.,10.);
    nt2::roll(b,0.,10.);
  }

  void operator()()
  {
    using nt2::_;
    for(std::size_t j = 1; j <= size_; ++j)
    {
      y(_,j) = exp(sqr(a(_,j) - b(_,j)) * 0.5);
    }
  }

  std::size_t size() const { return size_*size_; }

  friend std::ostream& operator<<(std::ostream& os, per_column const& p)
  {
    return os << "(" << p.y.extent() << ")";
  }

  private:
  std::size_t size_;
  nt2::table<double,nt2::_2D> a,b,y;
};

NT2_REGISTER_BENCHMARK( per_column )
{
  std::size_t n = args("size", 2e3);

  run_during_with<per_column> ( 3., fixed(n)
                              , absolute_time<stats::median_>()
                              , speedup < raw_C
                                        , absolute_time<stats::median_>
                                        >()
                              );
}
