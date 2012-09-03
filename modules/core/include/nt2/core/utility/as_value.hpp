//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_UTILITY_AS_VALUE_HPP_INCLUDED
#define NT2_CORE_UTILITY_AS_VALUE_HPP_INCLUDED

#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/tofloat.hpp>

namespace nt2
{
  namespace tag
  {
    struct as_value_ : boost::dispatch::tag::formal_
    {
      typedef boost::dispatch::tag::formal_ parent;
    };
  }

  template<class Target, class Value>
  BOOST_FORCEINLINE Target as_value( Value const& v )
  {
    typename make_functor<tag::as_value_,Value>::type callee;
    return callee(v,meta::as_<Target>());
  }
}

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::as_value_, tag::cpu_
                            , (V)(T)
                            , (generic_< unspecified_<V> >)
                              (target_< generic_< unspecified_<T> > >)
                            )
  {
    typedef typename T::type result_type;

    BOOST_FORCEINLINE result_type operator()(V const& v, T const&) const
    {
      return nt2::splat<result_type>(v);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::as_value_, tag::cpu_
                            , (A0)(A1)(X)(Y)
                            , ((simd_< unspecified_<A0>, X >))
                              ((target_< simd_< unspecified_<A1>, Y > >))
                            )
  {
    typedef typename A1::type result_type;

    inline result_type operator()(const A0& a0, const A1&) const
    {
      typedef typename meta::scalar_of<result_type>::type sA1;

      result_type tmp;
      for(unsigned int i = 0; i != meta::cardinal_of<result_type>::value; ++i)
        tmp[i] = static_cast<sA1>(a0[i]);

      return tmp;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::as_value_, tag::cpu_
                            , (V)(T)(X)
                            , ((simd_< integer_<V>, X >))
                              ((target_< simd_< floating_<T>, X > >))
                            )
  {
    typedef typename T::type result_type;

    BOOST_FORCEINLINE result_type operator()(V const& v, T const&) const
    {
      return nt2::tofloat(v);
    }
  };
} }

#endif
