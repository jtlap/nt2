//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_REPMAT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_REPMAT_HPP_INCLUDED

#include <nt2/include/functor.hpp>
#include <nt2/core/container/dsl/details/generate_as.hpp>

namespace nt2
{
  namespace tag
  {
    struct  repmat_ : ext::elementwise_<repmat_>
    {
      typedef ext::elementwise_<repmat_> parent;
    };
  }

  // repmat(xpr, size)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::repmat_, repmat, 2)

  // repmat(xpr, n, m)
  NT2_FUNCTION_IMPLEMENTATION(nt2::tag::repmat_, repmat, 3)
}

namespace nt2 { namespace container { namespace ext
{
  template<class Domain, int N, class X>
  struct  size_of<nt2::tag::repmat_,Domain,N,X>
  {
    typedef typename  boost::proto::result_of::
                      child_c<X&,0>::value_type::extent_type    extent_t;
    typedef typename  boost::proto::result_of::
                      value < typename  boost::proto::result_of::
                                        child_c<X&,1>::type
                            >::type                             reps_t;

    typedef typename meta::strip<extent_t>::type                ext1_t;
    typedef typename meta::strip<reps_t>::type                  ext2_t;

    typedef typename  make_size < (ext1_t::static_size > ext2_t::static_size)
                                ? ext1_t::static_size
                                : ext2_t::static_size
                                >::type                         result_type;

    BOOST_FORCEINLINE result_type operator()(X& e) const
    {
      result_type that(boost::proto::child_c<0>(e).extent());
      reps_t      r(boost::proto::value(boost::proto::child_c<1>(e)));

      for(std::size_t i=0;i<ext2_t::static_size;++i)
        that[i] *= r[i];

      return that;
    }
  };

  template<class Domain, int N, class Expr>
  struct  value_type<nt2::tag::repmat_,Domain,N,Expr>
  {
    typedef typename meta::scalar_of< typename  boost::proto::result_of::
                                                child_c<Expr&,0>::type
                                    >::type                             base_t;
    typedef typename meta::strip<base_t>::type                          type;
  };
} } }

#endif
