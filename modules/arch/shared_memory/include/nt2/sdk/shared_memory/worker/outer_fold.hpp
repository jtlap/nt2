//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_SDK_SHARED_MEMORY_WORKER_OUTER_FOLD_HPP_INCLUDED
#define NT2_SDK_SHARED_MEMORY_WORKER_OUTER_FOLD_HPP_INCLUDED

#include <nt2/sdk/shared_memory/worker.hpp>
#include <nt2/sdk/shared_memory/details/target_type_from_site.hpp>
#include <nt2/include/functor.hpp>

#include <boost/simd/memory/align_under.hpp>

namespace nt2
{

  namespace tag
  {
    struct outer_fold_step_;
    struct fold_;
  }

  // Outer Fold Step worker
  template<class BackEnd, class Site, class In, class Neutral, class Bop>
  struct worker<tag::outer_fold_step_,BackEnd,Site,In,Neutral,Bop>
  {
    typedef typename boost::remove_reference<In>::type::extent_type extent_type;

    worker(In & in, Neutral const & neutral, Bop const & bop)
          :in_(in),neutral_(neutral),bop_(bop)
    {}

    template<class Out>
    Out operator()(Out & out, std::size_t begin, std::size_t size)
    {
      extent_type ext = in_.extent();
      std::size_t ibound = boost::fusion::at_c<0>(ext);

      return details::fold_step(out, in_, bop_, begin, size, ibound);
    };

    In & in_;
    Neutral const & neutral_;
    Bop const & bop_;

    private:
    worker& operator=(worker const&);
  };


  // Outer Fold worker
  template<class BackEnd, class Site, class Out, class In, class Neutral,class Bop,class Uop>
  struct worker<tag::outer_fold_,BackEnd,Site,Out,In,Neutral,Bop,Uop>
  {
      typedef typename boost::remove_reference<In>::type::extent_type           extent_type;
      typedef typename Out::value_type                                          value_type;
      typedef typename details::target_type_from_site<Site,value_type>::type    target_type;

      worker(Out& out, In& in, Neutral const& n, Bop const& bop, Uop const& uop)
      : out_(out), in_(in), neutral_(n), bop_(bop), uop_(uop)
      {}

      void operator()(std::size_t begin, std::size_t size) const
      {
        extent_type ext = in_.extent();
        static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;
        std::size_t ibound = boost::fusion::at_c<0>(ext);
        std::size_t mbound = boost::fusion::at_c<1>(ext);
        std::size_t obound = boost::fusion::at_c<2>(ext);
        std::size_t iboundxmbound =  ibound * mbound;

        std::size_t cache_line_size = nt2::config::top_cache_line_size(2); // in byte
        std::size_t grain  = cache_line_size;

        // Compute the lower multiple of N of ibound
        std::size_t nb_vec = cache_line_size / (sizeof(value_type)*N);
        std::size_t cache_bound = (nb_vec)*N;
        std::size_t iibound =  boost::simd::align_under(ibound, cache_bound);

        // Compute the lower multiple of grain of mbound
        std::size_t mmbound =  (mbound/grain)*grain;

        // Instanciate the spawner/worker associated to the mbound dimension
        nt2::worker<tag::outer_fold_step_,BackEnd,Site,In,Neutral,Bop>
        w(in_,neutral_,bop_);
        nt2::spawner<tag::fold_, BackEnd, target_type> s;

        for(std::size_t o = begin, oout_ = begin*ibound, oin_ = begin * iboundxmbound;
            o < begin + size;
            ++o, oout_+=ibound, oin_+= iboundxmbound)
        {
          for(std::size_t i = 0; i < iibound; i+=cache_bound)
          {

            for (std::size_t k = 0, kout_ = oout_ + i, kin_ = oin_ + i;
                 k < nb_vec;
                 ++k, kout_+=N, kin_+=N)
            {
              target_type vec_out = neutral_(nt2::meta::as_<target_type>());

              if( (size == obound) && (grain < mmbound) )
                  vec_out = s( w, kin_, mmbound, grain);
              else
                  vec_out = w(vec_out, kin_, mmbound);

              vec_out = details::fold_step(
                          vec_out, in_, bop_
                        , kin_+mmbound*ibound, mbound-mmbound, ibound
                        );

              nt2::run(out_, kout_,vec_out);
            }
          }

          // scalar part
          for(std::size_t i = iibound, k_ = oout_ + iibound, m_ = oin_ + iibound;
              i < ibound;
              ++i, ++k_, ++m_)
          {
            nt2::run(out_, k_,
            details::fold_step(neutral_(nt2::meta::as_<value_type>()), in_, bop_
                              ,m_, mbound, ibound
                              )
            );
          }
        }
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
