//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2015          J.T. Lapreste
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTERPOL_FUNCTIONS_GENERIC_NEAREST_HPP_INCLUDED
#define NT2_INTERPOL_FUNCTIONS_GENERIC_NEAREST_HPP_INCLUDED

#include <nt2/interpol/functions/nearest.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/is_equal.hpp>
#include <nt2/include/functions/issorted.hpp>
#include <nt2/include/functions/isvector.hpp>
#include <nt2/include/functions/if_else.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/sdk/meta/as_integer.hpp>
#include <boost/assert.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/interpol/functions/details/bsearch.hpp>
#include <nt2/interpol/functions/details/extrapol.hpp>


namespace nt2 { namespace ext
{
  BOOST_DISPATCH_IMPLEMENT  ( nearest_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_<arithmetic_<A0> > )
                              (unspecified_<A1> )
                              (unspecified_<A2> )
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE
    result_type operator()(const A0 &, const A1 &, const A2 &) const

    {
      BOOST_ASSERT_MSG(false, "Interpolation requires at least two sample points in each dimension.");
      return Nan<A0>();
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( nearest_, tag::cpu_
                            , (A0)(A1)(A2)(A3)
                            , (scalar_<arithmetic_<A0> > )
                              (unspecified_<A1> )
                              (unspecified_<A2> )
                              (unspecified_<A3> )
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE
    result_type operator()(const A0 &, const A0 & , const A0 & , const A0 & ) const
    {
      BOOST_ASSERT_MSG(false, "Interpolation requires at least two sample points in each dimension.");
      return  Nan<A0>();
    }
  };

  BOOST_DISPATCH_IMPLEMENT  ( run_assign_, tag::cpu_
                            , (A0)(A1)(N1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::nearest_,N1,nt2::container::domain>))
                            )
  {
    typedef typename boost::proto::result_of::child_c<A1&,0>::value_type  child0;
    typedef typename boost::proto::result_of::child_c<A1&,1>::value_type  child1;
    typedef typename boost::proto::result_of::child_c<A1&,2>::value_type  child2;
    typedef typename child0::value_type                               value_type;
    typedef typename meta::as_integer<value_type>::type               index_type;
    typedef typename A0::value_type                                    sale_type;
    typedef A0&                                                      result_type;

    result_type operator()(A0& yi, A1& inputs) const
    {
      const child0 & x  =  boost::proto::child_c<0>(inputs);
      if (numel(x) <=  1)
        BOOST_ASSERT_MSG(numel(x) >  1, "Interpolation requires at least two sample points in each dimension.");
      else
      {
        BOOST_ASSERT_MSG(issorted(x, 'a'), "for 'nearest' interpolation x values must be sorted in ascending order");
        const child1 & y   =  boost::proto::child_c<1>(inputs);
        BOOST_ASSERT_MSG((numel(x) == height(y) || (isvector(y) && (numel(x) == numel(y))))
                        , "The grid vectors do not define a grid of points that match the given values.");
        const child2 & xi0  =  boost::proto::child_c<2>(inputs);
        auto xi =  rowvect(xi0);
        bool extrap = false;
        value_type extrapval = Nan<value_type>();
        choices(inputs, extrap, extrapval, N1());
        table<index_type> index;
        details::bsearch (index, x, xi);
        table<value_type>  dx    =  xi-x(index);
        table<index_type> indexp1 =  oneplus(index);
        auto test = nt2::if_else(lt(nt2::abs(xi-x(index)), nt2::abs(xi-x(indexp1))), index,  indexp1);
        if(isvector(y))
        {
          yi = y(test);
        }
        else
        {
          yi = y(test, nt2::_);
        }
        if (!extrap)
        {
          auto sizee = of_size(height(xi0), width(xi0), width(y)); // this is incorrect if xi0 is properly _3D
          details::extrapol(yi, x, xi, extrapval, sizee);
        }
      }
      return yi;
    }
  private :
    static void choices(const A1&, bool &,  value_type&, boost::mpl::long_<3> const &)
    { }
    static void choices(const A1& inputs, bool & extrap,  value_type& extrapval, boost::mpl::long_<4> const &)
    {
        typedef typename boost::proto::result_of::child_c<A1&,3>::type             child3;
        typedef typename meta::scalar_of<child3>::type                    cref_param_type;
        typedef typename meta::strip<cref_param_type>::type                    param_type;
        get(inputs, extrap, extrapval, param_type());
      }
    static void get(const A1& inputs, bool & extrap,  value_type&,  const bool &)
      {
        extrap =  boost::proto::child_c<3>(inputs);
      }
    static void get(const A1& inputs, bool &,  value_type& extrapval,  const value_type &)
      {
        extrapval =  boost::proto::child_c<3>(inputs);
      }
  };
} }


#endif
