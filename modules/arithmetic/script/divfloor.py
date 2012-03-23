[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::common_type<T,T>::type',
            },
         'simd_types' : ['real_'],
         'type_defs' : [],
         'types' : ['real_', 'unsigned_int_', 'signed_int_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'modified by jt the 01/12/2010',
             'included' : ['#include<nt2/include/functions/floor.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 13/12/2010',
            },
         'ranges' : {
             'default' : [['T(-10)', 'T(10)'], ['T(-10)', 'T(10)']],
             'real_' : [['T(-10)', 'T(10)'], ['T(-10)', 'T(10)']],
             'signed_int_' : [['-100', '100'], ['-100', '100']],
             'unsigned_int_' : [['0', '100'], ['0', '100']],
            },
         'specific_values' : {
             'default' : {
                },
             'real_' : {
                 'nt2::Four<T>(),nt2::Three<T>()' : 'nt2::One<r_t>()',
                 'nt2::Four<T>(),nt2::Zero<T>()' : 'nt2::Inf<r_t>()',   
                 'nt2::Inf<T>()' : 'nt2::Nan<r_t>()',
                 'nt2::Minf<T>()' : 'nt2::Nan<r_t>()',
                 'nt2::Mone<T>()' : 'nt2::One<r_t>()',
                 'nt2::Nan<T>()' : 'nt2::Nan<r_t>()',
                 'nt2::One<T>()' : 'nt2::One<r_t>()',
                },
             'signed_int_' : {
                 'nt2::Four<T>(),nt2::Three<T>()' : 'nt2::One<r_t>()',
                 'nt2::Mfour<T>(),nt2::Three<T>()' : 'nt2::Mtwo<r_t>()',
                 'nt2::Four<T>(),nt2::Zero<T>()' : 'nt2::Valmax<r_t>()',   
                 'nt2::Mfour<T>(),nt2::Zero<T>()' : 'nt2::Valmin<r_t>()',
                 'nt2::Mone<T>()' : 'nt2::One<r_t>()',
                 'nt2::One<T>()' : 'nt2::One<r_t>()',
                },
             'unsigned_int_' : {
                 'nt2::Four<T>(),nt2::Three<T>()' : 'nt2::One<r_t>()',
                 'nt2::Four<T>(),nt2::Zero<T>()' : 'nt2::Valmax<r_t>()',   
                 'nt2::One<T>()' : 'nt2::One<r_t>()',
                },
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['nt2::divfloor(a0,a1)'],
                },
             'property_value' : {
                 'unsigned_int_' : ['a1 ? r_t(nt2::floor(double(a0)/double(a1))) : (a0 ? nt2::Valmax<r_t>() : 0)'],
                 'signed_int_' : ['a1 ? r_t(nt2::floor(double(a0)/double(a1))) : (a0<0 ? nt2::Valmin<r_t>() : (a0 ? nt2::Valmax<r_t>() : 0))'],
                 'real_' : ['r_t(nt2::floor(a0/a1))'],
                 },
             'ulp_thresh' : {
                 'default' : ['0'],
                },
            },
        },
     'version' : '0.1',
    },
]
