[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ["The function computes the remainder of dividing a0 by a1.",
                          "The return value is a0-n*a1, where n is the value a0/a1,",
                          "rounded to the nearest integer.",
                          "If the absolute value of a0-n*a1 is 0.5, n is chosen to be even.",
                          "\par",
                          "if one prefer: if a1 is zero returns a0, else return",
                          "a0-divround(a0,a1)*a1"],
         'module' : 'boost',
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::common_type<T>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 01/12/2010',
             'included' : ['#include <boost/simd/include/functions/idivround.hpp>'],
             'notes' :
                ['The remainder() function computes the remainder of dividing x by y.',
                 'The return value is x-n*y, where n is the value x / y,',
                 'rounded to the nearest integer.  If the absolute value of x-n*y is 0.5,',
                 'n is chosen to be even. The drem() function does precisely the same thing.'],
             'stamp' : 'modified by jt the 13/12/2010',
            },
         'ranges' : {
             'real_' : [['T(-10)', 'T(10)'], ['T(-10)', 'T(10)']],
             'signed_int_' : [['-100', '100'], ['1', '100']],
             'default' : [['0', '100'], ['1', '100']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'boost::simd::Inf<T>()' : 'boost::simd::Nan<T>()',
                 'boost::simd::Minf<T>()' : 'boost::simd::Nan<T>()',
                 'boost::simd::Mone<T>()' : 'boost::simd::Zero<T>()',
                 'boost::simd::Nan<T>()' : 'boost::simd::Nan<T>()',
                 'boost::simd::One<T>()' : 'boost::simd::Zero<T>()',
                 'boost::simd::One<T>(),boost::simd::Zero<T>()' : 'boost::simd::Nan<T>()',
                 'boost::simd::Zero<T>(),boost::simd::Zero<T>()' : 'boost::simd::Nan<T>()',
                },
             'signed_int_' : {
                 'boost::simd::Mone<T>()' : 'boost::simd::Zero<T>()',
                 'boost::simd::One<T>()' : 'boost::simd::Zero<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                },
             'unsigned_int_' : {
                 'boost::simd::One<T>()' : 'boost::simd::Zero<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::remainder(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['a0-boost::simd::idivround(a0, a1)*a1'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
