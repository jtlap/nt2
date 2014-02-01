//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <boost/fusion/include/at.hpp>
#include <iostream>

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/metric/cycles_per_element.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/setup/combination.hpp>
#include <nt2/sdk/bench/setup/constant.hpp>
#include <nt2/sdk/bench/stats/median.hpp>

using namespace nt2::bench;

template<typename T> struct sigmadelta_scalar
{
  template<typename Setup>
  sigmadelta_scalar(Setup const& s)
                    :  height(boost::fusion::at_c<1>(s))
                    ,  width(boost::fusion::at_c<2>(s))
                    ,  size_(height*width)
                    ,  nb_frames(boost::fusion::at_c<0>(s))
  {
    variance_img.resize(size_);
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
    std::fill(variance_img.begin(), variance_img.end(), 1);
    background_img = frames[0];
    std::fill(binary_label.begin(), binary_label.end(), 0);
  }

  void operator()()
  {
    unsigned char d,mul;
    for(int k=1; k<nb_frames; k++)
    {
      for(int i=0; i < size_; i++)
      {
        if(background_img[i] < frames[k][i])
        {
          background_img[i] += 1;
        }
        else
        {
          if(background_img[i] > frames[k][i])
          {
            background_img[i] -= 1;
          }
        }

        d = abs(background_img[i]-frames[k][i]);
        mul = sigma * d;
        if(d != 0)
        {
          if(variance_img[i] < mul)
          {
            variance_img[i] += 1;
          }
          else
          {
            if(variance_img[i] > mul)
            {
              variance_img[i] -= 1;
            }
          }
        }
        if(d < variance_img[i])
        {
          binary_label[i] = 0;
        }
        else
        {
          binary_label[i] = 1;
        }
      }
    }
  }

  friend std::ostream& operator<<(std::ostream& os, sigmadelta_scalar<T> const& p)
  {
    return os << "(" << p.height << " x " << p.width << " @" << p.nb_frames << ")";
  }

  std::size_t size() const { return size_ * nb_frames; }

  private:
  std::size_t height;
  std::size_t width;
  std::size_t size_;
  std::vector<std::vector<T> > frames;
  std::vector<T>  variance_img, background_img, diff_img, binary_label;
  static const T sigma=3;
  int nb_frames;
};

NT2_REGISTER_BENCHMARK( sigmadelta_scalar )
{
  std::size_t frame = args("frame",  5);
  std::size_t hmin  = args("hmin",  32);
  std::size_t hmax  = args("hmax", 128);
  std::size_t hstep = args("hstep",  2);
  std::size_t wmin  = args("wmin",  32);
  std::size_t wmax  = args("wmax", 128);
  std::size_t wstep = args("wstep",  2);

  run_during_with< sigmadelta_scalar<nt2::uint8_t> > ( 1.
                                                     , and_( constant( frame )
                                                           , geometric(hmin,hmax,hstep)
                                                           , geometric(wmin,wmax,wstep)
                                                           )
                                                     , cycles_per_element<stats::median_>()
                                                     );
}

