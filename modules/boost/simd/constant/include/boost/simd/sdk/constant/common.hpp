//==============================================================================
//         Copyright 2003 & onward LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 & onward LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SDK_CONSTANT_COMMON_HPP_INCLUDED
#define BOOST_SIMD_SDK_CONSTANT_COMMON_HPP_INCLUDED

#include <boost/simd/include/functions/splat.hpp>
#include <boost/simd/include/functions/bitwise_cast.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/simd/sdk/simd/tags.hpp>
#include <boost/dispatch/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/as.hpp>
#include <boost/simd/sdk/constant/constant.hpp>

//==============================================================================
// Forward all constant call to the simd version of themselves that splat
// the appropriate scalar constants into a proper SIMD vector.
//==============================================================================
namespace boost { namespace simd { namespace ext
{
  //============================================================================
  // By default we splat the constant contained into the extarcted value from
  // the Tag over a given Target.
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( constant_<Tag>, tag::cpu_, (Tag)(A0)
                                   , ((target_< scalar_< arithmetic_<A0> > >))
                                   )
  {
    typedef typename A0::type                               base_type;
    typedef typename boost::mpl::apply<Tag,base_type>::type value_type;
    typedef typename value_type::value_type                 result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type operator()(A0 const&) const
    {
      value_type value;
      return boost::simd::splat<result_type>( result_type(value) );
    }
  };

  //============================================================================
  // In the SIMD case, if we generate an integral vector, we do a simple
  // splat from the Tag/Target bit pattern immediate, if not we add a bitwise
  // cast
  //============================================================================
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( constant_<Tag>, tag::cpu_, (Tag)(A0)(X)
                                    , ((target_< simd_< arithmetic_<A0>,X> >))
                                    )
  {
    typedef typename A0::type                                       target_type;
    typedef typename dispatch::meta::scalar_of<target_type>::type   base_type;
    typedef typename boost::mpl::apply<Tag,base_type>::type         value_type;
    typedef boost::simd::native<typename value_type::value_type,X>  result_type;

    BOOST_DISPATCH_FORCE_INLINE result_type operator()(A0 const&) const
    {
      typedef typename dispatch::meta::
                       as_integer<typename value_type::value_type>::type 
                                                                    pattern_type;
      typedef boost::simd::native<pattern_type,X>                   tmp_type;
      
      return bitwise_cast<result_type> ( boost::simd::
                                        splat<tmp_type>( pattern_type(value_type::value) )
                                      );
    }
  };
  
} } }

#endif
