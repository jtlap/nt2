//==============================================================================
// Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
// Copyright 2009 - 2013 LRI UMR 8623 CNRS/Univ Paris Sud XI
// Copyright 2012 - 2013 MetaScale SAS
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <iostream>
#include <string>
#include <nt2/sdk/bench/benchmark.hpp>
#include <boost/simd/include/functions/max.hpp>
#include <boost/simd/include/functions/min.hpp>
#include <boost/simd/include/functions/minus.hpp>
#include <boost/simd/include/functions/multiplies.hpp>
#include <boost/simd/include/functions/selinc.hpp>
#include <boost/simd/include/functions/seldec.hpp>
#include <boost/simd/include/functions/if_zero_else_one.hpp>
#include <boost/simd/include/functions/split_multiplies.hpp>
#include <boost/simd/include/functions/adds.hpp>
#include <boost/simd/include/functions/muls.hpp>
#include <boost/simd/sdk/simd/pack.hpp>
#include <boost/simd/memory/allocator.hpp>
#include <boost/simd/include/functions/aligned_store.hpp>

using namespace nt2;
template<class Pixel>
BOOST_FORCEINLINE Pixel do_work(Pixel &bkg, const Pixel &fr, Pixel &var)
{
  Pixel diff_img, mul_img, zero=0;
  bkg = selinc( bkg < fr, seldec( bkg > fr
                      , bkg
                      )
        );
  diff_img = max(bkg, fr) - min(bkg, fr);

  mul_img = adds(adds(diff_img,diff_img),diff_img);

  var = if_else( diff_img != zero, selinc( var < mul_img
                                 , seldec( var > mul_img
                                 , var
                                 )
                                 )
                            , var
                            );
  return if_zero_else_one( diff_img < var );
}


template<typename T> NT2_EXPERIMENT(sigmadelta_exp)
{
public:

  sigmadelta_exp( std::size_t const& h, std::size_t const& w, std::size_t const& seq)
  : NT2_EXPERIMENT_CTOR(1., "cycles/elements")
  , height(h), width(w), size(h*w), nb_frames(seq)
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
            frames[k][i,j] = 255;
          else frames[k][i,j] = 0;
        }
      }
    }
    std::fill(variance_img.begin(),variance_img.end(),1);
    background_img = frames[0];
    std::fill(etiquette_binaire.begin(),etiquette_binaire.end(),0);
  }

  virtual void run() const
  {
    using boost::simd::pack;
    using boost::simd::aligned_load;
    using boost::simd::aligned_store;

    typedef pack<T> type;

    for(int k=1; k<nb_frames; k++)
    {
      for (int j=0; j<size; j+=boost::simd::meta::cardinal_of<type>::value)
      {
        type bkg(&background_img[j]);
        type fr(&frames[k][j]);
        type var(&variance_img[j]);
        aligned_store(do_work(bkg,fr,var),&etiquette_binaire[j]);
        aligned_store(var,&variance_img[j]);
      }
    }
  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.first/double(height*width)/nb_frames;
  }

  virtual void info(std::ostream& os) const { os << height << "x" << width;}

  virtual void reset() const
  {
    std::fill(variance_img.begin(),variance_img.end(),1);
    background_img = frames[0];
    std::fill(etiquette_binaire.begin(),etiquette_binaire.end(),0);
  }

 private:
  std::size_t height;
  std::size_t width;
  std::size_t size;
  mutable std::vector< std::vector<T, boost::simd::allocator<T> > > frames;
  mutable std::vector<T, boost::simd::allocator<T> >  variance_img;
  mutable std::vector<T, boost::simd::allocator<T> > background_img;
  mutable std::vector<T, boost::simd::allocator<T> > etiquette_binaire;
  mutable std::vector<T, boost::simd::allocator<T> > frame;
  static const T N=3;
  std::size_t nb_frames;
};

NT2_RUN_EXPERIMENT_TPL( sigmadelta_exp, (nt2::uint8_t), (32,33,8));
NT2_RUN_EXPERIMENT_TPL( sigmadelta_exp, (nt2::uint8_t), (64,65,8));
NT2_RUN_EXPERIMENT_TPL( sigmadelta_exp, (nt2::uint8_t), (256,257,8));
NT2_RUN_EXPERIMENT_TPL( sigmadelta_exp, (nt2::uint8_t), (512,513,8));
NT2_RUN_EXPERIMENT_TPL( sigmadelta_exp, (nt2::uint8_t), (1024,1025,8));
