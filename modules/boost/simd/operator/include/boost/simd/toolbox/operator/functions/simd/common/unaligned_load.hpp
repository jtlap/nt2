//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_UNALIGNED_LOAD_HPP_INCLUDED
#define BOOST_SIMD_TOOLBOX_OPERATOR_FUNCTIONS_SIMD_COMMON_UNALIGNED_LOAD_HPP_INCLUDED
#include <boost/simd/toolbox/operator/functions/unaligned_load.hpp>
#include <boost/simd/include/functions/simd/insert.hpp>
#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/simd/include/functions/simd/is_nez.hpp>
#include <boost/simd/sdk/simd/logical.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost { namespace simd { namespace ext
{
  // scalar emulation
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_load_, tag::cpu_
                            , (A0)(A1)(A2)(X)
                            , (iterator_<scalar_< fundamental_<A0> > >)
                              (scalar_< fundamental_<A1> >)
                              ((target_< simd_< fundamental_<A2>, X > >))
                            )
  {
    typedef typename A2::type result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&)const
    {
      result_type that;
      for(std::size_t i=0; i!=meta::cardinal_of<result_type>::value; ++i)
        that[i] = a0[a1+i];
      return that;
    }
  };

  // regular load
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_load_, tag::cpu_
                            , (A0)(A1)(A2)(X)
                            , (iterator_<scalar_< arithmetic_<A0> > >)
                              (scalar_< fundamental_<A1> >)
                              ((target_< simd_< arithmetic_<A2>, X > >))
                            )
  {
    typedef typename A2::type const& result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&)const
    {
      return reinterpret_cast<result_type>(a0[a1]);
    }
  };

  // logical
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_load_, tag::cpu_
                            , (A0)(A1)(A2)(X)
                            , (iterator_<scalar_< logical_<A0> > >)
                              (scalar_< fundamental_<A1> >)
                              ((target_< simd_< logical_<A2>, X > >))
                            )
  {
    typedef typename A2::type result_type;
    inline result_type operator()(const A0& a0, const A1& a1, const A2&)const
    {
      return is_nez(unaligned_load<typename result_type::type>(a0, a1));
    }
  };

  // shifted
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::unaligned_load_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(X)
                            , (iterator_<scalar_< arithmetic_<A0> > >)
                              (scalar_< fundamental_<A1> >)
                              ((target_< simd_< arithmetic_<A2>, X > >))
                              (mpl_integral_< scalar_< integer_<A3> > >)
                            )
  {
    typedef typename dispatch::meta::
            call<tag::unaligned_load_(A0 const&, A1 const&, A2 const&)>::type
    result_type;
    inline result_type operator()(const A0& a0, const A1& a1,
                                  const A2&, const A3&)const
    {
      return unaligned_load<typename A2::type>(a0 + A3::value, a1);
    }
  };

  // gather
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::unaligned_load_, tag::cpu_
                            , (A0)(A1)(A2)(X)
                            , (mpl::equal_to< boost::simd::meta::cardinal_of<A1>
                                            , boost::simd::meta::cardinal_of<typename A2::type>
                                            >
                              )
                            , (iterator_< scalar_< arithmetic_<A0> > >)
                              ((simd_< integer_<A1>, X >))
                              ((target_< simd_< arithmetic_<A2>, X > >))
                            )
  {
    typedef typename A2::type                           result_type;
    typedef typename meta::scalar_of<result_type>::type stype;

    inline result_type operator()(const A0& a0, const A1& a1, const A2&) const
    {
      // Filling that directly as a result_type still has aliasing issues
      // TODO : Investigate further
      stype that[meta::cardinal_of<result_type>::value];

      for(std::size_t i=0; i<meta::cardinal_of<result_type>::value; ++i)
      {
        that[i] = a0[a1[i]];
      }

      return unaligned_load<result_type>(&that[0]);
    }
  };

} } }

#endif
