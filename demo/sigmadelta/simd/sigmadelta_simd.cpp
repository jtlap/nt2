//==============================================================================
// Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
// Copyright 2009 - 2013 LRI UMR 8623 CNRS/Univ Paris Sud XI
// Copyright 2012 - 2013 MetaScale SAS
//
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file LICENSE.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
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

#include <nt2/sdk/bench/benchmark.hpp>
#include <iostream>
#include <string>

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


template<typename T> NT2_EXPERIMENT(sigmadelta_simd)
{
public:

  sigmadelta_simd( std::size_t const& h, std::size_t const& w, std::size_t const& seq)
  : NT2_EXPERIMENT_CTOR(1., "cycles/elements")
  , height(h), width(w), size(h*w), nb_frames(seq)
  {
    frames.resize(seq);
    variance_img.resize(size);
    background_img.resize(size);
    etiquette_binaire.resize(size);
    for(std::size_t k=0; k<nb_frames; k++)
      frames[k].resize(size);

    for(std::size_t k=0; k<nb_frames; k++)
    {
      for(std::size_t j=0; j<width; j++)
      {
        for(std::size_t i=0; i<height;i++)
        {
          if(i>(height/4) && i<(height/2) && j>((width/4)+k%10) && j<((width/2)+k%10))
            frames[k][i*width+j] = 255;
          else
            frames[k][i*width+j] = 0;
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

    step_size=boost::simd::meta::cardinal_of<type>::value;
    aligned_sz = size & ~(step_size-1);
    for(std::size_t k=1; k<nb_frames; k++)
    {
      it         = 0;
      for(std::size_t m=aligned_sz; it != m; it += step_size)
      {
        type bkg(&background_img[it]);
        type fr(&frames[k][it]);
        type var(&variance_img[it]);
        aligned_store(do_work(bkg,fr,var),&etiquette_binaire[it]);
        aligned_store(var,&variance_img[it]);
      }
      for(std::size_t m=size; it != m; it++)
      {
        etiquette_binaire[it] = do_work(background_img[it],frames[k][it], variance_img[it]);
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

  std::size_t height;
  std::size_t width;
  std::size_t size;
  mutable std::size_t aligned_sz;
  mutable std::size_t it;
  mutable std::vector< std::vector<T, boost::simd::allocator<T> > > frames;
  mutable std::vector<T, boost::simd::allocator<T> > variance_img, background_img, etiquette_binaire;
  static const T N=3;
  mutable std::size_t step_size;
  std::size_t nb_frames;
};

NT2_RUN_EXPERIMENT_TPL( sigmadelta_simd, (nt2::uint8_t), (32,32,100));
NT2_RUN_EXPERIMENT_TPL( sigmadelta_simd, (nt2::uint8_t), (64,64,100));
NT2_RUN_EXPERIMENT_TPL( sigmadelta_simd, (nt2::uint8_t), (256,256,100));
NT2_RUN_EXPERIMENT_TPL( sigmadelta_simd, (nt2::uint8_t), (512,512,100));
NT2_RUN_EXPERIMENT_TPL( sigmadelta_simd, (nt2::uint8_t), (2048,2048,100));
NT2_RUN_EXPERIMENT_TPL( sigmadelta_simd, (nt2::uint8_t), (4096,4096,100));
