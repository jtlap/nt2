//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SIMD_INNER_FOLD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SIMD_INNER_FOLD_HPP_INCLUDED

#include <nt2/core/functions/inner_fold.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/sdk/simd/meta/is_vectorizable.hpp>

#ifndef BOOST_SIMD_NO_SIMD
namespace nt2 { namespace ext
{
  //============================================================================
  // Generates inner_fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::inner_fold_, boost::simd::tag::simd_, (A0)(S0)(A1)(A2)(A3)(A4)
                               , (boost::simd::meta::is_vectorizable<typename A0::value_type, BOOST_SIMD_DEFAULT_EXTENSION>)
                               , ((expr_< table_< unspecified_<A0>, S0 >
                                        , nt2::tag::terminal_
                                        , boost::mpl::long_<0>
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

    BOOST_FORCEINLINE result_type operator()(A0& out, A1& in, A2 const& neutral, A3 const& bop, A4 const& uop ) const
    {
      extent_type ext = in.extent();
      static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;
      std::size_t bound  = boost::fusion::at_c<0>(ext);
      std::size_t ibound = (boost::fusion::at_c<0>(ext)/N) * N;
      std::size_t obound = nt2::numel(boost::fusion::pop_front(ext));
      target_type vec_out ;


      for(std::size_t j = 0, k = 0; j < obound; ++j, k+=bound)
      {
        nt2::run(out, j, neutral(nt2::meta::as_<value_type>()));
        vec_out = neutral(nt2::meta::as_<target_type>());

        for(std::size_t i = 0; i < ibound; i+=N)
          vec_out = bop(vec_out,nt2::run(in, i+k, meta::as_<target_type>()));
        
        nt2::run(out, j, uop(vec_out));
        
        for(std::size_t i = ibound; i < bound; ++i)
          nt2::run(out, j
                   , bop(nt2::run(out, j, meta::as_<value_type>())
                         , nt2::run(in, i+k, meta::as_<value_type>())));
        
      }
    }

  };

  } }

#endif
#endif
