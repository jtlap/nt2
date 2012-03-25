[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ["returns saturation of \f$-a_0\f$ in the input type."],
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
         'types' : ['real_', 'signed_int_'],
         'simd_types' : ['real_', 'signed_int_'],     
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
                 'boost::simd::Inf<T>()' : 'boost::simd::Minf<T>()',
                 'boost::simd::Minf<T>()' : 'boost::simd::Inf<T>()',
                 'boost::simd::Mone<T>()' : 'boost::simd::One<T>()',
                 'boost::simd::Nan<T>()' : 'boost::simd::Nan<T>()',
                 'boost::simd::One<T>()' : 'boost::simd::Mone<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                 'boost::simd::Valmax<T>()' : 'boost::simd::Valmin<T>()',
                 'boost::simd::Valmin<T>()' : 'boost::simd::Valmax<T>()',
                 'T(100)':'T(-100)',   
                },
             'signed_int_' : {
                 'boost::simd::Mone<T>()' : 'boost::simd::One<T>()',
                 'boost::simd::One<T>()' : 'boost::simd::Mone<T>()',
                 'boost::simd::Zero<T>()' : 'boost::simd::Zero<T>()',
                 'boost::simd::Valmax<T>()' : '-boost::simd::Valmax<T>()',
                 'boost::simd::Valmin<T>()' : 'boost::simd::Valmax<T>()',
                 'T(100)':'T(-100)',   
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['boost::simd::negs(a0)'],
                },
             'property_value' : {
                 'signed_int_' : ['(a0>boost::simd::Valmin<T>() ? -a0 : boost::simd::Valmax<T>())'],
                 'real_'       :  ['-a0'],   
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
