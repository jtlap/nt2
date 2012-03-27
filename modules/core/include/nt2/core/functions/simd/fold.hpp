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
#include <boost/simd/toolbox/swar/include/functions/splatted_sum.hpp>
#include <iostream>
namespace nt2 { namespace ext
{
  //============================================================================
  // Generates fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fold_, boost::simd::tag::simd_, (A1)(A2)(A3)
                              , ((ast_< A1>))
                              (unspecified_<A2>)
                              (unspecified_<A3>)
                            )
  {
    typedef typename boost::remove_reference<A1>::type::extent_type            extent_type;
    typedef typename boost::remove_reference<A1>::type::value_type             result_type;
    typedef BOOST_SIMD_DEFAULT_EXTENSION                                       extension_type;
    typedef boost::simd::native<result_type,extension_type>                    native_type;

    BOOST_FORCEINLINE result_type operator()(A1& in, A2 const& neutral, A3 const& op ) const
    {
      extent_type ext = in.extent();
      std::ptrdiff_t card = boost::simd::meta::cardinal_of<native_type>();
      result_type out = neutral(nt2::meta::as_<result_type>());
      native_type vec = neutral(nt2::meta::as_<native_type>());

      if( card <= ext[0]){

        std::ptrdiff_t nb_iter = ext[0]/card;
        for(std::ptrdiff_t c_0 = 0; c_0 < nb_iter; ++c_0){
          for(std::ptrdiff_t j = 0; j < card; ++j){
            vec[j] = in(c_0*card + j + 1);
          }
          out = op(out, boost::simd::splatted_sum(vec)[0]); 
          //FIXME : Made specialisation of functor fold_ to avoid to use splatted_sum in general case
        }

        // Compute the end of the table with scalar version        
        for(std::ptrdiff_t c_0 = nb_iter*card; c_0 < ext[0]; ++c_0){
          out = op(out, in(c_0));
        }

      }
      else{
        //Use scalar version
        for(std::ptrdiff_t c_0 = 1; c_0 <= ext[0]; ++c_0){
          out = op(out, in(c_0));
        }
      }
      return out;     

    }
  };

} }

#endif
