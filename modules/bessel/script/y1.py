[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['Bessel function of the second kind of order 1.'],
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_floating<T>::type',
            },
         'type_defs' : [],
         'types' : ['real_'],
         'simd_types' : ['real_'],
         'simd_ulp_thresh'   : '500.0',
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 16/02/2011',
             'included' : ['extern "C" {long double cephes_y1l(long double);}'],
             'notes' : [],
             'stamp' : 'modified by jt the 16/02/2011',
            },
         'ranges' : {
             'real_' : [['T(0)', 'T(10)']],
            },
         'specific_values' : {
             'real_' : {
                 'nt2::One<T>()' : {'result' : 'r_t(-7.812128213002889e-01)','ulp_thresh' : '1.5',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Minf<r_t>()','ulp_thresh' : '0',},
                 'nt2::Inf<T>()' : {'result' : 'nt2::Zero<r_t>()','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'default' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'real_' : ['nt2::y1(a0)'],
                },
             'property_value' : {
                 'real_' : ['cephes_y1l(a0)'],
                },
             'ulp_thresh' : {
                 'real_' : ['500.0'],
                },
 
            },
        },
    },
]
