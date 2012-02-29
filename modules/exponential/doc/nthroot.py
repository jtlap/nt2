[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' :['nth root function: \\\\f$\sqrt[a_1]{a_0}\\\\f$','\par',
                         '\\\\arg a1 must be of integer type',
                         '\\\\arg if a1 is even and a0 negative the result is nan'] ,
         'param_1' : ['must be of integer type'],   
         'arity' : '2',
         'call_types' : ['T', 'iT'],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_floating<T>::type',
            },
         'type_defs' : [],
         'types' : ['real_', 'signed_int_', 'unsigned_int_'],
         'simd_types' : ['real_', "sintgt_16_", "uintgt_16_"],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created by jt the 08/12/2010',
             'cover_included' : ['#include <nt2/include/functions/sqr.hpp>', '#include <nt2/include/functions/abs.hpp>'],
             'notes' : [],
             'stamp' : 'modified by jt the 15/12/2010',
            },
         'ranges' : {
             'real_' : [['T(0)', 'T(10)'], ['iT(-10)', 'iT(10)']],
             'signed_int_' : [['-100', '100'], ['-100', '100']],
             'unsigned_int_' : [['0', '100'], ['0', '100']],
             'sintgt_16_' : [['-100', '100'], ['-100', '100']],
             'uintgt_16_' : [['0', '100'], ['0', '100']],
            },
         'specific_values' : {
             'default' : {
                 'T(8),iT(3)' : {'result' :'r_t(2)', 'ulp_thresh' : '0.5',},
                 'T(81),iT(4)' :{'result' : 'r_t(3)',  'ulp_thresh' : '0.5',},                       
                },
             'signed_int_' : {
                 'T(8),iT(3)' : {'result' :'r_t(2)', 'ulp_thresh' : '0.5',},
                 'T(81),iT(4)' :{'result' : 'r_t(3)',    'ulp_thresh' : '0.5',},                     
                 'T(-8),iT(3)' :{'result' : 'r_t(-2)', 'ulp_thresh' : '0.5',},
                },
             'uintgt_16_' : {
                 'T(8),iT(3)' : {'result' :'r_t(2)', 'ulp_thresh' : '0.5',},
                 'T(256),iT(4)' :{'result' : 'r_t(4)',  'ulp_thresh' : '0.5',},                       
                },
             'sintgt_16_' : {
                 'T(8),iT(3)' : {'result' :'r_t(2)', 'ulp_thresh' : '0.5',},
                 'T(256),iT(4)' :{'result' : 'r_t(4)',  'ulp_thresh' : '0.5',},                       
                 'T(-8),iT(3)' : {'result' :'r_t(-2)', 'ulp_thresh' : '0.5',},
                },
              'real_' : {
                 'T(-8),iT(3)' :{'result' : 'r_t(-2)', 'ulp_thresh' : '0.5',},
                 'T(8),iT(3)' : {'result' :'r_t(2)', 'ulp_thresh' : '0.5',},
                 'T(256),iT(4)' :{'result' : 'r_t(4)',  'ulp_thresh' : '0.5',},   
                 'nt2::Inf<T>(),iT(3)' :{'result' : 'nt2::Inf<r_t>()', 'ulp_thresh' : '0.5',},
                 'nt2::Minf<T>(),iT(3)' :{'result' : 'nt2::Minf<r_t>()', 'ulp_thresh' : '0.5',},
                 'nt2::Mone<T>(),iT(3)' :{'result' : 'nt2::Mone<r_t>()', 'ulp_thresh' : '0.5',},
                 'nt2::Nan<T>(),iT(3)' : {'result' :'nt2::Nan<r_t>()', 'ulp_thresh' : '0.5',},
                 'nt2::One<T>(),iT(3)' : {'result' :'nt2::One<r_t>()', 'ulp_thresh' : '0.5',},
                 'nt2::Zero<T>(),iT(3)' :{'result' : 'nt2::Zero<r_t>()', 'ulp_thresh' : '0.5',},
                 'nt2::Inf<T>(),iT(4)' :{'result' : 'nt2::Inf<r_t>()', 'ulp_thresh' : '0.5',},
                 'nt2::Minf<T>(),iT(4)' :{'result' : 'nt2::Nan<r_t>()', 'ulp_thresh' : '0.5',},
                 'nt2::Mone<T>(),iT(4)' :{'result' : 'nt2::Nan<r_t>()', 'ulp_thresh' : '0.5',},
                 'nt2::Nan<T>(),iT(4)' : {'result' :'nt2::Nan<r_t>()', 'ulp_thresh' : '0.5',},
                 'nt2::One<T>(),iT(4)' :{'result' : 'nt2::One<r_t>()', 'ulp_thresh' : '0.5',},
                 'nt2::Zero<T>(),iT(4)' : {'result' :'nt2::Zero<r_t>()', 'ulp_thresh' : '0.5',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'real_' : ['nt2::nthroot(a0*nt2::sqr(a0),3)', 'nt2::nthroot(nt2::sqr(a0),2)'],
                },
             'property_value' : {
                 'real_' : ['T(a0)', 'nt2::abs(a0)'],
                },
             'ulp_thresh' : {
                 'real_' : ['1', '1'],
                },
            },
        },
     'version' : '0.1',
    },
]
