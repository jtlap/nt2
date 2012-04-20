//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_CHOL_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_CHOL_HPP_INCLUDED

#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/tril.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/leading_size.hpp>
#include <nt2/toolbox/linalg/details/lapack/potrf.hpp>
#include <nt2/toolbox/linalg/details/lapack/potrs.hpp>
#include <nt2/toolbox/linalg/details/lapack/pocon.hpp>
#include <nt2/toolbox/linalg/details/lapack/lange.hpp>

namespace nt2 { namespace details
{
  template<class T> struct cholesky_result
  {
    typedef typename meta::strip<T>::type                   source_t;
    typedef typename source_t::value_type                   type_t;
    typedef typename source_t::index_type                   index_t;
    typedef typename meta::as_real<type_t>::type            base_t;
    typedef T                                               data_t;
    typedef nt2::table<type_t,index_t>                      result_type;

    template<class Input>
    cholesky_result ( char uplo, Input& xpr )
                    : values_(xpr)
                    , height_( nt2::height(xpr) )
                    , leading_( nt2::leading_size(values_) )
                    , info_(0)
                    , uplo_(uplo)
    {
      nt2::details::potrf ( &uplo_, &height_
                          , boost::proto::value(values_).raw()
                          , &leading_, &info_
                          );
    }

    //==========================================================================
    // Return raw values
    //==========================================================================
    data_t values() const { return values_; }

    //==========================================================================
    // Return properly formatted result depending on up/low options
    //==========================================================================
    result_type result() const
    {
      result_type that;
      if(uplo_ == 'U')  that = nt2::triu(values_);
      else              that = nt2::tril(values_);

      // TODO Add expand to trim too [p-1 p-1] size
      ////if(p > 0) that = nt2::expand(that, nt2::of_size(p-1,p-1) );
      return that;
    }

    //==========================================================================
    // Return upper formatted result
    // TODO Add expand to trim too [p-1 p-1] size
    //==========================================================================
    typename meta::call<tag::triu_(data_t const&)>::type upper_result() const
    {
      BOOST_ASSERT_MSG( (uplo_ == 'U')
                      , "Lower Cholesky can't return upper result"
                      );
      return nt2::triu(values_);
    }

    //==========================================================================
    // Return upper formatted result
    // TODO Add expand to trim too [p-1 p-1] size
    //==========================================================================
    typename meta::call<tag::tril_(data_t const&)>::type lower_result() const
    {
      BOOST_ASSERT_MSG( (uplo_ == 'L')
                      , "Upper Cholesky can't return lower result"
                      );
      return nt2::tril(values_);
    }

    //==========================================================================
    // Return post-computation status
    //==========================================================================
    nt2_la_int  status() const { return info_; }

    //==========================================================================
    // Reverse conditioning evaluation
    //==========================================================================
    base_t rcond() const
    {
      char norm = '1';
      base_t anorm = nt2::details::lange( &norm,  &height_,  &height_
                                        , values_.raw(), &leading_
                                        );

      base_t res;
      nt2::details::pocon ( &uplo_, &height_
                          , boost::proto::value(values_).raw()
                          , &leading_
                          , &anorm, &res, &info_
                          );

      return res;
    }

    //==========================================================================
    // Solver interface
    //==========================================================================
    template<class XPR> result_type solve(const XPR& b ) const
    {
      result_type bb = b;
      inplace_solve(bb);
      return bb;
    }

    template<class Xpr> void inplace_solve(Xpr& b ) const
    {
      long int nrhs       = nt2::size(b, 1);
      long int leading_b  = nt2::leading_size(b);

      nt2::details::potrs ( &uplo_, &height_, &nrhs
                          , boost::proto::value(values_).raw()
                          , &leading_
                          , b.raw()         , &leading_b
                          , &info_
                          );
    }

    private:
    data_t      values_;
    nt2_la_int  height_, leading_, info_;
    char        uplo_;
  };
} }

#endif
