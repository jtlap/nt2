//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_OUTER_FOLD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_OUTER_FOLD_HPP_INCLUDED

#include <nt2/core/functions/outer_fold.hpp>
#include <boost/fusion/include/pop_back.hpp>
#include <nt2/include/functions/scalar/numel.hpp>

namespace nt2 { namespace details
{
  template <class X, class N, class B, class U>
  BOOST_FORCEINLINE typename X::value_type
  outer_fold_step(X const& in, const std::size_t& p, const std::size_t& obound, N const& neutral, B const& bop, U const& uop)
  {
    typedef typename X::value_type   value_type;
    typedef typename X::extent_type  extent_type;
    extent_type ext = in.extent();

    std::size_t ibound  = ext[ext.size()-1];
    value_type out = neutral(nt2::meta::as_<value_type>());
      
    for(std::size_t i = 0, k=0; i < ibound; ++i, k+=obound)
    {
        out = bop(out, nt2::run(in, k + p, meta::as_<value_type>()));
    }
    
    return out;
  }
} }


namespace nt2 { namespace ext
{
  //============================================================================
  // Generates outer_fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::outer_fold_, tag::cpu_, (A0)(A1)(A2)(A3)(A4)
                            , ((ast_< A0, nt2::container::domain>))
                              ((ast_< A1, nt2::container::domain>))
                              (unspecified_<A2>)
                              (unspecified_<A3>)
                              (unspecified_<A4>)
                            )
  {
    typedef void                                                               result_type;
    typedef typename A0::value_type                                            value_type;
    typedef typename boost::remove_reference<A1>::type::extent_type            extent_type;

    BOOST_FORCEINLINE result_type operator()(A0& out, A1& in, A2 const& neutral, A3 const& bop, A4 const& uop) const
    {
      extent_type ext = in.extent();

      std::size_t numel  = 1;
      for(std::size_t m = 0; m!= ext.size()-1 ; ++m)
        numel*=ext[m];

      std::size_t obound = numel;//nt2::numel(boost::fusion::pop_back(ext));

      for(std::size_t j = 0; j < obound; ++j)
      {
          nt2::run(out, j, details::outer_fold_step(in, j, obound, neutral, bop, uop));
      }
    }

  };

} }

#endif
