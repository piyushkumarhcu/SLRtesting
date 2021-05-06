#ifndef _ALGO_TOP_H_
#define _ALGO_TOP_H_

#include <iostream>
#include <ap_axi_sdata.h>
#include <hls_stream.h>
#include "ap_int.h"
#include <algorithm>
#include <utility>
#include <stdint.h>

#define N_INPUT_LINKS 34
#define N_OUTPUT_LINKS 4

template<int D, int U>
struct ap_axiu <D, U, 0, 0>{
	ap_uint<D>       data;
	ap_uint<U>       user;
	ap_uint<1>       last;
};

namespace algo {
	typedef ap_axiu<384, 8, 0, 0> axiword384;
}

void algo_top(hls::stream<algo::axiword384> link_in[N_INPUT_LINKS], hls::stream<algo::axiword384> link_out[N_OUTPUT_LINKS]);

#endif
