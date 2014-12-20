#error "This file is for documentation purpose only."
/*!
 * \ingroup toolbox
 * \defgroup blas blas functions access
 * \brief Allows easy access blas functions from nt2,
 * i.e functions from the Basic Linear Algebra Subroutine
 * \par
 * These functions provide a full access to BLAS routines through NT2 containers
 * and have roughly the same parameters as the original blas functions except
 * matrices dimensions that generally omitted and are only necessary when they
 * can't be deduced from the NT2 containers internal dimensions (for exemple in
 * band storage where an mxn array is stored in a (nx(kl+ku+1)) container: n can
 * be deduced but not* both kl and kd). In doubt, see the documentation of each
 * individual routine.
 *
 * However the parameter order is always respected,  all pure inputs parameter
 * are marked const and the output parameters are the same as in FORTRAN documentation.
 * \par
 * All d, s, c, z FORTRAN routines are groupes in a lone functor in which the letter
 * prefix is omitted. They reside in blas namespace.
 * for routines acting on symmetric or hermitian matrices,  i.e. routines syxxxx
 * or hexxxx,  we choose that for real types of elements the two calls
 * (wih he and sy) are identical,  the rationale being that as a real symmetric
 * matrix is hermitian and conversely.
 * \par
 * Some utilities (not implementing any blas functions) of names (un)band, (un)band_h or
 * (un)pack are also provided to convert dense storage to packed or band
 * storage and conversly. However these routines are merely given to test
 * or display purposes and can be slow.
**/
