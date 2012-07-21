/*******************************************************************************
 *         Copyright 2003 - 2012 LASMEA UMR 6602 CNRS/Univ. Clermont II
 *         Copyright 2009 - 2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/

#include <nt2/table.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/erf.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/tic.hpp>

template<class T>
void blackscholes ( T const&  price , T const& strike     , T const& rate
                  , T const&  time  , T const& volatility
                  , T&        call  , T& put
                  )
{
  T d1  = (nt2::log(price/strike) + (rate + (0.5f)*nt2::sqr(volatility)) * time)
        / (volatility * nt2::sqrt(time) * nt2::sqrt((2.f)));

  T d2 = d1 - volatility * nt2::sqrt(time) / nt2::sqrt((2.f));
  T d3 = (0.5f) * strike * nt2::exp(-rate * time);

  call =  price * (0.5f) * strike * (1.f + nt2::sqr( d1)) - d3 * (1.f + nt2::sqr( d2));
  put  = -price * (0.5f) * strike * (1.f + nt2::erf(-d1)) + d3 * (1.f + nt2::erf(-d2));
}

double call()
{
  typedef float T;
  nt2::table<T> price     = nt2::ones(nt2::of_size(128000), nt2::meta::as_<T>());
  nt2::table<T> strike    = nt2::ones(nt2::of_size(128000), nt2::meta::as_<T>());
  nt2::table<T> rate      = nt2::ones(nt2::of_size(128000), nt2::meta::as_<T>());
  nt2::table<T> time      = nt2::ones(nt2::of_size(128000), nt2::meta::as_<T>());
  nt2::table<T> volatility= nt2::ones(nt2::of_size(128000), nt2::meta::as_<T>());
  nt2::table<T> call      = nt2::ones(nt2::of_size(128000), nt2::meta::as_<T>());
  nt2::table<T> put       = nt2::ones(nt2::of_size(128000), nt2::meta::as_<T>());

  std::cout << "expression\n";
  double t(0);
  for(int k=0;k<100;++k)
  {
    nt2::tic();
    blackscholes( price, strike , rate , time , volatility
                , call , put
                );
    t += nt2::toc(false);
  }
  std::cout << t/100 << "\n";
  return t;
}

int main()
{
  typedef float T;
  double t(0),v(0);
  {
    std::vector<T> price     (128000);
    std::vector<T> strike    (128000);
    std::vector<T> rate      (128000);
    std::vector<T> time      (128000);
    std::vector<T> volatility(128000);
    std::vector<T> call      (128000);
    std::vector<T> put       (128000);

    std::fill(price.begin(),price.end(),1.);
    std::fill(strike.begin(),strike.end(),1.);
    std::fill(rate.begin(),rate.end(),1.);
    std::fill(time.begin(),time.end(),1.);
    std::fill(volatility.begin(),volatility.end(),1.);

    std::cout << "std::vector\n";
    for(int k=0;k<100;++k)
    {
      nt2::tic();
      for(std::size_t i=0;i<price.size();++i)
      blackscholes( price[i], strike[i] , rate[i] , time[i] , volatility[i]
                  , call[i] , put[i]
                  );
      t += nt2::toc(false);
    }
    std::cout << t/100 << "\n";
  }

  v = call();
  std::cout << "Speed-up: " << t/v << "\n";
}
