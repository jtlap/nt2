//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SIMD_FOLD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SIMD_FOLD_HPP_INCLUDED

#include <nt2/core/functions/fold.hpp>
#include <boost/simd/sdk/simd/native.hpp>
#include <nt2/include/functions/run.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/simd/meta/is_vectorizable.hpp>

#ifndef BOOST_SIMD_NO_SIMD
namespace nt2 { namespace ext
{
  //============================================================================
  // Generates fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION_IF( nt2::tag::fold_, boost::simd::tag::simd_, (A1)(A2)(A3)(A4)
                               , (boost::simd::meta::is_vectorizable<typename A1::value_type, BOOST_SIMD_DEFAULT_EXTENSION>)
                               , ((ast_< A1, nt2::container::domain>))
                                 (unspecified_<A2>)
                                 (unspecified_<A3>)
                                 (unspecified_<A4>)
                               )
  {
    typedef typename boost::remove_reference<A1>::type::extent_type            extent_type;
    typedef typename boost::remove_reference<A1>::type::value_type             stype;
    typedef typename boost::dispatch::meta::result_of<A4 const(stype)>::type   result_type;
    typedef boost::simd::native<result_type,BOOST_SIMD_DEFAULT_EXTENSION>      target_type;

    BOOST_FORCEINLINE result_type operator()(A1& in, A2 const& neutral, A3 const& bop, A4 const& uop) const
    {
      extent_type ext = in.extent();
      static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;
      std::size_t bound  = boost::fusion::at_c<0>(ext);
      std::size_t aligned_bound = (boost::fusion::at_c<0>(ext)/N) * N;

      result_type out = neutral(nt2::meta::as_<result_type>());
      target_type vec_out = neutral(nt2::meta::as_<target_type>());

      for(std::size_t i =0; i < aligned_bound; i+=N)
        vec_out = bop(vec_out, nt2::run(in, i, meta::as_<target_type>()));
      out = uop(vec_out);

      for(std::size_t i = aligned_bound; i < bound; ++i)
        out = bop(out, nt2::run(in, i, meta::as_<result_type>()));

      return out;
    }
  };

} }
#endif
#endif
