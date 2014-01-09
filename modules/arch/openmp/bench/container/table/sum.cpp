//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/unit/details/prng.hpp>
#include <nt2/sdk/bench/metric/cycles_per_element.hpp>
#include <nt2/sdk/bench/metric/speedup.hpp>
#include <nt2/sdk/bench/setup/repeat.hpp>
#include <nt2/sdk/bench/setup/arithmetic.hpp>
#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/stat/median.hpp>

#include <nt2/include/functions/sum.hpp>
#include <nt2/table.hpp>

using namespace nt2::bench;

//==============================================================================
// nt2::table based plus benchmark
//==============================================================================
template<typename T>
struct table_sum
{
  table_sum() {}

  template<typename Setup>
  table_sum ( Setup const& s )
              : size_(boost::fusion::at_c<1>(s)*boost::fusion::at_c<1>(s))
              , dim_(boost::fusion::at_c<0>(s))
              , a0(nt2::_2D ( boost::fusion::at_c<1>(s)
                            , boost::fusion::at_c<1>(s)
                            )
                  )
              , a1(nt2::_2D ( boost::fusion::at_c<1>(s)
                            , boost::fusion::at_c<1>(s)
                            )
                  )
  {
    nt2::roll(a1,-3.1415/4., 3.1415/4.);
  }

  void operator()()
  {
    a1  = nt2::sum ( a0, dim_ );
  }

  std::size_t size()   const { return size_;        }
  nt2::_2D    extent() const { return a0.extent();  }
  std::size_t dim()    const { return dim_;         }

  private:
  std::size_t size_,dim_;
  nt2::table<T> a0,a1;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, table_sum<T> const& p)
{
  return os << "(" << p.extent() << ") @ " << p.dim();
}

template<typename T>
std::ostream& operator<<(std::ostream& os, table_sum<T> const& p)
{
  return os << "(" << p.extent() << ") @ " << p.dim();
}

NT2_REGISTER_BENCHMARK_TPL( table_sum, (float)(double) )
{
  std::size_t mn = args("min" , 2   );
  std::size_t mx = args("max" , 2048);
  std::size_t s  = args("step", 2   );

  run_during_with< table_sum<T> > ( 1.
                                    , repeat( arithmetic(1,2)
                                            , geometric(mn,mx,s)
                                            )
                                    , cycles_per_element<stat::median_>()
                                    );
}
