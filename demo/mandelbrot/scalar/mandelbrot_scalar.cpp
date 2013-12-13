//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#include <iostream>
#include <nt2/sdk/bench/benchmark.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/strip.hpp>
#include <nt2/include/functions/any.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/arrayfun.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/seladd.hpp>
#include <nt2/include/functions/expand_to.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/table.hpp>
#include "../include/utils.hpp"

// --------------------------------------------------
int mandelbrot_scalar(float a, float b, int max_iter)
// --------------------------------------------------
{

    // conseil: afficher le contenu des variables dans la boucles *et* valider via excel

    int iter = 0;
    float x = 0;
    float y = 0;
    float t;
    do {
        t = x*x - y*y + a;
        y = 2*x*y + b;
        x = t;
        iter++;
    } while ((x*x+y*y<4) && (iter<max_iter));

    return iter;
}

template<typename T> NT2_EXPERIMENT(mandelbrot_exp)
{
public:
  typedef T value_type;

  mandelbrot_exp( std::size_t const& h, std::size_t const& w
                , value_type const& a0, value_type const& a1
                , value_type const& b0, value_type const& b1
                , std::size_t const& max_iter
                )
  : NT2_EXPERIMENT_CTOR(10., "cycles/elements")
  , h_(h), w_(w), a0_(a0), a1_(a1), b0_(b0), b1_(b1), max_iter_(max_iter)
  {
    C.resize(h*w);
  }


  virtual void run() const
  {
   // intervale de valeurs: [a0:a1]x[b0:b1]

    // la seule chose a modifier dans cette fonction est la ligne de pragma OpenMP

    int i, j;

    float da, db;
    float a, b;
    int iter;

    da = (a1_-a0_)/w_;
    db = (b1_-b0_)/h_;

    // AJOUTER ICI DIFFERENTS PRAGMA OPENMP

#pragma message("PENSEZ A EFFACER LA LIGNE OPENMP")
//#ifdef OPENMP
    //#pragma omp parallel for shared(M) private (h, w, x0, x1, y0, y1, max_iter, i, j, dx, dy, x, y, iter)
//#pragma omp parallel for
    //#pragma omp parallel for schedule(static)
#pragma omp parallel for schedule(dynamic, 8)
//#endif
    for(i=0; i<h_; i++) {
        for(j=0; j<w_; j++) {

            // conversion (i,j) -> (x,y)
            a = a0_ + i * da;
            b = b0_ + j * db;

            iter = mandelbrot_scalar(a, b, max_iter_);

            C[j+w_*i] = iter;
        }
    }

  }

  virtual double compute(nt2::benchmark_result_t const& r) const
  {
    return r.first/double(h_*w_);
  }

  virtual void info(std::ostream& os) const { os << h_ << "x" << w_; }

  virtual void reset() const
  {
    static int pass = 0;
    if(pass==1)
    {
      utils::save_pgm(C,h_,w_, "test_pgm.pgm");
    }
    pass++;
  }

 private:
  mutable std::vector<value_type> A, B;
  mutable std::vector<int> C;
  std::size_t h_, w_, max_iter_;
  value_type a0_, a1_, b0_, b1_;
};

NT2_RUN_EXPERIMENT_TPL( mandelbrot_exp, (float), (5000,5000,-1.5,0.5,-1.0,1.0,256));
NT2_RUN_EXPERIMENT_TPL( mandelbrot_exp, (float), (5000,5000,-1.5,0.5,-1.0,1.0,256));
NT2_RUN_EXPERIMENT_TPL( mandelbrot_exp, (float), (5000,5000,-1.5,0.5,-1.0,1.0,256));
NT2_RUN_EXPERIMENT_TPL( mandelbrot_exp, (float), (5000,5000,-1.5,0.5,-1.0,1.0,256));
