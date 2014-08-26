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
#include <nt2/sdk/shared_memory/worker/outer_fold_step.hpp>
#include <nt2/sdk/shared_memory/details/target_type_from_site.hpp>
#include <nt2/include/functor.hpp>

#include <boost/simd/memory/align_under.hpp>

namespace nt2
{

  namespace tag
  {
    struct outer_fold_step_outcache_;
    struct outer_fold_step_incache_;
    struct fold_;
    struct cpu_;
  }

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

        // Compute the lower multiple of cache_line of ibound
        std::size_t cache_bound = (cache_line_size / (sizeof(value_type)*N))*N;
        std::size_t iibound =  boost::simd::align_under(ibound, cache_bound);

        // Compute the lower multiple of grain of mbound
        std::size_t mmbound =  (mbound/grain)*grain;

        if( ibound < grain )
        {
          // Instanciate the spawner/worker associated to the mbound dimension
          nt2::spawner<tag::fold_, BackEnd, target_type> s_simd;
          nt2::spawner<tag::fold_, BackEnd, value_type> s_scalar;

          for(std::size_t o = begin, oout_ = begin*ibound, oin_ = begin * iboundxmbound;
              o < begin + size;
              ++o, oout_+=ibound, oin_+= iboundxmbound)
          {
            // parallelized part
            for (std::size_t i = 0, kout_ = oout_, kin_ = oin_;
                 i < iibound;
                 i+=N, kout_+=N, kin_+=N)
            {
              nt2::worker<tag::outer_fold_step_outcache_,BackEnd,Site,In,Neutral,Bop>
              w(in_,neutral_,bop_,kin_);

              target_type vec_out = neutral_(nt2::meta::as_<target_type>());

              if( (size == obound) && (grain < mmbound) )
                  vec_out = s_simd( w, 0, mmbound, grain);
              else
                  vec_out = w(vec_out, 0, mmbound);

              vec_out = w(vec_out, mmbound, mbound-mmbound);

              nt2::run(out_, kout_,vec_out);
            }

            // scalar part
            for(std::size_t i = iibound, k_ = oout_ + iibound, m_ = oin_ + iibound;
                i < ibound;
                ++i, ++k_, ++m_)
            {
              nt2::worker<tag::outer_fold_step_outcache_,BackEnd,Site,In,Neutral,Bop>
              w(in_,neutral_,bop_,m_);

              value_type s_out = neutral_(nt2::meta::as_<value_type>());

              if( (size == obound) && (grain < mmbound) )
                  s_out = s_scalar( w, 0, mmbound, grain);
              else
                  s_out = w(s_out, 0, mmbound);

              s_out = w(s_out, mmbound, mbound-mmbound);

              nt2::run(out_, k_,s_out);
            }
          }
        }

        else
        {
          // Instanciate the spawner/worker associated to the ibound dimension
          nt2::spawner<tag::transform_, BackEnd> s;

          for(std::size_t o = 0, oout_ = begin*ibound, oin_ = begin * iboundxmbound;
              o < size;
              ++o, oout_+=ibound, oin_+= iboundxmbound)
          {
            // vectorized worker
            nt2::worker<tag::outer_fold_step_incache_,BackEnd,Site,Out,In,Neutral,Bop>
            vec_w(out_,in_,neutral_,bop_, begin*ibound, begin * iboundxmbound);

            // scalar worker
            nt2::worker<tag::outer_fold_step_incache_,BackEnd,tag::cpu_,Out,In,Neutral,Bop>
            w(out_,in_,neutral_,bop_, begin*ibound, begin * iboundxmbound);

            // parallelized part
            if((size == obound) && (grain < iibound))
              s(vec_w,0,iibound,grain);

            else if(iibound != 0)
              vec_w(0,iibound);

            // scalar part
            w(iibound,ibound-iibound);
          }
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
