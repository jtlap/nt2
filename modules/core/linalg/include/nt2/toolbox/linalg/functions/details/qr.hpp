/*******************************************************************************
 *         Copyright 2003-2012 LASMEA UMR 6602 CNRS/U.B.P
 *         Copyright 2011-2012 LRI    UMR 8623 CNRS/Univ Paris Sud XI
 *
 *          Distributed under the Boost Software License, Version 1.0.
 *                 See accompanying file LICENSE.txt or copy at
 *                     http://www.boost.org/LICENSE_1_0.txt
 ******************************************************************************/
#ifndef NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_QR_HPP_INCLUDED
#define NT2_TOOLBOX_LINALG_FUNCTIONS_DETAILS_QR_HPP_INCLUDED
// Matlab syntaxes
// Note that the syntaxes can be obtained using qr and pqr
// These 2 are qr ie no_p
//    [q,r] = qr(a), where a is m-by-n, produces an m-by-n upper triangular
//     matrix r and an m-by-m unitary matrix q so that a = q*r.

//     [q,r] = qr(a,0) produces the "economy size" decomposition.
//     if m>n, only the first n columns of q and the first n rows of r are
//     computed. if m<=n, this is the same as [q,r] = qr(a).

// and also these
//     x = qr(a) and x = qr(a,0) return the output of lapack's *geqrf routine.
//     (values() in the class)
//     triu(x) is the upper triangular factor r.
//////////// TODO
// to get the econmy size we much expand the results to the liked dimensions
////////////
// The others use pqr

//     if a is full:

//     [q,r,p] = qr(a) produces unitary q, upper triangular r and a
//     permutation matrix p so that a*p = q*r. the column permutation p is
//     chosen so that abs(diag(r)) is decreasing.

//     [q,r,p] = qr(a,'vector') returns the permutation information as a
//     vector instead of a matrix.  that is, p is a row vector such that
//     a(:,p) = q*r. similarly, [q,r,p] = qr(a,'matrix') returns a permutation
//     matrix e. this is the default behavior.

//     [q,r,p] = qr(a,0) produces an "economy size" decomposition in which p
//     is a permutation vector, so that a(:,p) = q*r.


#include <nt2/toolbox/linalg/details/utility/workspace.hpp>
#include <nt2/toolbox/linalg/details/utility/options.hpp>
#include <nt2/include/functions/qr.hpp>
#include <nt2/include/functions/of_size.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/include/functions/prod.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/first_index.hpp>
#include <nt2/include/functions/diag_of.hpp>
#include <nt2/include/functions/if_one_else_zero.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/toolbox/linalg/details/lapack/geqp3.hpp>
#include <nt2/toolbox/linalg/details/lapack/geqrf.hpp>
#include <nt2/toolbox/linalg/details/lapack/gqr.hpp>
#include <nt2/toolbox/linalg/details/lapack/mqr.hpp>
#include <nt2/toolbox/linalg/details/lapack/trtrs.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>
namespace nt2 {
  struct no_p {};

