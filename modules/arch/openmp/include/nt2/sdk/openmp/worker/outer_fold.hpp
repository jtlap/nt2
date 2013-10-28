//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_OPENMP_WORKER_OUTER_FOLD_HPP_INCLUDED
#define NT2_SDK_OPENMP_WORKER_OUTER_FOLD_HPP_INCLUDED

#include <nt2/sdk/shared_memory/worker.hpp>
#include <nt2/include/functor.hpp>

namespace nt2
{
namespace tag
  {
    struct outer_fold_;
    template<class T> struct openmp_;
  }

  // Outer Fold worker
  template<class Site, class Out, class In, class Neutral,class Bop,class Uop>
  struct worker<tag::outer_fold_,tag::openmp_<Site>,Out,In,Neutral,Bop,Uop>
  {
    worker(Out& out, In& in, Neutral const& n, Bop const& bop, Uop const& uop)
    : out_(out), in_(in), neutral_(n), bop_(bop), uop_(uop)
    {}

    void operator()(std::size_t begin, std::size_t size) const
    {
      work(out_,in_,neutral_,bop_,uop_,std::make_pair(begin,size));
    }

    Out&                     out_;
    In&                      in_;
    Neutral const &          neutral_;
    Bop const &              bop_;
    Uop const &              uop_;

    nt2::functor<tag::outer_fold_,Site> work;

    private:
    worker& operator=(worker const&);
   };

}

#endif

