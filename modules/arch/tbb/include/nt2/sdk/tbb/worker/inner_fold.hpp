//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_TBB_WORKER_INNER_FOLD_HPP_INCLUDED
#define NT2_SDK_TBB_WORKER_INNER_FOLD_HPP_INCLUDED

#include <tbb/tbb.h>
#include <nt2/sdk/tbb/blocked_range.hpp>
#include <nt2/sdk/shared_memory/worker.hpp>
#include <nt2/include/functor.hpp>
#include <nt2/sdk/config/cache.hpp>
#include <boost/simd/sdk/simd/native.hpp>

namespace nt2
{

  namespace tag
  {
    struct inner_fold_step_;
    template<class T> struct tbb_;
  }

  namespace details
  {
   template<class Site, class value_type>
   struct target_type_from_site
   {
     typedef boost::simd::native<value_type,BOOST_SIMD_DEFAULT_EXTENSION> type;
   };

   template<class value_type>
   struct target_type_from_site<tag::cpu_,value_type>
   {
     typedef value_type type;
   };

  }

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

  // Inner Fold worker
  template<class Site, class Out, class In, class Neutral,class Bop,class Uop>
  struct worker<tag::inner_fold_,tag::tbb_<Site>,Out,In,Neutral,Bop,Uop>
  {
    typedef typename boost::remove_reference<In>::type::extent_type           extent_type;

    typedef typename Out::value_type                                          value_type;
    typedef typename details::target_type_from_site<Site,value_type>::type    target_type;

    worker(Out& out, In& in, Neutral const& n, Bop const& bop, Uop const& uop)
    : out_(out), in_(in), neutral_(n), bop_(bop), uop_(uop)
    {}

    void operator()(nt2::blocked_range<std::size_t> const& r) const
    {
      extent_type ext = in_.extent();
      std::size_t top_cache_line_size = config::top_cache_size(2)/sizeof(value_type);

      std::size_t bound  = boost::fusion::at_c<0>(ext);
      std::size_t ibound = (bound/top_cache_line_size) * top_cache_line_size;
      std::size_t obound = nt2::numel(boost::fusion::pop_front(ext));
      std::size_t grain  = top_cache_line_size;

      for(std::size_t j = r.begin(); j < r.end(); ++j)
      {
        std::size_t k = j*bound;

         nt2::worker<tag::inner_fold_step_,tag::tbb_<Site>,target_type,In,Neutral,Bop>
         w(in_,neutral_,bop_);


        tbb::parallel_reduce( nt2::blocked_range<std::size_t>(k,k+ibound,grain)
                            , w
                            );

        nt2::run(out_, j, uop_(w.out_));

        for(std::size_t i = ibound; i < bound; ++i)
          nt2::run(out_, j
                  , bop_( nt2::run( out_, j, meta::as_<value_type>())
                                  , nt2::run(in_, i+k, meta::as_<value_type>())));
      }
    }

    Out&                     out_;
    In&                      in_;
    Neutral const &          neutral_;
    Bop const &              bop_;
    Uop const &              uop_;

    private:
    worker& operator=(worker const&);
   };

}
#endif
