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
#include <boost/fusion/include/pop_front.hpp>
#include <boost/fusion/include/pop_back.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates outer_fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::outer_fold_, boost::simd::tag::simd_, (A0)(S0)(A1)(A2)(A3)(A4)
                            , ((expr_< table_< unspecified_<A0>, S0 >
                                     , nt2::tag::terminal_
                                     , boost::mpl::long_<0>
                                     >
                              ))
                              (ast_< A1>)
                              (unspecified_<A2>)
                              (unspecified_<A3>)
                              (unspecified_<A4>)
                            )
  {
    typedef void                                                              result_type;
    typedef typename A0::value_type                                           value_type;
    typedef typename boost::remove_reference<A1>::type::extent_type           extent_type;
    typedef boost::simd::native<value_type,BOOST_SIMD_DEFAULT_EXTENSION>      target_type;

    BOOST_FORCEINLINE result_type operator()(A0& out, A1& in, A2 const& neutral, A3 const& bop, A4 const& uop) const
    {
      extent_type ext = in.extent();
      static const std::size_t N = boost::simd::meta::cardinal_of<target_type>::value;
      typename A0::index_type::type bs;
      std::ptrdiff_t ilow   = boost::fusion::at_c<0>(bs);// it's not 0 it's ext.size() -1;
      std::ptrdiff_t olow   = boost::fusion::at_c<0>(bs);
      std::ptrdiff_t ibound = ilow + ext[ext.size()-1]; 

      // Workaround to have nt2::numel(boost::fusion::pop_back(ext));
      std::ptrdiff_t numel  = 1;
      for(std::ptrdiff_t m = 0; m!= ext.size()-1 ; ++m)
        numel*=ext[m];

      std::ptrdiff_t bound  = olow + ((numel)/N) * N;
      std::ptrdiff_t obound = olow + (numel);


      target_type vec_out ;

      for(std::ptrdiff_t j=olow; j!=bound; j+=N)
        {
          out(j,1) = neutral(nt2::meta::as_<value_type>());
          vec_out = neutral(nt2::meta::as_<target_type>());
          
          for(std::ptrdiff_t i=ilow; i!=ibound; ++i)
            vec_out = bop(vec_out,nt2::run(in, as_aligned(boost::fusion::vector_tie(j,i)), meta::as_<target_type>()));

          //stored the result in out(j,1)          
          for(std::ptrdiff_t n = 0; n!=N; ++n)
            out(j+n,1) = vec_out[n];
        }


      // scalar part
      for(std::ptrdiff_t j=bound; j!=obound; ++j)
        { 
          out(j,1) = neutral(nt2::meta::as_<value_type>());
          for(std::ptrdiff_t i=ilow; i!=ibound; ++i)
            out(j,1) = bop(out(j,1), nt2::run(in, boost::fusion::vector_tie(j,i), meta::as_<value_type>()));
        }
      

    }
  };

} }

#endif
