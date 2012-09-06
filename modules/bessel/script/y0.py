[ ## this file was manually modified by jt
    {
     'functor' : {
         'description' : ['Bessel function of the second kind of order 0.'],
         'arity' : '1',
         'call_types' : [],
         'ret_arity' : '0',
         'rturn' : {
             'default' : 'typename boost::dispatch::meta::as_floating<T>::type',
            },
         'type_defs' : [],
         'types' : ['real_'],
         'simd_types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 16/02/2011',
             'included' : ['extern "C" {long double cephes_y0l(long double);}'],
             'notes' : [],
             'stamp' : 'modified by jt the 16/02/2011',
            },
         'ranges' : {
             'real_' : [['T(0)', 'T(10)']],
            },
         'specific_values' : {
             'real_' : {
                 'nt2::One<T>()' : {'result' : 'r_t( 8.825696421567700e-02)','ulp_thresh' : '2',},
                 'nt2::Zero<T>()' : {'result' : 'nt2::Minf<r_t>()','ulp_thresh' : '0',},
                },
            },
         'verif_test' : {
             'nb_rand' : {
                 'real_' : 'NT2_NB_RANDOM_TEST',
                },
             'property_call' : {
                 'real_' : ['nt2::y0(a0)'],
                },
             'property_value' : {
                 'real_' : ['cephes_y0l(a0)'],
                },
             'ulp_thresh' : {
                 'real_' : ['30'],
                },
            },
        },
    },
]
