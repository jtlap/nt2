//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_TSXFUN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_TSXFUN_HPP_INCLUDED

#include <nt2/core/functions/tsxfun.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/ind2sub.hpp>
#include <nt2/include/functions/sub2ind.hpp>
#include <nt2/sdk/meta/as_index.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::tsxfun_, N>))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename boost::proto::result_of::
                     child_c<A0&,0>::value_type                         child0_t;
    typedef typename child0_t::value_type                               s0_t;
    typedef typename boost::simd::ext::adapt_data<child0_t,Data>::type  ad0_t;

    typedef typename boost::proto::result_of::
                     child_c<A0&,1>::value_type                         child1_t;
    typedef typename child1_t::value_type                               s1_t;
    typedef typename boost::simd::ext::adapt_data<child1_t,Data>::type  ad1_t;

    typedef typename boost::proto::result_of::
                     child_c<A0&,2>::value_type                         child2_t;
    typedef typename child1_t::value_type                               s2_t;
    typedef typename boost::simd::ext::adapt_data<child2_t,Data>::type  ad2_t;

    typedef typename child0_t::extent_type    ext1_t;
    typedef typename child1_t::extent_type    ext2_t;
    typedef typename child2_t::extent_type    ext3_t;
    typedef typename make_size< (ext1_t::static_size > ext2_t::static_size)
                              ? ext1_t::static_size
                              : ext2_t::static_size
                               >::type                                  ext0_t;
    typedef typename make_size< (ext0_t::static_size > ext3_t::static_size)
                              ? ext0_t::static_size
                              : ext3_t::static_size
                               >::type                                  ext_t;


    typedef typename Data::type                                     result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      typename ad0_t::type v0;
      typename ad1_t::type v1;
      typename ad2_t::type v2;

      v0 = gather_values<0>(a0,p,boost::proto::child_c<0>(a0).extent(),ad0_t());
      v1 = gather_values<1>(a0,p,boost::proto::child_c<1>(a0).extent(),ad1_t());
      v2 = gather_values<2>(a0,p,boost::proto::child_c<2>(a0).extent(),ad2_t());

      return boost::proto::value(boost::proto::child_c<3>(a0))(v0,v1,v2);
    }

    template<std::size_t I,class T>
    static BOOST_FORCEINLINE typename T::type
    gather_values(A0 const& a0, State const& p, ext_t const& sz, T const& tgt)
    {
      typedef typename meta::as_index<result_type>::type              i_t;
      typedef typename meta::call < nt2::tag
                                    ::enumerate_(State,meta::as_<i_t>)
                                  >::type                               p_t;
      typedef typename meta::call<nt2::tag::ind2sub_(ext_t,p_t)>::type  s_t;
      typedef typename s_t::value_type                                  w_t;

      s_t pos = ind2sub(a0.extent(),enumerate<i_t>(p));

      for(std::size_t i = 0; i != ext_t::size(); ++i)
        pos[i] = nt2::min(splat<w_t>(sz[i]),pos[i]);

      return  run(boost::proto::child_c<I>(a0), sub2ind(sz, pos), tgt);
    }
  };
} }

#endif
