#error "This file is for documentation purpose only."

/*!
 * \defgroup complex NT2 complex toolbox
 *
 * This module is devoted to the simd and scalar definition of
 * standard or mathematical functions that still bear a meaning when
 * extended to the complex plane.
 * It also defines some new functions that have no interest outside
 * of complex number scope.
 *
 * But for trivial functions the complex functions are NOT defined
 * for integral inputs the only for floating ones.
 *
 * As far as possible compatibility has been searched with C99 and
 * Matlab(TM). However they are sometimes not compatible.
 * a #ifdef soution can be taken if one seems to need it.
 *
 * What are the implied types :
 *   In scalar mode there are three complex template types
 *
 *   The first one is not a proper nt2 one but simply std::complex<T>
 *   where T can be float or double
 *
 *   An nt2::imaginary<T> type which only holds pure (null real part) complex
 *   An nt2::dry<T>       type which only real complex numbers (!)
 *
 * All complex functions can use an mix these 3 types together and with floating,
 * producing the smallest type (determined statically) able to hold the result,
 * but never floating if on of the three other is involved.
 * 
 * The dry<T> type is not T, it smells like T, it looks like T, but:
 *                      i = nt2::sqrt(dry<float>(-1.0f)) 
 * is of type nt2::imaginary<float> and of value satisfying as expected i*i == -1, 
 * opposite to nt2::sqrt(-1.0f)) returning Nan<float>() (not a number)
 *
 * So be dry, if you aim complex type results.
 *
 * Take care that std::complex being used the operator default to standard quite
 * easily. Don't hesitate to use nt2:: prefix.
 *
 * The currently implanted functors are submodule-wise:
 *
 * proper
 *        real : return a floating containing the real part value
 *        imag : return a floating containing the imaginary part value
 *        pure : return an imaginary containing the imaginary part
 *
 * arithmetic
 *
 *        abs       : modulus  (using hypot)
 *        arg       : argument (using atan2)
 *        average   : half sum
 *        ceil      : these four roundings act on real and imaginary parts
 *        floor
 *        round
 *        trunc
 *        conj      : conjugate
 *        dist      : abs(a0-a1)
 *        fma       : a0*a1+a2
 *        max       : max and min use sorting on modulus then argument
 *        min
 *        minusone  : a0-1
 *        oneminus  : 1-a0
 *        oneplus   : a0+1
 *        rec
 *        rsqrt
 *        sqr 
 *        sqr_abs  : square modulus sqr(real(a0))+sqr(imag(a0))
 *        sqrt
 *
 * exponential
 *
 *        exp10
 *        exp2
 *        exp    : exp(abs(a0))*(cos(a0)+isin(a0))
 *        expm1
 *        log10
 *        log1p
 *        log2
 *        log
 *        pow
 *        sqrt1pm1
 *
 * hyperbolic
 *
 * For trigonometric and hyperbolic the acos/asin acosh/asinh atan/atanh which
 * tightly and simply related functions we followed boost special_functions and
 * have rewritten a simd version.
 * The results can differ from matlab(TM), but a priori by being more accurate.
 *
 * cos(h) and sin(h) are simply written in terms of the real counterparts.
 *
 *        acosh
 *        asinh
 *        atanh
 *        cosh
 *        coth
 *        csch
 *        sech
 *        sinhcosh
 *        sinh
 *        tanh
 *
 * ieee
 *
 *        copysign : applies to real and imaginary parts,  the second parameter being floating
 *        eps      : eps(abs(a0))
 *        frac     : applies to real and imaginary parts
 *        ldexp    : multiplies the complex by 2^n n being the second and integral parameter
 *        negate   : the second parameter must be floating and the functor applies  to real and imaginary parts
 *        sign     : complex sign,  i.e. a0/abs(a0) (or 0)
 *        ulpdist  : maximum of the ulpdist applied on real and imaginary parts 
 *
 * operator
 *
 *        compare_equal         : these five are for stl iterator purposes
 *        compare_greater_equal
 *        compare_greater
 *        compare_less_equal
 *        compare_less
 *        compare_not_equal
 *        divides
 *        if_else
 *        minus
 *        multiplies
 *        plus
 *        splat
 *        unary_minus
 * predicates
 *
 * All order comparisons in predicates are made only on the real part (as in matlab)
 * It is of course not the case for equality tests.
 * Please note that a complex number can be infinite and nan simultaneously
 *
 *        is_equal
 *        is_equal_with_equal_nans
 *        is_eqz
 *        is_finite
 *        is_gez
 *        is_greater_equal
 *        is_greater
 *        is_gtz
 *        is_imag       : real part is 0  
 *        is_inf        : one of the a0 parts is infinite
 *        is_invalid    : one of the a0 parts is not finite
 *        is_less_equal
 *        is_less
 *        is_lez
 *        is_ltz
 *        is_nan         : one of the a0 parts is nan
 *        is_nez
 *        is_ngez
 *        is_ngtz
 *        is_nlez
 *        is_nltz
 *        is_not_equal
 *        is_not_equal_with_equal_nans
 *        is_not_greater_equal
 *        is_not_greater
 *        is_not_imag       : real part is not 0  
 *        is_not_infinite
 *        is_not_less_equal
 *        is_not_less
 *        is_not_nan        : both a0 parts are not nan
 *        is_not_real       : imaginary part is not 0  
 *        is_real           : imaginary part is 0 
 *
 * reduction
 *
 *        all.hpp
 *        any.hpp
 *        at_i.hpp
 *        maximum.hpp
 *        minimum.hpp
 *        nbtrue.hpp
 *        none.hpp
 *        posmax.hpp
 *        posmin.hpp
 *        sum.hpp
 *         
 * swar
 *
 *        cumsum.hpp
 *        group.hpp
 *        lookup.hpp
 *        put_first.hpp
 *        splatted_first.hpp
 *        splatted_maximum.hpp
 *        splatted_minimum.hpp
 *        splatted_prod.hpp
 *        splatted_second.hpp
 *        splatted_sum.hpp
 *        split.hpp
 *         
 * trigonometric
 *        
 *        acos.hpp
 *        asin.hpp
 *        atan.hpp
 *        cos.hpp
 *        cot.hpp
 *        csc.hpp
 *        sec.hpp
 *        sincos.hpp
 *        sin.hpp
 *        tan.hpp
 *
 */
