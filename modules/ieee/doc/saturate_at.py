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
         'special' : ['ieee'],
         'tpl'   : '<nt2::tag::Pi>',   
         'type_defs' : [],
         'types' : ['real_'],
        },
     'info' : 'manually modified',
     'unit' : {
         'global_header' : {
             'first_stamp' : 'created  by jt the 20/03/2011',
             'included' : [],
             'notes' : [],
             'stamp' : 'modified by jt the 20/03/2011',
            },
         'ranges' : {
             'default' : [['-nt2::Ten<T>()', 'nt2::Ten<T>()']],
            },
         'specific_values' : {
            },
         'verif_test' : {
             'property_call' : {
                 'default' : ['saturate_at<nt2::tag::Pi>(a0)'],
                },
             'property_value' : {
                 'default' : ['a0>nt2::Pi<T>() ? nt2::Pi<T>() : (a0<-nt2::Pi<T>() ? -nt2::Pi<T>() :a0)'],
                },
             'simd' : {
                },
             'ulp_thresh' : {
                 'default' : ['1'],
                },
            },
        },
    },
]
