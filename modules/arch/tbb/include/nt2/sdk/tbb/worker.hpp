//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_TBB_WORKER_HPP_INCLUDED
#define NT2_SDK_TBB_WORKER_HPP_INCLUDED

#include <nt2/sdk/shared_memory/worker/worker.hpp>
#include <nt2/include/functor.hpp>

namespace nt2
{

  namespace tag
  {
    struct transform_;
    struct outer_fold_;
    struct inner_fold_step_;
    template<class T> struct tbb_;
  }

  // Transform Worker
  template<class Site, class Out, class In>
  struct worker<tag::transform_,tag::tbb_<Site>,Out,In>
  {
    worker(Out & out, In & in)
    :out_(out),in_(in)
    {}

    void operator()(nt2::blocked_range<std::size_t> const& r) const
    {
      work(out_,in_,std::make_pair(r.begin(),r.size()));
    };

    Out & out_;
    In & in_;

    nt2::functor<tag::transform_,Site> work;

    private:
    worker& operator=(worker const&);
  };

  // Inner Fold Step worker
  template<class Site, class Out, class In, class Neutral,class Bop>
  struct worker<tag::inner_fold_step_,tag::tbb_<Site>,Out,In,Neutral,Bop>
  {
    worker(In & in, Neutral const & neutral, Bop const & bop)
          :in_(in),neutral_(neutral),bop_(bop)
    {
      out_ = neutral_(nt2::meta::as_<Out>());
    }

    worker(worker& src, tbb::split)
    : in_(src.in_), neutral_(src.neutral_), bop_(src.bop_)
    {
      out_ = neutral_(nt2::meta::as_<Out>());
    }

    void operator()(nt2::blocked_range<std::size_t> const& r)
    {
      work(out_,in_,neutral_,bop_,std::make_pair(r.begin(),r.size()));
    };

    void join(worker& rhs) { out_ = bop_(out_, rhs.out_); }

    Out out_;
    In & in_;
    Neutral const & neutral_;
    Bop const & bop_;

    nt2::functor<tag::inner_fold_step_,Site> work;

    private:
    worker& operator=(worker const&);
  };

  // Outer Fold worker
  template<class Site, class Out, class In, class Neutral,class Bop,class Uop>
  struct worker<tag::outer_fold_,tag::tbb_<Site>,Out,In,Neutral,Bop,Uop>
  {
    worker(Out& out, In& in, Neutral const& n, Bop const& bop, Uop const& uop)
    : out_(out), in_(in), neutral_(n), bop_(bop), uop_(uop)
    {}

    void operator()(nt2::blocked_range<std::size_t> const& r) const
    {
      work(out_,in_,neutral_,bop_,uop_,std::make_pair(r.begin(),r.size()));
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
