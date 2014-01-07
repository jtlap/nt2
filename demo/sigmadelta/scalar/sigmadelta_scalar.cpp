//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <stdlib.h>
#include <nt2/sdk/bench/benchmark.hpp>
#include <iostream>

using namespace nt2;

template<typename T>
NT2_EXPERIMENT(sigmadelta_scalar)
{
   public :
      sigmadelta_scalar(int h, int w, int seq)
      : NT2_EXPERIMENT_CTOR(1,"cycles/element"),
      height(h), width(w), size(h*w), nb_frames(seq)
  {
    frames.resize(seq);
    variance_img.resize(size);
    background_img.resize(size);
    etiquette_binaire.resize(size);
    for(int k=0; k<nb_frames; k++)
      frames[k].resize(size);
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
    std::fill(etiquette_binaire.begin(), etiquette_binaire.end(), 0);
  }

  BOOST_FORCEINLINE virtual void run() const
  {
    unsigned char d,mul;

    for(int k=1; k<nb_frames; k++)
    {
      for(int i=0; i < size; i++)
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
        mul = N * d;
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
          etiquette_binaire[i] = 0;
        }
        else
        {
          etiquette_binaire[i] = 1;
        }
      }
    }
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.first/double(height*width)/nb_frames;
  }

  virtual void info(std::ostream& os) const { os << height << "x" << width;}

  virtual void reset()
  {
  }

  int height;
  int width;
  int size;
  std::vector<std::vector<T> > frames;
  mutable std::vector<T>  variance_img, background_img, diff_img, etiquette_binaire;
  static const T N=3;
  int nb_frames;
};

NT2_RUN_EXPERIMENT_TPL( sigmadelta_scalar, (nt2::uint8_t), (32,32,100));
NT2_RUN_EXPERIMENT_TPL( sigmadelta_scalar, (nt2::uint8_t), (64,64,100));
NT2_RUN_EXPERIMENT_TPL( sigmadelta_scalar, (nt2::uint8_t), (256,256,100));
NT2_RUN_EXPERIMENT_TPL( sigmadelta_scalar, (nt2::uint8_t), (512,512,100));
NT2_RUN_EXPERIMENT_TPL( sigmadelta_scalar, (nt2::uint8_t), (2048,2048,100));
NT2_RUN_EXPERIMENT_TPL( sigmadelta_scalar, (nt2::uint8_t), (4096,4096,100));
