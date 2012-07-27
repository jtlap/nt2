//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_COMMON_BSXFUN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_COMMON_BSXFUN_HPP_INCLUDED

#include <nt2/core/functions/bsxfun.hpp>
#include <nt2/include/functions/run.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/splat.hpp>
#include <nt2/include/functions/ind2sub.hpp>
#include <nt2/include/functions/sub2ind.hpp>
#include <nt2/include/functions/enumerate.hpp>
#include <boost/fusion/include/pop_front.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)(N)
                            , ((node_<A0, nt2::tag::bsxfun_, N>))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename  boost::proto::result_of::
                      child_c<A0&,0>::value_type                    child0_t;
    typedef typename  boost::proto::result_of::
                      child_c<A0&,1>::value_type                    child1_t;

    typedef typename  boost::proto::result_of::
                      value < typename  boost::proto::result_of::
                                        child_c<A0&,2>::value_type
                            >::type                                 func_t;
    typedef typename boost::dispatch::meta::
            call<nt2::tag::run_( child0_t, State&, Data&)>::type    base0_t;
    typedef typename boost::dispatch::meta::
            call<nt2::tag::run_( child1_t, State&, Data&)>::type    base1_t;
    typedef typename boost::dispatch::meta::
            result_of<func_t const( base0_t, base1_t)>::type        result_type;

    typedef typename meta::strip<typename child0_t::extent_type>::type  ext1_t;
    typedef typename meta::strip<typename child1_t::extent_type>::type  ext2_t;
    typedef typename  make_size < (ext1_t::static_size > ext2_t::static_size)
                                ? ext1_t::static_size
                                : ext2_t::static_size
                                >::type                                 ext_t;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      // Size and stride for each children
      ext_t       ex0 = boost::proto::child_c<0>(a0).extent();
      std::size_t s0  = nt2::numel(boost::fusion::pop_front(ex0));

      ext_t       ex1 = boost::proto::child_c<1>(a0).extent();
      std::size_t s1  = nt2::numel(boost::fusion::pop_front(ex1));

      // Expand or gather values
      result_type v0  = (ex0[0] == 1 )  ? expand_singleton<0>(a0,p,s0)
                                        : gather_values<0>(a0,p,ex0);

      result_type v1  = (ex1[0] == 1 )  ? expand_singleton<1>(a0,p,s1)
                                        : gather_values<1>(a0,p,ex1);

      // Apply the function
      return boost::proto::value(boost::proto::child_c<2>(a0))(v0,v1);
    }

    // If dimension is a singleton, we know we just need to splat it all over
    template<std::size_t I> static BOOST_FORCEINLINE result_type
    expand_singleton(A0 const& a0, State const& p, std::size_t limit)
    {
      return  splat<result_type>
              ( nt2::run( boost::proto::child_c<I>(a0)
                        , (p / a0.extent()[0]) % limit
                        , meta::as_<typename meta::scalar_of<Data>::type>()
                        )
              );
    }

    // If not, we run a circular gather evaluation
    template<std::size_t I> static BOOST_FORCEINLINE result_type
    gather_values(A0 const& a0, State const& p, ext_t const& sz)
    {
      typedef typename meta::as_integer<result_type>::type  i_t;
      typename meta::call<nt2::tag::ind2sub_(ext_t,State)>::type
      pos = ind2sub(a0.extent(),p);

      for(size_t i = 0; i != ext_t::size(); ++i)
        pos[i] = (sz[i] < size_t(pos[i])) ? sz[i] : size_t(pos[i]);

      return  run ( boost::proto::child_c<I>(a0)
                  , enumerate<i_t>(sub2ind(sz, pos))
                  , Data()
                  );
    }
  };
} }

#endif
