//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II         
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI         
//                                                                              
//          Distributed under the Boost Software License, Version 1.0.          
//                 See accompanying file LICENSE.txt or copy at                 
//                     http://www.boost.org/LICENSE_1_0.txt                     
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_LOAD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_LOAD_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// load for no SIMD types
////////////////////////////////////////////////////////////////////////////////
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/simd/sdk/memory/is_aligned.hpp>
#include <boost/mpl/equal_to.hpp>
#include <nt2/sdk/error/assert.hpp>
#include <cstring>

namespace boost { namespace simd { namespace ext
{
  // regular load
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::load_, tag::cpu_
                            , (A0)(A1)(A2)(X)
                            , (iterator_<scalar_< fundamental_<A0> > >)
                              (scalar_< fundamental_<A1> >)
                              ((target_< simd_< fundamental_<A2>, X > >))
                            )
  {
    typedef typename A2::type result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&) const
    {
      BOOST_ASSERT_MSG
      ( boost::simd::memory::is_aligned(a0,BOOST_SIMD_CONFIG_ALIGNMENT)
      , "Unaligned memory location. You tried to load with a pointer that"
        " is not aligned on the simd vector size.");
      result_type that;
      std::memcpy ( &that
                  , reinterpret_cast<result_type const*>(a0) + a1
                  , sizeof that
                  );
      return that;
    }
  };

  // shifted load
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::load_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(X)
                            , (iterator_<scalar_< fundamental_<A0> > >)
                              (scalar_< fundamental_<A1> >)
                              ((target_< simd_< fundamental_<A2>, X > >))
                              (mpl_integral_< scalar_< integer_<A3> > >)
                            )
  {
    typedef typename A2::type result_type;
    inline result_type operator()(const A0& a0, const A1& a1,
                                  const A2&, const A3&) const
    {
      BOOST_ASSERT_MSG
      ( boost::simd::memory::is_aligned(a0,BOOST_SIMD_CONFIG_ALIGNMENT)
      , "Unaligned memory location. You tried to load with a pointer that"
        "is not aligned on the simd vector size.");
      result_type that;
      std::memcpy ( &that
                  , reinterpret_cast<result_type const*>(a0 + A3::value) + a1
                  , sizeof that
                  );
      return that;
    }
  };
  
  // gather
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::load_, tag::cpu_
                            , (A0)(A1)(A2)(X)
                            , (mpl::equal_to< boost::simd::meta::cardinal_of<A1>
                                            , boost::simd::meta::cardinal_of<typename A2::type>
                                            >
                              )
                            , (iterator_< scalar_< fundamental_<A0> > >)
                              ((simd_< integer_<A1>, X >))
                              ((target_< simd_< arithmetic_<A2>, X > >))
                            )
  {
    typedef typename A2::type result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&) const
    {
      BOOST_ASSERT_MSG
      ( boost::simd::memory::is_aligned(a0,BOOST_SIMD_CONFIG_ALIGNMENT)
      , "Unaligned memory location. You tried to load with a pointer that"
        "is not aligned on the simd vector size.");
      result_type that;
      for(std::size_t i=0; i<meta::cardinal_of<result_type>::value; ++i)
        that[i] = a0[a1[i]];
      
      return that;
    }
  };
  
} } }

#endif
