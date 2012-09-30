//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_COMMON_PERMUTE_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_SWAR_FUNCTIONS_SIMD_COMMON_PERMUTE_HPP_INCLUDED

#include <boost/simd/toolbox/swar/functions/permute.hpp>
#include <nt2/sdk/meta/type_id.hpp>
//#include <iostream>

namespace boost { namespace simd { namespace ext
{
//   BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::permute_, tag::cpu_
//                                       , (A0)(I0)(I1)(I2)(I3)(I4)(I5)(I6)(I7)(X)
//                                       , ((simd_< arithmetic_<A0>, X>))
//                                       ((unspecified_<I0> ))
//                                       ((unspecified_<I1>))
//                                       ((unspecified_<I2>))
//                                       ((unspecified_<I3>))
//                                       ((unspecified_<I4>))
//                                       ((unspecified_<I5>))
//                                       ((unspecified_<I6>))
//                                       ((unspecified_<I7>))
//                                       )
//   {
//     typedef A0 result_type;

//     result_type operator()(A0 const& a0, I0 const &, I1 const&, I2 const&, I3 const&,
//                                          I4 const &, I5 const&, I6 const&, I7 const&) const
//     {
//       result_type that;
//       const std::size_t n = meta::cardinal_of<A0>::value-1;
//       int ind[] = {I0::value, I1::value, I2::value, I3::value, I4::value, I5::value, I6::value, I7::value};
//       for(std::size_t i=0;i<= n;++i) that[i] = (ind[i]>= 0) ?a0[ind[i]] : 0;
//       return that;
//     }
//   };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::permute_, tag::cpu_
                                      , (A0)(I0)(I1)(I2)(I3)(X)
                                      , ((simd_< arithmetic_<A0>, X>))
                                      ((unspecified_<I0>))
                                      ((unspecified_<I1>))
                                      ((unspecified_<I2>))
                                      ((unspecified_<I3>))
                                      )
  {
    typedef A0 result_type;

    result_type operator()(A0 const& a0, I0 const &, I1 const&, I2 const&, I3 const&) const
    {
      //        std::cout << "common" << std::endl; 
      result_type that;
      const std::size_t n = meta::cardinal_of<A0>::value-1;
      int ind[] = {I0::value, I1::value, I2::value, I3::value};
      for(std::size_t i=0;i<= n;++i) that[i] = (ind[i]>= 0) ?a0[ind[i]] : 0;
      return that;
    }
  };
  
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::permute_, tag::cpu_
                                      , (A0)(I0)(I1)(X)
                                      , ((simd_< arithmetic_<A0>, X>))
                                      ((unspecified_<I0>))
                                      ((unspecified_<I1>))
                                      )
  {
    typedef A0 result_type;

    result_type operator()(A0 const& a0, I0 const &, I1 const&) const
    {
      result_type that;
      const std::size_t n = meta::cardinal_of<A0>::value-1;
      int ind[] = {I0::value, I1::value};
      for(std::size_t i=0;i<= n;++i) that[i] = (ind[i]>= 0) ?a0[ind[i]] : 0;
      return that;
    }
  };
} } }

#endif
