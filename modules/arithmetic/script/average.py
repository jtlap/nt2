[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'T',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_', 'signed_int_', 'unsigned_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 28/11/2010',
             'included' : ['#include<nt2/include/functions/round.hpp>'],
             'cover_included' : ['#include<nt2/include/functions/iround.hpp>'],
             'notes' : ['for integer values average does not coincide with (a0+a1)/2 by at most one unit.'],
             'stamp' : 'modified by jt the 13/12/2010',
            },
         'ranges' : {
             'real_' : [['T(-100)', 'T(100)'], ['T(-100)', 'T(100)']],
             'signed_int_' : [['T(-100)', 'T(100)'], ['T(-100)', 'T(100)']],
             'unsigned_int_' : [['T(0)', 'T(100)'], ['T(0)', 'T(100)']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'nt2::Inf<T>()' : 'nt2::Inf<T>()',
                 'nt2::Minf<T>()' : 'nt2::Minf<T>()',
                 'nt2::Mone<T>()' : 'nt2::Mone<T>()',
                 'nt2::Nan<T>()' : 'nt2::Nan<T>()',
                 'nt2::One<T>()' : 'nt2::One<T>()',
                 'nt2::Zero<T>()' : 'nt2::Zero<T>()',
                 'nt2::Zero<T>(),nt2::One<T>()' : 'nt2::Half<T>()',   
                },
             'signed_int_' : {
                 'nt2::Mone<T>()' : 'nt2::Mone<T>()',
                 'nt2::One<T>()' : 'nt2::One<T>()',
                 'nt2::Zero<T>()' : 'nt2::Zero<T>()',
                 'nt2::Zero<T>(),nt2::One<T>()' : 'nt2::Zero<T>()',   
                },
             'unsigned_int_' : {
                 'nt2::One<T>()' : 'nt2::One<T>()',
                 'nt2::Zero<T>()' : 'nt2::Zero<T>()',
                 'nt2::Zero<T>(),nt2::One<T>()' : 'nt2::Zero<T>()',   
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::average(a0,a1)'],
                },
             'property_value' : {
                 'default' : ['nt2::iround((a0+a1)/2)'],
                 'real_'   : ['(a0+a1)/2'],   
                },
             'ulp_thresh' : {
                 'default' : ['1'],
                 'real_' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
