//==============================================================================
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================

#include <nt2/table.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/adds.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/selinc.hpp>
#include <nt2/include/functions/seldec.hpp>
#include <nt2/include/functions/if_zero_else_one.hpp>
#include <nt2/include/functions/is_less.hpp>
#include <nt2/include/functions/is_greater.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <boost/fusion/include/at.hpp>
#include <iostream>

#include <nt2/sdk/bench/benchmark.hpp>
#include <nt2/sdk/bench/metric/fps.hpp>
#include <nt2/sdk/bench/metric/cycles_per_element.hpp>
#include <nt2/sdk/bench/protocol/max_duration.hpp>
#include <nt2/sdk/bench/setup/geometric.hpp>
#include <nt2/sdk/bench/setup/combination.hpp>
#include <nt2/sdk/bench/setup/constant.hpp>
#include <nt2/sdk/bench/stats/median.hpp>

using namespace nt2::bench;
using namespace nt2;
template<class Pixel>
BOOST_FORCEINLINE void do_work(Pixel &bkg, const Pixel &fr, Pixel &var, Pixel &diff_img, Pixel &mul_img, Pixel &out)
{
  typename Pixel::value_type zero = 0;

  bkg = nt2::selinc( bkg < fr, nt2::seldec( bkg > fr
                                          , bkg
                                          )
                   );
  diff_img = nt2::max(bkg, fr) - nt2::min(bkg, fr);

  mul_img = nt2::adds(nt2::adds(diff_img,diff_img),diff_img);

  var = nt2::if_else( diff_img != zero, nt2::selinc( var < mul_img
                                                   , nt2::seldec( var > mul_img
                                                                , var
                                                                )
                                                   )
                    , var
                    );
  out = nt2::if_zero_else_one( diff_img < var );
}

template<typename T> struct sigmadelta_nt2
{
  template<typename Setup>
  sigmadelta_nt2(Setup const& s)
                    :  height(boost::fusion::at_c<1>(s))
                    ,  width(boost::fusion::at_c<2>(s))
                    ,  size_(height*width)
                    ,  nb_frames(boost::fusion::at_c<0>(s))
  {
    frames.resize(nb_frames);
    image_variance.resize(nt2::of_size(height,width));
    diff_img.resize(nt2::of_size(height,width));
    mul_img.resize(nt2::of_size(height,width));
    background_img.resize(nt2::of_size(height,width));
    binary_label.resize(nt2::of_size(height,width));

    for(std::size_t k=0; k<nb_frames; k++)
      frames[k].resize(nt2::of_size(height,width));

    for(std::size_t k=0; k<nb_frames; k++)
    {
      for(std::size_t j=1; j<=width; j++)
      {
        for(std::size_t i=1; i<=height;i++)
        {
          if(i-1>(height/4) && i-1<(height/2) && j-1>((width/4)+k%10) && j-1<((width/2)+k%10))
            frames[k](i,j) = 255;
          else
            frames[k](i,j) = 0;
        }
      }
    }
    image_variance = ones(nt2::of_size(height,width),nt2::meta::as_<T>());
    for (std::size_t i=1;i<=height;i++)
      for (std::size_t j=1;j<=width;j++)
        background_img(i,j) = frames[0](i,j);

    binary_label = zeros(nt2::of_size(height,width),nt2::meta::as_<T>());
  }

  void operator()()
  {
    for(std::size_t k=1; k<nb_frames; k++)
    {
      do_work(background_img, frames[k], image_variance, diff_img, mul_img, binary_label);
    }
  }

  friend std::ostream& operator<<(std::ostream& os, sigmadelta_nt2<T> const& p)
  {
    return os << "(" << p.height << " x " << p.width << " @" << p.nb_frames << ")";
  }

  std::size_t size() const { return size_ * nb_frames; }
  std::size_t frame_count()  const { return nb_frames; }

private:
  std::size_t height;
  std::size_t width;
  std::size_t size_;
  std::vector<table<T> > frames;
  nt2::table<T> image_variance, background_img, binary_label, mul_img, diff_img;
  std::size_t nb_frames;
};

NT2_REGISTER_BENCHMARK( sigmadelta_nt2 )
{
  std::size_t frame = args("frame", 5);
  std::size_t hmin = args("hmin", 32);
  std::size_t hmax = args("hmax", 128);
  std::size_t hstep = args("hstep", 2);
  std::size_t wmin = args("wmin", 32);
  std::size_t wmax = args("wmax", 128);
  std::size_t wstep = args("wstep", 2);

  run_during_with< sigmadelta_nt2<nt2::uint8_t> > ( 1.
                                                  , and_( constant( frame )
                                                        , geometric(hmin,hmax,hstep)
                                                        , geometric(wmin,wmax,wstep)
                                                        )
                                                  , cycles_per_element<stats::median_>()
                                                  , fps<stats::median_>()
                                                  );
}
