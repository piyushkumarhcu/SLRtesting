#include "algo_top.h"

void processOutputLinks(hls::stream<algo::axiword384> &link, algo::axiword384 &bigdataword){
        #pragma HLS INTERFACE axis port=link
        #pragma HLS INLINE

        algo::axiword384 rOut;
        rOut.user = 0;
        rOut.last = 1;
        rOut.data = bigdataword.data;
        link.write(rOut);
}

void processInputLinks(hls::stream<algo::axiword384> &link, algo::axiword384 &valOut){
    #pragma HLS INTERFACE axis port=link
    #pragma HLS PIPELINE II=6
    #pragma HLS INLINE
    valOut = link.read();
}

void algo_top(hls::stream<algo::axiword384> link_in[N_INPUT_LINKS], hls::stream<algo::axiword384> link_out[N_OUTPUT_LINKS]){
    #pragma HLS INTERFACE axis port=link_in
    #pragma HLS INTERFACE axis port=link_out
    #pragma HLS PIPELINE II=6

    algo::axiword384 valOutMain[N_INPUT_LINKS];
    #pragma HLS ARRAY_PARTITION variable=valOutMain
    valOutLoop: for (size_t jLink = 0; jLink < N_INPUT_LINKS; jLink++) {
        #pragma HLS UNROLL
    processInputLinks(link_in[jLink], valOutMain[jLink]);
  }

  ap_uint<5> gain = 2;

    algo::axiword384 valOutLink[N_INPUT_LINKS];
    #pragma HLS ARRAY_PARTITION variable=valOutMain
  GainLoop: for (size_t jLink = 0; jLink < N_INPUT_LINKS; jLink++) {
        #pragma HLS UNROLL
    valOutLink[jLink].data = (valOutMain[jLink].data)*gain;
  }

  processOutputLinks(link_out[0], valOutLink[0]);
  processOutputLinks(link_out[1], valOutLink[1]);
  processOutputLinks(link_out[2], valOutLink[2]);
  processOutputLinks(link_out[3], valOutLink[3]);

}
