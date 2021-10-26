#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#include "heatshrink_encoder.h"
#include "heatshrink_decoder.h"
/************************************************************************/
/*                                                                      */
/************************************************************************/
//uint8_t input[] = "Allocate a new encoder struct and its buffers.Poll for output from the encoder, copying at most OUT_BUF_SIZE bytes into.";
uint8_t input[] = "foofoofoofoofoofoo";
uint8_t output[1024];
uint8_t deoutput[1024];
size_t copied = 0;
size_t count = 0, sum = 0;

void decoder(void)
{
    heatshrink_decoder *hsd = heatshrink_decoder_alloc(256, 8, 7);
    
    printf("decoder\n");
    
    for (uint32_t i = 0; i < copied; i++) {
        HSD_sink_res sres = heatshrink_decoder_sink(hsd, &output[i], 1, &count);
        //printf("sres is %d\n", sres);
        if(sres < 0)
            printf("error %d\n", __LINE__);
    }
    
    for (uint32_t i = 0; i < sizeof(input); i++) {
        if(heatshrink_decoder_poll(hsd, &deoutput[i], 1, &count) < 0)
            printf("error %d\n", __LINE__);
        
        sum += count;
    }
    printf("sum len %ld\n", sum);
    
    for (size_t i = 0; i < sum; i++)
        printf("0x%02x, ", deoutput[i]);
    printf("\n");
    
    heatshrink_decoder_free(hsd);
}

void encoder(void)
{
    heatshrink_encoder *hse = heatshrink_encoder_alloc(8, 7);
    
    printf("encoder\n");
    
    HSE_sink_res sres = heatshrink_encoder_sink(hse, input, sizeof(input), &copied);
    if((sres != HSER_SINK_OK) || (copied != sizeof(input)))
        printf("error %d\n", __LINE__);
    printf("sink len %ld\n", sizeof(input));
    for (size_t i = 0; i < sizeof(input); i++)
        printf("0x%02x, ", input[i]);
    printf("\n");
    
    HSE_finish_res fres = heatshrink_encoder_finish(hse);
    if(fres != HSER_FINISH_MORE)
        printf("error %d\n", __LINE__);
    
    HSE_poll_res pres = heatshrink_encoder_poll(hse, output, 1024, &copied);
    if(pres != HSER_POLL_EMPTY)
        printf("error %d\n", __LINE__);
    printf("poll len %ld\n", copied);
    
    fres = heatshrink_encoder_finish(hse);
    if(fres != HSER_FINISH_DONE)
        printf("error %d\n", __LINE__);
    
    for (size_t i = 0; i < copied; i++)
        printf("0x%02x, ", output[i]);
    printf("\n");
    
    heatshrink_encoder_free(hse);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

int main(int argc, char* argv[])
{
    encoder();
    decoder();
    
    return 0;
}