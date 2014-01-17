//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/experiment.hpp>
#include <nt2/sdk/unit/details/prng.hpp>

#include <nt2/sdk/bench/metric/absolute_time.hpp>
#include <nt2/sdk/bench/metric/cycles_per_element.hpp>

#include <nt2/sdk/bench/protocol/max_iteration.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>

#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/setup/combination.hpp>
#include <nt2/sdk/bench/setup/constant.hpp>

#include <nt2/sdk/bench/stats/average.hpp>
#include <nt2/sdk/bench/stats/median.hpp>
#include <nt2/sdk/bench/stats/min.hpp>
#include <nt2/sdk/bench/stats/max.hpp>

#include <boost/simd/sdk/simd/pack.hpp>

#include <boost/simd/include/functions/max.hpp>
#include <boost/simd/include/functions/min.hpp>
#include <boost/simd/include/functions/minus.hpp>
#include <boost/simd/include/functions/selinc.hpp>
#include <boost/simd/include/functions/seldec.hpp>
#include <boost/simd/include/functions/if_zero_else_one.hpp>
#include <boost/simd/include/functions/adds.hpp>
#include <boost/simd/include/functions/is_less.hpp>
#include <boost/simd/include/functions/is_greater.hpp>
#include <boost/simd/include/functions/aligned_store.hpp>

#include <boost/simd/memory/allocator.hpp>

#include <boost/fusion/include/at.hpp>

#include <iostream>
using namespace nt2::bench;
using namespace nt2;

template<class Pixel>
BOOST_FORCEINLINE Pixel do_work(Pixel &bkg, const Pixel &fr, Pixel &var)
{
  Pixel diff_img, mul_img, zero=0;
  bkg = boost::simd::selinc( bkg < fr, boost::simd::seldec( bkg > fr
                                                          , bkg
                                                          )
                           );
  diff_img = boost::simd::max(bkg, fr) - boost::simd::min(bkg, fr);

  mul_img = boost::simd::adds(boost::simd::adds(diff_img,diff_img),diff_img);

  var = boost::simd::if_else( diff_img != zero, boost::simd::selinc( var < mul_img
                                                                   , boost::simd::seldec( var > mul_img
                                                                                        , var
                                                                                        )
                                                                   )
                            , var
                            );
  return boost::simd::if_zero_else_one( diff_img < var );
}

template<typename T> struct sigmadelta_simd
{
  template<typename Setup>
  sigmadelta_simd(Setup const& s)
                    :  nb_frames(boost::fusion::at_c<0>(s))
                    ,  height(boost::fusion::at_c<1>(s))
                    ,  width(boost::fusion::at_c<2>(s))
                    ,  size_(height*width)
  {
    image_variance.resize(size_);
    background_img.resize(size_);
    binary_label.resize(size_);
    frames.resize(nb_frames);

    for(int k=0; k<nb_frames; k++)
      frames[k].resize(size_);
    for(int k=0; k<nb_frames; k++)
    {
      for(int j=0; j<width; j++)
      {
        for(int i=0; i<height;i++)
        {
          if(i>(height/4) && i<(height/2) && j>((width/4)+k%10) && j<((width/2)+k%10))
            frames[k][i*width+j] = 255;
          else
            frames[k][i*width+j] = 0;
        }
      }
    }
    std::fill(image_variance.begin(), image_variance.end(), 1);
    background_img = frames[0];
    std::fill(binary_label.begin(), binary_label.end(), 0);
  }

  void operator()()
  {
    using boost::simd::pack;
    using boost::simd::aligned_load;
    using boost::simd::aligned_store;

    typedef pack<T> type;

    step_size = boost::simd::meta::cardinal_of<type>::value;
    aligned_sz = size_ & ~(step_size-1);
    for(std::size_t k=1; k<nb_frames; k++)
    {
      it         = 0;
      for(std::size_t m=aligned_sz; it != m; it += step_size)
      {
        type bkg(&background_img[it]);
        type fr(&frames[k][it]);
        type var(&image_variance[it]);
        aligned_store(do_work(bkg,fr,var),&binary_label[it]);
        aligned_store(var,&image_variance[it]);
      }
      for(std::size_t m=size_; it != m; it++)
      {
        binary_label[it] = do_work(background_img[it],frames[k][it], image_variance[it]);
      }
    }
  }

  friend std::ostream& operator<<(std::ostream& os, sigmadelta_simd<T> const& p)
  {
    return os << "(" << p.height << " x " << p.width << " @" << p.nb_frames << ")";
  }

  std::size_t size() const { return size_ * nb_frames; }

  private:
  std::size_t height;
  std::size_t width;
  std::size_t size_, aligned_sz, it, step_size;
  std::vector< std::vector<T, boost::simd::allocator<T> > > frames;
  std::vector<T, boost::simd::allocator<T> > image_variance, background_img, binary_label;
  std::size_t nb_frames;
};

NT2_REGISTER_BENCHMARK( sigmadelta_simd )
{

  std::size_t frame = args("frame", 5);
  std::size_t hmin = args("hmin", 32);
  std::size_t hmax = args("hmax", 128);
  std::size_t hstep = args("hstep", 2);
  std::size_t wmin = args("wmin", 32);
  std::size_t wmax = args("wmax", 128);
  std::size_t wstep = args("wstep", 2);

  run_during_with< sigmadelta_simd<nt2::uint8_t> > ( 1.
                                          , and_( constant( frame )
                                                , geometric(hmin,hmax,hstep)
                                                , geometric(wmin,wmax,wstep)
                                                )
                                          , cycles_per_element<stats::median_>()
                                          );
}
