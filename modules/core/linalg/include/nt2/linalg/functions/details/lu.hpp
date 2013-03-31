// TODO - DISABLE COMPELTELY WHEN GESV IS DONE

    // Reverse conditioning evaluation
//     base_t rcond(char c = '1')
//     {
//       /* this method which is presumably faster provides results that depend on
//       // the lapack used version
//       // it seems that gecon is buggy (J.T.L. 28/2/2013)
//       //
//       //   base_t rc = 0;
//       //   tab_t aa = a_;
//       //   char norm = (c == 1) ? '1' : ((c == 0) ? 'o' : c);
//       //   base_t anorm = nt2::details::lange(&norm,  &n_,  &n_, aa.raw(), &ldlu_);
//       //   nt2::details::gecon(&norm, &n_,  lu_.raw(), &ldlu_, &anorm, &rc, &info_);
//       //   return rc;
//       //
//         So we switch to a direct computation
//       */

//       return nt2::rec(nt2::norm(a_, c)*nt2::norm(this->inv(false), c));
//     }

    // system rank
//     size_t rank(base_t epsi = nt2::Eps<base_t>()) //provisouare
//     {
//       //int32_t r = 0;
//       base_t thresh = nt2::max(n_, m_)*epsi*nt2::max(nt2::abs(nt2::diag_of(lu_)(_)));
//       return  size_t(sum(if_one_else_zero(gt(nt2::diag_of(lu_), thresh))(_)));

//       //       for(int i=1; i <= nt2::min(n_, m_); ++i)
//       //         {
//       //           if(nt2::abs(lu_(i, i)) > thresh) ++r;
//       //         }
//       //       return r;
//       //      nt2::inbtrue(nt2::abs(diag_of(lu_)) > nt2::max(n_, m_)*epsi*nt2::max(abs(diag_of(lu_()))) );
//     }

//     base_t absdet()
//     {
//       BOOST_ASSERT_MSG(m_ == n_, "non square matrix in determinant computation");
//       return nt2::prod(nt2::abs(nt2::diag_of(lu_)(_)));
//     }

//     type_t absdet(itype_t & exponent)
//     {
//       BOOST_ASSERT_MSG(m_ ==  n_, "non square matrix in determinant computation");
//       // compute e and return m for matrix determinant such that |det| = ldexp(m, e)
//       // if no overflow or underflow can occur,  with 0.5 < abs(m) < 1
//       // the exponent result is enough to know the order of magnitude of the determinant
//       // (between 0.5*2^e and 2^e if the mantissa is non zero)
//       // This routine is inspired from linpack http://www.netlib.org/linpack/dgedi.f
//       // that use ten power factor instead
//       type_t   m1 = One<type_t>();
//       exponent = Zero<itype_t>();
//       for(size_t i = 1;  i <= size_t(n_); ++i)
//       {
//         itype_t e;
//         m1 *=  nt2::abs(nt2::frexp(nt2::abs(lu_(i, i)), e));
//         exponent+= e;
//       }
//       if (is_eqz(m1)){
//         exponent = Zero<itype_t>();
//       }
//       return m1;
//     }

//     type_t det(itype_t & exponent)
//     {
//       BOOST_ASSERT_MSG(m_ ==  n_, "non square matrix in determinant computation");
//       // compute e and m for matrix determinant such that det = ldexp(m, e)
//       // if no overflow or underflow can occur,  with 0.5 < abs(m) < 1
//       // the exponent result is enough to know the order of magnitude of the determinant
//       // (between 0.5*2^e and 2^e if the mantissa is non zero)
//       // This routine is inspired from linpack http://www.netlib.org/linpack/dgedi.f
//       // that use ten power factor instead
//       type_t   m1 = One<type_t>();
//       exponent = Zero<itype_t>();
//       for(size_t i = 1;  i <= size_t(n_); ++i)
//       {
//         itype_t e;
//         m1 *=  nt2::frexp(nt2::abs(lu_(i, i)), e);
//         exponent+= e;
//       }
//       if (is_eqz(m1)){
//         exponent = Zero<itype_t>();
//       }
//       return m1*signdet(false);
//     }

//     template<class Xpr> void inplace_solve(Xpr& b )
//     {
//       BOOST_ASSERT_MSG(issquare(a_), "matrix must be square to use the lu solver");
//       nt2_la_int nrhs = nt2::size(b, 2);
//       nt2_la_int ldb  = b.leading_size();
//       tab_t x(b);
//       nt2_la_int ldx  = x.leading_size();
//       btab_t ferr(of_size(nrhs, 1)), berr(of_size(nrhs, 1));
//       btab_t r_(of_size(n_, 1)), c_(of_size(n_, 1));
//       char equed = 'N';
//       base_t rc = rcond();
//       nt2::details::gesvx(nt2::details::lapack_option('F'),
//                           nt2::details::lapack_option('N'),
//                           &n_, &nrhs,
//                           a_.raw(), &ldlu_,
//                           lu_.raw(), &ldlu_,
//                           ipiv_.raw(),
//                           &equed,
//                           r_.raw(),
//                           c_.raw(),
//                           b.raw(), &ldb,
//                           x.raw(), &ldx,
//                           &rc,
//                           ferr.raw(),
//                           berr.raw(),
//                           &info_,
//                           w_);
//       b = x;
//     }