  namespace details
  {
    template<class T> struct qr_result
    {
      typedef typename meta::strip<T>::type                   source_t;
      typedef typename source_t::value_type                     type_t;
      typedef typename source_t::index_type                    index_t;
      typedef typename meta::as_real<type_t>::type              base_t;
      typedef typename meta::as_integer<base_t, signed>::type  itype_t;
      typedef T                                                 data_t;
      typedef nt2::container::table<type_t,nt2::_2D>                        tab_t;
      typedef nt2::container::table<base_t,nt2::_2D>                       btab_t;
      typedef nt2::container::table<itype_t,nt2::_2D>                      itab_t;
      typedef nt2::details::workspace<type_t>              workspace_t;
      typedef nt2::container::table<nt2_la_int,nt2::_2D>                   ibuf_t;
      typedef nt2::container::table<type_t,index_t>                   result_type;
      typedef nt2::container::table<itype_t,index_t>                 iresult_type;


      template<class Input>
      qr_result ( Input& xpr, const char & nop)
        : a_(xpr)
        , aa_(xpr)
        , m_(nt2::height(xpr))
        , n_(nt2::width(xpr))
        , k_(nt2::min(m_, n_))
        , lda_(a_.leading_size())
        , jpvt_(nt2::zeros(n_,1, meta::as_<nt2_la_int>()))
        , tau_(nt2::of_size(k_,1))
        , info_(0)
        , nop_(nop)
        , q_(of_size(0, 1))
        , p_(of_size(0, 1))
        , jp_(of_size(0, 1))
      {
        if (nop_ != 'N')
        {
          nt2::details::geqp3(&m_, &n_, aa_.raw(), &lda_,
                              jpvt_.raw(), tau_.raw(), &info_);
        }
        else
        {
          nt2::details::geqrf(&m_, &n_, aa_.raw(), &lda_,
                              tau_.raw(), &info_, wrk_);
        }
      }

      qr_result(qr_result const& src)
        : a_(src.a_),aa_(src.aa_),m_(src.m_),n_(src.n_),
          k_(src.k_),lda_(src.lda_),jpvt_(src.jpvt_),
          tau_(src.tau_),info_(src.info_),
          nop_(src.nop_), q_(src.q_), p_(src.p_), jp_(src.jp_)
      {}

      qr_result& operator=(qr_result const& src)
      {
        a_      = src.a_;
        aa_     = src.aa_;
        m_      = src.m_;
        n_      = src.n_;
        k_      = src.k_;
        lda_    = src.lda_;
        jpvt_   = src.jpvt_;
        tau_    = src.tau_;
        info_   = src.info_;
        nop_    =  src.nop_;
        q_      =  src.q_;
        p_      =  src.p_;
        jp_      =  src.jp_;
        return *this;
      }
      data_t values() const { return a_; }
      const tab_t& qr() const { return aa_; }

      const tab_t& q ()
      {
        if (isempty(q_))
        {
          nt2_la_int info;
          if (nop_ == 'N')
          {
            nt2_la_int nn = nt2::min(k_, n_);
            q_ = expand(aa_, of_size(m_, nn));
            nt2::details::gqr(&m_, &nn, &k_, q_.raw(), &lda_, tau_.raw(), &info);
          }
          else
          {
            q_ = expand(aa_, of_size(m_, m_));
            nt2::details::gqr(&m_, &m_, &k_, q_.raw(), &lda_, tau_.raw(), &info);
          }
        }
        return q_;
      }
      typedef typename meta::call < tag::colon_(int32_t, int32_t)>::type T0;
      typedef typename meta::call < tag::function_(tab_t, T0, nt2::container::colon_)>::type T1;
      typedef typename meta::call < tag::triu_(T1)>::type  r_result;
      r_result r()const
      {
        int32_t nn = (nop_ == 'N')? k_ : m_;
        return triu(aa_(nt2::_(1, nn), nt2::_));
      }

      const tab_t& p()
      {
        if (isempty(p_))
        {
          if (nop_ == 'N')
          {
            p_ = nt2::eye(n_, n_, meta::as_<type_t>());
          }
          else
          {
            p_ = nt2::zeros(nt2::numel(jpvt_), nt2::meta::as_<type_t>());
            for(unsigned int i=1; i <= nt2::size(p_, 1) ; ++i)
            {
              p_(jpvt_(i), i) = One<type_t>();
            }
          }
        }
        return p_;
      }

      const itab_t& jp()
      {
        if (isempty(jp_))
        {
          itype_t start = first_index<1>(a_); //boost::mpl::at_c<index_t, 0>::type::value;
          if (nop_)
          {
            jp_ = _(start, n_+start-1);
          }
          else
          {
            jp_.resize(of_size(1, numel(jpvt_)));
            for(size_t i=1; i <= numel(jpvt_); ++i) jp_(i) = jpvt_(i)+start-1;
          }
        }
        return jp_;
      }
      nt2_la_int status() const { return info_; }

      size_t     rank(base_t epsi = nt2::Eps<base_t>())const
      {
        base_t thresh = nt2::max(n_, m_)*epsi*nt2::max(nt2::abs(diag_of(aa_)(_)));
        return  size_t(sum(if_one_else_zero(gt(nt2::abs(nt2::diag_of(aa_)), thresh))(_)));
      }

      base_t absdet()const{
        BOOST_ASSERT_MSG(m_ == n_, "non square matrix in determinant computation");
        return nt2::prod(nt2::abs(diag_of(aa_)(_)));
      }

      //==========================================================================
      // Solver interface
      //==========================================================================
      template<class XPR> result_type solve(const XPR & b, base_t epsi = nt2::Eps<base_t>(),
                                            bool transpose = false)const
      {
        result_type bb = b;
        inplace_solve(bb, epsi, transpose);
        return bb;
      }

      template<class XPR, class OUT> void solve(const XPR & b, OUT& x, base_t epsi = nt2::Eps<base_t>(),
                                                bool transpose = false)const
      {
        x = b;
        inplace_solve(x, epsi, transpose);
      }

      template < class XPR > void inplace_solve(XPR & b, base_t epsi = nt2::Eps<base_t>(),
                                                bool transpose = false) const
      {
        typedef typename meta::is_complex<type_t>::type iscplx_t;
        char side = 'L';
        char tr = (!transpose) ?  ((iscplx_t::value)? 'C':'T') : 'N';
        nt2_la_int M = nt2::size(b, 1), N = nt2::size(b, 2);
        nt2_la_int ldb = b.leading_size();
        nt2_la_int info;
        nt2::details::mqr(&side, &tr, &M, &N, &k_, aa_.raw(), &lda_, tau_.raw(), b.raw(), &ldb, &info, wrk_);
        nt2_la_int nrhs = size(b, 2);
        char uplo =  'U', d = 'N';
        nt2_la_int rk = rank(epsi);
        tr = (transpose) ?  ((iscplx_t::value)? 'C':'T') : 'N';
        nt2::details::trtrs(&uplo, &tr, &d, &rk, &nrhs, aa_.raw(), &lda_, b.raw(), &ldb, &info);
        if (!nop_) b = permute(b);
        if (N == 1)
          b.resize(of_size(n_, 1));
        else if(M != n_)
          b = expand(b, of_size(n_, N));
      }

    private :

      inline tab_t permute(const tab_t& bb) const
      {
        tab_t res(nt2::of_size(nt2::numel(jpvt_), nt2::size(bb, 2)));
        const size_t m =  nt2::min(size(bb, 1), numel(jpvt_));
////        res(jpvt_(nt2::_(1, m)), nt2::_) = bb;
        for(size_t i=1; i <= m; ++i)
        {

          for(size_t j=1; j <= nt2::size(bb, 2); ++j)
          {
            res(jpvt_(i), j) = bb(i, j);
          }
////          res(jpvt_(i), _) = bb(i, _);
        }
        return res;
      }

      data_t                 a_;
      tab_t                 aa_;
      nt2_la_int     m_, n_, k_;
      nt2_la_int           lda_;
      ibuf_t              jpvt_;
      tab_t                tau_;
      nt2_la_int          info_;
      char                 nop_;
      mutable workspace_t  wrk_;
      tab_t                  q_;
      tab_t                  p_;
      itab_t                jp_;

    };

  }
}
#endif
