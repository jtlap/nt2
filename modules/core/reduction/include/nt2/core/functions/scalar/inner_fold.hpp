//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_INNER_FOLD_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_INNER_FOLD_HPP_INCLUDED

#include <nt2/core/functions/inner_fold.hpp>
#include <nt2/core/functions/inner_fold_step.hpp>
#include <boost/fusion/include/pop_front.hpp>
#include <nt2/include/functions/scalar/numel.hpp>
#include <nt2/include/functor.hpp>

namespace nt2 { namespace ext
{

  //============================================================================
  // General inner_fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::inner_fold_, tag::cpu_
                              , (A0)(A1)(A2)(A3)(A4)
                              , ((ast_< A0, nt2::container::domain>))
                                ((ast_< A1, nt2::container::domain>))
                                (unspecified_<A2>)
                                (unspecified_<A3>)
                                (unspecified_<A4>)
                             )
  {
    typedef void                                                              result_type;
    typedef typename A1::extent_type                                          extent_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& out, A1& in, A2 const& neutral, A3 const& bop, A4 const& uop) const
    {
      extent_type ext = in.extent();
      std::size_t obound = nt2::numel(boost::fusion::pop_front(ext));

      nt2::inner_fold(out,in,neutral,bop,uop,std::make_pair(0,obound));
    }
  };

  //============================================================================
  // Generates inner_fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::inner_fold_, tag::cpu_
                            , (A0)(A1)(A2)(A3)(A4)(A5)
                            , ((ast_< A0, nt2::container::domain>))
                              ((ast_< A1, nt2::container::domain>))
                              (unspecified_<A2>)
                              (unspecified_<A3>)
                              (unspecified_<A4>)
                              (unspecified_<A5>)
                            )
  {
    typedef void                                                               result_type;
    typedef typename A0::value_type                                            value_type;
    typedef typename boost::remove_reference<A1>::type::extent_type            extent_type;

    BOOST_FORCEINLINE result_type operator()(A0& out, A1& in
                                            , A2 const& neutral, A3 const& bop, A4 const& uop
                                            , A5 const& a5
                                            ) const
    {
      extent_type ext = in.extent();
      std::size_t ibound  = boost::fusion::at_c<0>(ext);
      std::size_t obound =  nt2::numel(boost::fusion::pop_front(ext));
      std::size_t begin = a5.first;
      std::size_t size = a5.second;

      for(std::size_t j = begin, k = begin*ibound; j < begin+size; ++j, k+=ibound)
      {
          value_type s_out;
          s_out = neutral(nt2::meta::as_<value_type>());

          nt2::inner_fold_step(s_out,in,neutral,bop,std::make_pair(k,ibound));

          nt2::run(out, j, s_out);
      }

    }

    };

  } }

#endif
