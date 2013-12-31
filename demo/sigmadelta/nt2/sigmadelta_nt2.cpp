//==============================================================================
// Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
// Copyright 2009 - 2013 LRI UMR 8623 CNRS/Univ Paris Sud XI
// Copyright 2012 - 2013 MetaScale SAS
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
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

#include <nt2/sdk/bench/benchmark.hpp>
#include <iostream>
#include <string>

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


template<typename T> NT2_EXPERIMENT(sigmadelta_nt2)
{
public:

  sigmadelta_nt2( std::size_t const& h, std::size_t const& w, std::size_t const& seq)
  : NT2_EXPERIMENT_CTOR(1., "cycles/elements")
  , height(h), width(w), size(h*w), nb_frames(seq)
  {
    frames.resize(seq);
    variance_img.resize(nt2::of_size(h,w));
    diff_img.resize(nt2::of_size(h,w));
    mul_img.resize(nt2::of_size(h,w));
    background_img.resize(nt2::of_size(h,w));
    etiquette_binaire.resize(nt2::of_size(h,w));
    for(std::size_t k=0; k<nb_frames; k++)
      frames[k].resize(nt2::of_size(h,w));

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
    variance_img = ones(nt2::of_size(size),nt2::meta::as_<T>());
    for (std::size_t i=1;i<=height;i++)
      for (std::size_t j=1;j<=width;j++)
        background_img(i,j) = frames[0](i,j);
    etiquette_binaire = zeros(nt2::of_size(height,width),nt2::meta::as_<T>());
  }

  virtual void run() const
  {
    for(std::size_t k=1; k<nb_frames; k++)
    {
      do_work(background_img, frames[k], variance_img, diff_img, mul_img, etiquette_binaire );
    }
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.first/double(height*width)/nb_frames;
  }

  virtual void info(std::ostream& os) const { os << height << "x" << width;}

  virtual void reset() const
  {
    for (std::size_t i=1;i<=height;i++)
      for (std::size_t j=1;j<=width;j++)
        background_img(i,j) = frames[0](i,j);

    etiquette_binaire = zeros(nt2::of_size(height,width),nt2::meta::as_<T>());
    variance_img = ones(nt2::of_size(height,width),nt2::meta::as_<T>());
  }

  std::size_t height;
  std::size_t width;
  std::size_t size;
  mutable nt2::table<T> variance_img, background_img, etiquette_binaire, mul_img, diff_img;
  mutable std::vector<table<T> > frames;
  static const T N=3;
  mutable std::size_t step_size;
  std::size_t nb_frames;
};

NT2_RUN_EXPERIMENT_TPL( sigmadelta_nt2, (nt2::uint8_t), (32,32,100));
NT2_RUN_EXPERIMENT_TPL( sigmadelta_nt2, (nt2::uint8_t), (64,64,100));
NT2_RUN_EXPERIMENT_TPL( sigmadelta_nt2, (nt2::uint8_t), (256,256,100));
NT2_RUN_EXPERIMENT_TPL( sigmadelta_nt2, (nt2::uint8_t), (512,512,100));
NT2_RUN_EXPERIMENT_TPL( sigmadelta_nt2, (nt2::uint8_t), (2048,2048,100));
NT2_RUN_EXPERIMENT_TPL( sigmadelta_nt2, (nt2::uint8_t), (4096,4096,100));
