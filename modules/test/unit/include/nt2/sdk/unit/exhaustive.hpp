//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2013        MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_UNIT_EXHAUSTIVE_HPP_INCLUDED
#define NT2_SDK_UNIT_EXHAUSTIVE_HPP_INCLUDED

#include <nt2/include/functions/load.hpp>
#include <nt2/include/functions/extract.hpp>
#include <nt2/include/functions/is_invalid.hpp>
#include <nt2/include/functions/successor.hpp>
#include <nt2/include/functions/ulpdist.hpp>
#include <nt2/include/constants/valmin.hpp>
#include <nt2/include/functions/iround.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/ilog2.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/constants/nan.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <nt2/sdk/meta/type_id.hpp>
#include <iostream>
#include <iomanip>
#include <cstdio>

#define NT2_ASSERTS_AS_TRAP
#include <nt2/sdk/error/assert_as_trap.hpp>

namespace nt2
{
  /*!
    @brief Exhaustive precision test for single precision driver

    Perform a ULP test on every representable single precision value
    in a given interval. Results are reported using a bucket histogram that
    gives hint on how many values fall in a given range of ULPs,
    the smallest and greatest inputs in the chosen range
    leading to this precision and  the result from this minimum input
    against the awaited result.

    @par Note:
    Currently this function is designed to take care of single precision only as
    running such a test on double precision values take an absurd amount of time.

    @tparam Type          Data type used for computation
    @param  mini Lower    bound of the test interval
    @param  maxi Upper    bound of the test interval
    @param  test_f        Function to test
    @param  reference_f   Reference function to compare to

    ****************************************************************************
    @par How to use it :

    0) write a standard main file (with argc and argv parameters if you intend using step 3o)

    1) include the right files: nt2/sdk/unit/exhaustive.hpp is mandatory

    2) define a functor against which the nt2 functor will be tested

    3) provide defaults for mini and maxi values for the tested range

    3o) get the mini and maxi values if they are command line provided (optionnal)

    4) call the test with the above described parameters

    5) return 0;

    ****************************************************************************
    Here is a full example for nt2:log testing using available simd and float
    ****************************************************************************
    @code
    #include <nt2/sdk/unit/exhaustive.hpp>
    #include <nt2/include/functions/log.hpp>

    #include <boost/simd/sdk/simd/native.hpp>
    #include <nt2/include/constants/zero.hpp>
    #include <nt2/include/constants/valmax.hpp>
    #include <cmath>

    struct std_log
    {
      float operator()(float x) const
      {
        return float(std::log(double(x)));
      }
    };

    int main(int argc, char* argv[])
    {
      typedef BOOST_SIMD_DEFAULT_EXTENSION             ext_t;    //simd extension to be tested
      typedef boost::simd::native<float,ext_t>           n_t;    //type to be tested
      float mini = nt2::Zero<float>();                           //default min value
      float maxi = nt2::Valmax<float>();                         //default max value
      if(argc >= 2) mini = std::atof(argv[1]);                   //do we override default for mini ?
      if(argc >= 3) maxi = std::atof(argv[2]);                   //do we override default for maxi ?

      nt2::exhaustive_test<n_t> (mini                            //call the test
                               , maxi
                               , nt2::functor<nt2::tag::log_>()
                               , std_log()
                               );

      return 0;                                                  //that's it
    }
    @endcode

  **/


  template<typename Type, typename TestF, typename RefF> inline
  void exhaustive_test(float mini, float maxi, TestF test_f, RefF reference_f)
  {
    typedef Type                                                    n_t;
    typedef typename boost::dispatch::meta::as_integer<Type>::type  in_t;

    const nt2::uint32_t M = 128;
    const nt2::uint32_t N = boost::simd::meta::cardinal_of<n_t>::value;
    const in_t vN = nt2::splat<in_t>(N);

    float a[N];
    float maxin[M+2];
    float minin[M+2];
    float minref[M+2];
    float minval[M+2];
    bool  hit[M+2];
    nt2::uint32_t histo[M+2];

    for(std::size_t i = 0; i < M+2; i++)
    {
      histo[i] = 0;
      minval[i] = nt2::Nan<float>();
      minin[i]  = nt2::Valmin<float>();
      maxin[i]  = nt2::Valmax<float>();
      hit[i] =  false;
    }

    // Fill up the reference SIMD register data
    a[0] = mini;
    for(std::size_t i = 1; i < N; i++)
      a[i] = nt2::successor(a[i-1], 1);

    n_t a0 = nt2::load<n_t>(&a[0],0);

    nt2::uint32_t k = 0, j = 0;

    std::cout << "Exhaustive test for: " << nt2::type_id(test_f)      << "\n"
              << "             versus: " << nt2::type_id(reference_f) << "\n"
              << "             With T: " << nt2::type_id<Type>()      << "\n"
              << "    in the interval: [" << mini << ",  " << maxi << "]" << "\n";
    std::cout << std::endl;
    std::cout << "[" << std::flush;

    while( nt2::extract(a0,N-1) < maxi )
    {
      n_t z = test_f(a0);

      for(std::size_t i = 0; i < N; i++)
      {
        float v = reference_f(nt2::extract(a0,i));

        float sz = nt2::extract(z,i);
        double u = nt2::ulpdist(v, sz)*2.0+1.0;

        if(nt2::is_invalid(u))
        {
          ++histo[M+1];
          if (!hit[M+1])
          {
            maxin [M+1] = minin [M+1] = nt2::extract(a0,i);
            minref[M+1] = v;
            minval[M+1] = nt2::extract(z,i);
            hit[M+1] = true;
          }
          else
          {
            maxin [M+1] = nt2::extract(a0,i);
          }
        }
        else
        {
          int p = nt2::min(int(M), int(nt2::ilog2(nt2::iround(u))));
          if (!hit[p])
          {
            maxin [p] = minin [p] = nt2::extract(a0,i);
            minref[p] = v;
            minval[p] = nt2::extract(z,i);
            hit[p] = true;
          }
          else
          {
            maxin [p] = nt2::extract(a0,i);
          }
          ++histo[p];
        }

        ++k;
        if (k%100000000 == 0)
        {
          if (k%1000000000 == 0)
            std::cout << "*" << std::flush;
          else
            std::cout << "." << std::flush;

          ++j;
          if (j == 80)
          {
            std::cout << std::endl;
            j = 0;
          }
        }
      }

      a0 = nt2::successor(a0, vN);
    }

    std::cout << "]" << std::endl;
    std::cout << k << " values computed.\n";

    double d = 1;
    for(std::size_t i = 0; i < M+1; i++, d*= 2.0)
    {
      if(histo[i])
      {
        printf("%10u values (%.2f%%)\twithin %1.1f ULPs.\t"
              , histo[i], (histo[i]*100.0/k), (d < 2 ? 0 : d/4)
              );
        if(i)
          std::cout << std::scientific << std::setprecision(7)
                    << "All samples values are in = [" << minin[i] << ",  "<< maxin[i] << "]"
                    << " Example: "<< minin[i] << " returns " << minval[i]
                    << " instead of " << minref[i];
        std::cout << std::endl;
      }
    }

    if( histo[M+1])
    {
        printf("%10u values (%.2f%%)\twith invalid result.\t"
              , histo[M+1], (histo[M+1]*100.0/k)
              );
        std::cout << std::scientific << std::setprecision(7)
                  << "All samples value in = [" << minin[M+1] << ",  "<< maxin[M+1] << "]"
                  << " Example: "<< minin[M+1] << " returns " << minval[M+1]
                  << " instead of " << minref[M+1]
                  << std::endl;

    }
  }
}

#endif
