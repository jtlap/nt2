//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SIMD_PARTIAL_FOLD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SIMD_PARTIAL_FOLD_HPP_INCLUDED

#include <nt2/core/functions/partial_fold.hpp>
#include <boost/simd/sdk/simd/meta/is_vectorizable.hpp>
#include <boost/fusion/include/pop_back.hpp>
#include <nt2/sdk/config/cache.hpp>

#ifndef BOOST_SIMD_NO_SIMD
namespace nt2 { namespace ext
{
  //============================================================================
  // Generates partial_fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::partial_fold_, boost::simd::tag::simd_, (A0)(S0)(T0)(N0)(A1)(A2)(A3)(A4)
                               , (boost::simd::meta::is_vectorizable<typename A0::value_type, BOOST_SIMD_DEFAULT_EXTENSION>)
                               , ((expr_< table_< unspecified_<A0>, S0 >
                                        , T0
                                        , N0
                                        >
                                 ))
                                 ((ast_< A1, nt2::container::domain>))
                                 (unspecified_<A2>)
                                 (unspecified_<A3>)
                                 (unspecified_<A4>)
                               )
  {
    typedef void                                                              result_type;
    typedef typename A0::value_type                                           value_type;
    typedef typename boost::remove_reference<A1>::type::extent_type           extent_type;
    typedef boost::simd::native<value_type,BOOST_SIMD_DEFAULT_EXTENSION>      target_type;

    BOOST_FORCEINLINE result_type operator()(A0& out, A1& in, A2 const& neutral, A3 const& bop, A4 const&) const
    {
      extent_type ext = in.extent();
      static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;
      std::size_t ibound  = boost::fusion::at_c<0>(ext);
      std::size_t mbound =  boost::fusion::at_c<1>(ext);
      std::size_t obound =  boost::fusion::at_c<2>(ext);
      std::size_t id;

      std::size_t cache_line_size = nt2::config::top_cache_line_size(2); // in byte
      std::size_t nb_vec = cache_line_size/(sizeof(value_type)*N);
      std::size_t cache_bound = (nb_vec)*N;
      std::size_t bound  =  ((ibound)/cache_bound) * cache_bound;

      if(ibound >= cache_bound){

        for(std::size_t o = 0, o_ = 0; o < obound; ++o, o_+=ibound){
          for(std::size_t i = 0; i < bound; i+=cache_bound){
            id = i+o_;
            for (std::size_t k = 0, k_ = id; k < nb_vec; ++k, k_+=N)
              nt2::run(out, k_, neutral(nt2::meta::as_<target_type>()));

            for(std::size_t m = 0, m_ = 0; m < mbound; ++m, m_+=ibound){
              for (std::size_t k = 0, k_ = id; k < nb_vec; ++k, k_+=N)
                nt2::run(out, k_
                         , bop(nt2::run(out, k_, meta::as_<target_type>())
                               ,nt2::run(in, k_+m_, meta::as_<target_type>()))
                         );
            }
          }
        }
        
        //scalar part
        for(std::size_t o = 0, o_ = 0; o < obound; ++o, o_+=ibound){
          for(std::size_t i = bound; i < ibound; ++i){
            id = i+o_;
            nt2::run(out, id, neutral(nt2::meta::as_<value_type>()));
            for(std::size_t m = 0, m_ = 0; m < mbound; ++m, m_+=ibound){
              nt2::run(out, id
                       , bop(nt2::run(out, id,meta::as_<value_type>())
                             ,nt2::run(in, id+m_,meta::as_<value_type>()))
                       );
            }
          }
        }
      }
      
      else {

        for(std::size_t o = 0, o_ = 0; o < obound; ++o, o_+=ibound){
          for(std::size_t i = 0; i < ibound; ++i){
            id = i+o_;
            nt2::run(out, id, neutral(nt2::meta::as_<value_type>()));
            for(std::size_t m = 0, m_ = 0; m < mbound; ++m, m_+=ibound){
              nt2::run(out, id
                       , bop(nt2::run(out, id,meta::as_<value_type>())
                             ,nt2::run(in, id+m_,meta::as_<value_type>()))
                       );
            }
          }
        }
      }
    }
  };

  } }

#endif
#endif
