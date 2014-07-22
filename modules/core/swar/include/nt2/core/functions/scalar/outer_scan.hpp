//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_OUTER_SCAN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_OUTER_SCAN_HPP_INCLUDED

#include <nt2/core/functions/outer_scan.hpp>
#include <nt2/core/functions/details/scan_step.hpp>
#include <boost/fusion/include/pop_front.hpp>
#include <nt2/include/functions/scalar/numel.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // General outer_scan
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::outer_scan_, tag::cpu_
                            , (Out)(In)(Neutral)(Bop)(Uop)
                            , ((ast_< Out, nt2::container::domain>))
                              ((ast_< In, nt2::container::domain>))
                              (unspecified_<Neutral>)
                              (unspecified_<Bop>)
                              (unspecified_<Uop>)
                            )
  {
    typedef void                                                              result_type;
    typedef typename Out::value_type                                          value_type;
    typedef typename In::extent_type                                          extent_type;

    BOOST_FORCEINLINE result_type
    operator()(Out& out, In& in, Neutral const& neutral, Bop const& bop, Uop const& uop) const
    {
      extent_type ext = in.extent();
      std::size_t obound =  boost::fusion::at_c<2>(ext);

      nt2::outer_scan(out,in,neutral,bop,uop,std::make_pair(0,obound));
    }
  };

  //============================================================================
  // Generates outer_scan
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::outer_scan_, tag::cpu_, (Out)(In)(Neutral)(Bop)(Uop)(Range)
                            , ((ast_< Out, nt2::container::domain>))
                              ((ast_< In, nt2::container::domain>))
                              (unspecified_<Neutral>)
                              (unspecified_<Bop>)
                              (unspecified_<Uop>)
                              (unspecified_<Range>)
                            )
  {
    typedef void                                                               result_type;
    typedef typename Out::value_type                                            value_type;
    typedef typename boost::remove_reference<In>::type::extent_type            extent_type;

    BOOST_FORCEINLINE result_type
    operator()( Out& out, In& in , Neutral const& neutral
              , Bop const& bop   , Uop const&
              , Range const& range
              ) const
    {
      extent_type ext = in.extent();

      std::size_t ibound  = boost::fusion::at_c<0>(ext);
      std::size_t mbound =  boost::fusion::at_c<1>(ext);
      std::size_t iboundxmbound = ibound * mbound;

      std::size_t begin = range.first;
      std::size_t size = range.second;

      for(std::size_t o = begin, o_ = begin * iboundxmbound;
          o < size;
          ++o, o_+=iboundxmbound)
      {
        for(std::size_t i = 0, i_ = o_; i < ibound; ++i, ++i_)
        {
          value_type summary = neutral(nt2::meta::as_<value_type>());
          summary = details::scan_step(summary, out, in, bop, i_, mbound, ibound, false);
        }
      }
    }
  };
} }

#endif
