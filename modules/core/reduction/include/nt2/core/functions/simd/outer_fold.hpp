//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SIMD_OUTER_FOLD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SIMD_OUTER_FOLD_HPP_INCLUDED

#include <nt2/core/functions/outer_fold.hpp>
#include <nt2/core/functions/details/fold_step.hpp>
#include <boost/simd/sdk/simd/meta/is_vectorizable.hpp>
#include <boost/simd/memory/align_under.hpp>
#include <boost/fusion/include/pop_back.hpp>
#include <nt2/sdk/config/cache.hpp>
#include <boost/config.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4702) // unreachable code false positive
#endif

#ifndef BOOST_SIMD_NO_SIMD
namespace nt2 { namespace ext
{
  //============================================================================
  // Partial outer_fold with offset/size
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION_IF ( nt2::tag::outer_fold_, boost::simd::tag::simd_
                                , (A0)(A1)(A2)(A3)(A4)(A5)
                                , ( boost::simd::meta::
                                    is_vectorizable < typename A0::value_type
                                                    , BOOST_SIMD_DEFAULT_EXTENSION
                                                    >
                                  )
                                , ((ast_< A0, nt2::container::domain>))
                                  ((ast_< A1, nt2::container::domain>))
                                  (unspecified_<A2>)
                                  (unspecified_<A3>)
                                  (unspecified_<A4>)
                                  (unspecified_<A5>)
                                )
  {
    typedef void                                                              result_type;
    typedef typename A0::value_type                                           value_type;
    typedef typename A1::extent_type                                          extent_type;
    typedef boost::simd::native<value_type,BOOST_SIMD_DEFAULT_EXTENSION>      target_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& out, A1& in, A2 const& neutral, A3 const& bop, A4 const&, A5 const& range) const
    {
      extent_type ext = in.extent();
      static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;
      std::size_t ibound = boost::fusion::at_c<0>(ext);
      std::size_t mbound = boost::fusion::at_c<1>(ext);
      std::size_t iboundxmbound =  ibound * mbound;

      std::size_t cache_line_size = nt2::config::top_cache_line_size(2); // in byte
      std::size_t nb_vec = cache_line_size / (sizeof(value_type)*N);
      std::size_t cache_bound = (nb_vec)*N;
      std::size_t bound =  boost::simd::align_under(ibound, cache_bound);

      std::size_t begin = range.first;
      std::size_t size = range.second;

      for(std::size_t o = begin, oout_ = begin*ibound, oin_ = begin * iboundxmbound;
          o < begin + size;
          ++o, oout_+=ibound, oin_+= iboundxmbound)
      {
        for(std::size_t i = 0; i < bound; i+=cache_bound)
        {
          for (std::size_t k = 0, kout_ = oout_ + i, kin_ = oin_ + i;
               k < nb_vec;
               ++k, kout_+=N, kin_+=N)
          {
            nt2::run(out, kout_,
              details::fold_step(neutral(nt2::meta::as_<target_type>()), in, bop
                                ,kin_, mbound, ibound
                                )
              );
          }
        }

        // scalar part
        for(std::size_t i = bound, k_ = oout_ + bound, m_ = oin_ + bound;
            i < ibound;
            ++i, ++k_, ++m_)
        {
          nt2::run(out, k_,
          details::fold_step(neutral(nt2::meta::as_<value_type>()), in, bop
                            ,m_, mbound, ibound
                            )
          );
        }
      }
    }
  };
} }

#endif

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif
