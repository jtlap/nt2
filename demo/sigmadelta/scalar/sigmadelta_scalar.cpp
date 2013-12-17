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
      variance_img      = (T*)malloc(size*sizeof(T));
      background_img    = (T*)malloc(size*sizeof(T));
      diff_img          = (T*)malloc(size*sizeof(T));
      etiquette_binaire = (T*)malloc(size*sizeof(T));

      for(int k=0; k<nb_frames; k++)
        frames[k]  = (T*)malloc(size*sizeof(T));

      for(int k=0; k<nb_frames; k++)
      {
        frame = frames[k];
        for(int i=0; i<height;i++)
        {
          for(int j=0; j<width; j++)
          {
            if(i>(height/4) && i<(height/2) && j>((width/4)+k%10) && j<((width/2)+k%10))
              frame[i*width+j] = 255;
            else frame[i*width+j] = 0;
          }
        }

        for(int i=0; i < size; i++)
        {
          variance_img[i] = 1;
          background_img[i] = (frames[0])[i];
          etiquette_binaire[i] = 0;
        }
      }
    }


    BOOST_FORCEINLINE virtual void run() const
    {
      unsigned char d,mul;

      for(int k=1; k<nb_frames; k++)
      {
        frame = frames[k];

        #pragma simd
        for(int i=0; i < size; i++)
        {
          if(background_img[i] < frame[i])
          {
            background_img[i] += 1;
          }
          else
          {
            if(background_img[i] > frame[i])
            {
              background_img[i] -= 1;
            }
          }

          d = abs(background_img[i]-frame[i]);

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
            etiquette_binaire[i] = 255;
          }
        }
      }
    }
    virtual void info(std::ostream& os) const { os << height << "x" << width; }

    virtual double compute(nt2::benchmark_result_t const& r) const
    {
      return r.first/double(height*width)/nb_frames;
    }

    virtual void reset()
    {
      for(int k=0; k<nb_frames; k++)
        free(frames[k]);
      free(variance_img);
      free(background_img);
      free(diff_img);
      free(etiquette_binaire);
    }

    int height;
    int width;
    int size;
    T* frames[10];
    T*  variance_img;
    T*  background_img;
    T*  diff_img;
    T*  etiquette_binaire;
    mutable T* frame;
    static const T N=3;
    int nb_frames;
  };

NT2_RUN_EXPERIMENT_TPL( sigmadelta_scalar, (nt2::uint8_t), (32,33,8));
NT2_RUN_EXPERIMENT_TPL( sigmadelta_scalar, (nt2::uint8_t), (64,65,8));
NT2_RUN_EXPERIMENT_TPL( sigmadelta_scalar, (nt2::uint8_t), (256,257,8));
NT2_RUN_EXPERIMENT_TPL( sigmadelta_scalar, (nt2::uint8_t), (512,513,8));
NT2_RUN_EXPERIMENT_TPL( sigmadelta_scalar, (nt2::uint8_t), (1024,1025,8));
