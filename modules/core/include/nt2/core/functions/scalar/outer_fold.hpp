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
#include <boost/fusion/include/pop_front.hpp>
#include <boost/fusion/include/pop_back.hpp>
#include <nt2/include/functions/numel.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates outer_fold
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::outer_fold_, tag::cpu_, (A0)(S0)(A1)(A2)(A3)(A4)
                            , ((expr_< table_< unspecified_<A0>, S0 >
                                     , nt2::tag::terminal_
                                     , boost::mpl::long_<0>
                                     >
                              ))
                              (ast_< A1>)
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

      typename A0::index_type::type bs;
      std::ptrdiff_t ilow   = boost::fusion::at_c<3>(bs);
      std::ptrdiff_t olow   = boost::fusion::at_c<0>(bs);
      std::ptrdiff_t ibound  = ext[ext.size()-1] + ilow;
      std::ptrdiff_t obound = olow + ext[0]*ext[1];//nt2::numel(boost::fusion::pop_back(ext));


      std::cout << "ilow " << ilow << "\n";
      std::cout << "olow " << olow << "\n";
      std::cout << "ext[ext.size()-1] " << ext[ext.size()-1] << "\n";
      std::cout << "ibound " << ibound << "\n";
      std::cout << "obound " << obound << "\n";

      // std::cout << "pop_back = " << boost::fusion::pop_back(ext) << "\n";
      // std::cout << "pop_front = " << boost::fusion::pop_front(ext)<< "\n";


      for(std::ptrdiff_t j = olow; j != obound; ++j){
        out(j,1) = neutral(nt2::meta::as_<value_type>());
        for(std::ptrdiff_t i = ilow; i != ibound; ++i){
          std::cout << "(" << j << ", " << i << ")\t";
          std::cout << out(j,1) << " + " << nt2::run(in, boost::fusion::vector_tie(j,i), meta::as_<value_type>()) << " = ";
          out(j,1) = bop(out(j,1), nt2::run(in, boost::fusion::vector_tie(j,i), meta::as_<value_type>()));
          std::cout << out(j,1) << "\t";
        }
        std::cout << "--> " <<out(j,1) << "\n";
      }

    }
  };

} }

#endif
