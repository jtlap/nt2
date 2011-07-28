[ ## this file was manually modified by jt
    {
     'functor' : {
         'arity' : '2',
         'call_types' : ['T','iT'],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'r_t',
            },
         'type_defs' : ['typedef typename nt2::meta::scalar_of<T>::type sT;'],
         'types' : ['integer_','real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 18/02/2011',
             'included' : [],
             'no_ulp' : 'True',
             'notes' : [],
             'stamp' : 'modified by jt the 18/02/2011',
            },
         'ranges' : {
             'default' : [
                [['nt2::Valmin<T>()/2', 'nt2::Valmax<T>()/2'], ['0','sizeof(sT)*8-1']],
                ],
            },
         'specific_values' : {
             'default' : {
                 'nt2::One<T>(),nt2::One<iT>()' : {'result' : 'nt2::Two<r_t>()','ulp_thresh' : '0',},
                 'nt2::One<T>(),nt2::Zero<iT>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>(),nt2::One<iT>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'integer_' : {
                 'nt2::Mone<T>(),nt2::One<iT>()' : {'result' : 'r_t(-nt2::Two<r_t>())','ulp_thresh' : '0',},
                 'nt2::One<T>(),nt2::One<iT>()' : {'result' : 'nt2::Two<r_t>()','ulp_thresh' : '0',},
                 'nt2::One<T>(),nt2::Zero<iT>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>(),nt2::One<iT>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                },
             'real_' : {
                 'nt2::One<T>(),nt2::Zero<iT>()' : {'result' : 'nt2::One<r_t>()','ulp_thresh' : '0',},
                 'nt2::Zero<T>(),nt2::One<iT>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'property_call' : {
                 'integer_' : ['nt2::shift_left(a0,a1)'],
                },
             'property_value' : {
                 'integer_' : ['r_t(a0<<a1)'],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'integer_' : ['0'],
                },
            },
        },
    },
]
