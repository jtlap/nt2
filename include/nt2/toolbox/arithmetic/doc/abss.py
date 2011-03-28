[ ## this file was manually modified by jt
    {
     'functor' : {
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
             'included' : ['#include<nt2/toolbox/standard/include/abs.hpp>'],
             'no_ulp' : 'True',
             'stamp' : 'modified by jt the 13/12/2010',
            },
         'ranges' : {
             'default' : [['nt2::Valmin<T>()', 'nt2::Valmax<T>()']],
             'real_' : [['T(-100)', 'T(100)']],
             'signed_int_' : [['T(-100)', 'T(100)']],
             'unsigned_int_' : [['T(0)', 'T(100)']],
            },
         'specific_values' : {
             'real_' : {
                 'nt2::Inf<T>()' : 'nt2::Inf<T>()',
                 'nt2::Minf<T>()' : 'nt2::Inf<T>()',
                 'nt2::Mone<T>()' : 'nt2::One<T>()',
                 'nt2::Nan<T>()' : 'nt2::Nan<T>()',
                 'nt2::One<T>()' : 'nt2::One<T>()',
                 'nt2::Zero<T>()' : 'nt2::Zero<T>()',
                 'nt2::Valmax<T>()' : 'nt2::Valmax<T>()',
                 'nt2::Valmin<T>()' : 'nt2::Valmax<T>()',
                 'T(1)':'T(1)',   
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' : 'nt2::One<T>()',
                 'nt2::One<T>()' : 'nt2::One<T>()',
                 'nt2::Zero<T>()' : 'nt2::Zero<T>()',
                 'nt2::Valmax<T>()' : 'nt2::Valmax<T>()',
                 'nt2::Valmin<T>()' : 'nt2::Valmax<T>()',
                },
             'unsigned_int_' : {
                 'nt2::One<T>()' : 'nt2::One<T>()',
                 'nt2::Zero<T>()' : 'nt2::Zero<T>()',
                 'nt2::Valmin<T>()' : 'nt2::Valmin<T>()',
                 'nt2::Valmax<T>()' : 'nt2::Valmax<T>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::abss(a0)'],
                },
             'property_value' : {
                 'default' : ['(a0>=0 ? a0 : (a0==nt2::Valmin<T>()?nt2::Valmax<T>():-a0))'],
                },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
