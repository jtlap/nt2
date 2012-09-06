[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' :[ 'This is generally equivalent to abs except for signed integer',
                          'types for which \c abss(Valmin) is \c Valmax-1',
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
                 'boost::simd::Valmin<T>()' : 'boost::simd::Valmax<T>()',
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
                 'default' : ['boost::simd::abss(a0)'],
                },
             'property_value' : {
                 'default' : ['(a0>=0 ? a0 : (a0==boost::simd::Valmin<T>()?boost::simd::Valmax<T>():-a0))'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
