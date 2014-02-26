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
#include <nt2/sdk/bench/setup/combination.hpp>
#include <nt2/sdk/bench/protocol/until.hpp>
#include <nt2/sdk/bench/stats/median.hpp>

#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/table.hpp>

#include <vector>
#include <cmath>

using nt2::table;
using nt2::of_size;
using namespace nt2::bench;

//==============================================================================
// std::vector based 1D subscript benchmark
//==============================================================================
template<typename T>
struct vector_subscript1D
{
  vector_subscript1D( std::size_t n = 0 ) : size_(n), a(size_),b(size_)
  {
    nt2::roll(b,-10.,10.);
  }

  void operator()()
  {
    for(std::size_t i=0; i<size_; ++i) a[i] = b[i];
  }

  std::size_t size() const { return size_; }

  private:
  std::size_t size_;
  std::vector<T> a,b;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, vector_subscript1D<T> const& p)
{
  return os << "(" << p.size() << ")";
}

NT2_REGISTER_BENCHMARK_TPL( vector_subscript1D, (float)(double) )
{
  std::size_t mn = args("min1D" , 2);
  std::size_t mx = args("max1D" , 4096);
  std::size_t s  = args("step1D", 2);
  std::size_t i = args("iteration", 1000);
  std::size_t d = args("duration" , 1.);

  run_until_with< vector_subscript1D<T> > ( d, i
                                          , geometric(mn,mx,s)
                                          , cycles_per_element<stats::median_>()
                                          );
}

//==============================================================================
// std::vector based 2D subscript benchmark
//==============================================================================
template<typename T>
struct vector_subscript2D
{
  vector_subscript2D() {}

  template<typename Args>
  vector_subscript2D( Args const& args )
                    : d0_( boost::fusion::at_c<0>(args) )
                    , d1_( boost::fusion::at_c<1>(args) )
                    , a(d0_*d1_),b(d0_*d1_)
  {
    nt2::roll(b,-10.,10.);
  }

  void operator()()
  {
    for(std::size_t j=0; j<d1_; ++j)
      for(std::size_t i=0; i<d0_; ++i)
        a[i+j*d0_] = b[i+j*d0_];
  }

  std::size_t size() const { return d0_*d1_; }
  std::size_t d0()   const { return d0_; }
  std::size_t d1()   const { return d1_; }

  private:
  std::size_t d0_,d1_;
  std::vector<T> a,b;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, vector_subscript2D<T> const& p)
{
  return os << "(" << p.d0() << " x " << p.d1() << ")";
}

NT2_REGISTER_BENCHMARK_TPL( vector_subscript2D, (float)(double) )
{
  std::size_t mn = args("min2D" , 2);
  std::size_t mx = args("max2D" , 4096);
  std::size_t s  = args("step2D", 2);
  std::size_t i = args("iteration", 1000);
  std::size_t d = args("duration" , 1.);

  run_until_with< vector_subscript2D<T> > ( d, i
                                          , and_( geometric(mn,mx,s)
                                                , geometric(mn,mx,s)
                                                )
                                          , cycles_per_element<stats::median_>()
                                          );
}

//==============================================================================
// nt2::table based 1D subscript benchmark
//==============================================================================
template<typename T>
struct table_subscript1D
{
  table_subscript1D ( std::size_t n = 0 )
                    : size_(n)
                    , a(nt2::of_size(size_)),b(nt2::of_size(size_))
  {
    nt2::roll(b,-10.,10.);
  }

  void operator()()
  {
    for(std::size_t i=1; i<=size_; ++i) a(i) = b(i);
  }

  std::size_t size()   const { return size_; }
  nt2::_1D    extent() const { return a.extent(); }

  private:
  std::size_t size_;
  nt2::table<T> a,b;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, table_subscript1D<T> const& p)
{
  return os << p.extent();
}

NT2_REGISTER_BENCHMARK_TPL( table_subscript1D, (float)(double) )
{
  std::size_t mn = args("min1D" , 2);
  std::size_t mx = args("max1D" , 4096);
  std::size_t s  = args("step1D", 2);
  std::size_t i = args("iteration", 1000);
  std::size_t d = args("duration" , 1.);

  run_until_with< table_subscript1D<T> >( d, i
                                        , geometric(mn,mx,s)
                                        , cycles_per_element<stats::median_>()
                                        , speedup < vector_subscript1D<T>
                                                  , cycles_per_element<stats::median_>
                                                  >()
                                        );
}

//==============================================================================
// nt2::table based 2D subscript benchmark
//==============================================================================
template<typename T>
struct table_subscript2D
{
  table_subscript2D() {}

  template<typename Args>
  table_subscript2D( Args const& args )
                    : d0_( boost::fusion::at_c<0>(args) )
                    , d1_( boost::fusion::at_c<1>(args) )
                    , a(nt2::of_size(d0_,d1_)),b(nt2::of_size(d0_,d1_))
  {
    nt2::roll(b,-10.,10.);
  }

  void operator()()
  {
    for(std::size_t j=1; j<=d1_; ++j)
      for(std::size_t i=1; i<=d0_; ++i)
        a(i,j) = b(i,j);
  }

  std::size_t size()    const { return d0_*d1_; }
  nt2::_2D    extent()  const { return a.extent(); }

  friend std::ostream& operator<<(std::ostream& os, table_subscript2D<T> const& p)
  {
    return os << p.a.extent();
  }

  private:
  std::size_t d0_,d1_;
  nt2::table<T> a,b;
};

NT2_REGISTER_BENCHMARK_TPL( table_subscript2D, (float)(double) )
{
  std::size_t mn = args("min2D" , 2);
  std::size_t mx = args("max2D" , 4096);
  std::size_t s  = args("step2D", 2);
  std::size_t i = args("iteration", 1000);
  std::size_t d = args("duration" , 1.);

  run_until_with< table_subscript2D<T> >( d, i
                                        , and_( geometric(mn,mx,s)
                                              , geometric(mn,mx,s)
                                              )
                                        , cycles_per_element<stats::median_>()
                                        , speedup < vector_subscript2D<T>
                                                  , cycles_per_element<stats::median_>
                                                  >()
                                        );
}
