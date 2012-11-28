[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : [ "The function always returns a value of the same type than the entry.",
                           "\par",
                           "Take care that for signed integers the absolute value of Valmin is Valmin",
                           "(thus negative!).",
                           "This is a side effect of the 2-complement representation  of integers.",
                           "To avoid this,  you can use the \c abss saturated functor or convert the",
                           "input parameter to a larger type before taking the abs value.",
                           ],
         'module' : 'boost',
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'notes' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
         'simd_types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 30/11/2010',
             'cover_included' : ['#include <boost/simd/toolbox/standard/include/functions/abs.hpp>'],
             'no_ulp' : 'True',
             'stamp' : 'modified by jt the 13/12/2010',
            },
         'ranges' : {
             'default' : [['boost::simd::Valmin<T>()', 'boost::simd::Valmax<T>()']],
             'real_' : [['T(-100)', 'T(100)']],
             'signed_int_' : [['T(-100)', 'T(100)']],
             'unsigned_int_' : [['T(0)', 'T(100)']],
            },
         'specific_values' : {
             'real_' : {
                 'boost::simd::Inf<T>()' : 'boost::simd::Inf<T>()',
                 'boost::simd::Minf<T>()' : 'boost::simd::Inf<T>()',
                 'boost::simd::Mone<T>()' : 'boost::simd::One<T>()',
                 'boost::simd::Nan<T>()' : 'boost::simd::Nan<T>()',
                 'boost::simd::One<T>()' : 'boost::simd::One<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                 'boost::simd::Valmax<T>()' : 'boost::simd::Valmax<T>()',
                 'boost::simd::Valmin<T>()' : 'boost::simd::Valmax<T>()',
                 'T(1)':'T(1)',
                },
             'signed_int_' : {
                 'boost::simd::Mone<T>()' : 'boost::simd::One<T>()',
                 'boost::simd::One<T>()' : 'boost::simd::One<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                 'boost::simd::Valmax<T>()' : 'boost::simd::Valmax<T>()',
                 'boost::simd::Valmin<T>()' : 'boost::simd::Valmin<T>()',
                },
             'unsigned_int_' : {
                 'boost::simd::One<T>()' : 'boost::simd::One<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                 'boost::simd::Valmin<T>()' : 'boost::simd::Valmin<T>()',
                 'boost::simd::Valmax<T>()' : 'boost::simd::Valmax<T>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::abs(a0)'],
                },
             'property_value' : {
                 'default' : ['a0>0 ? T(a0) : T(-a0)'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
