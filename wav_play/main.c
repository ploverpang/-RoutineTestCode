#include <stdio.h>

#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"

int main(int argc, char *argv[])
{
     drwav wav;
     if (!drwav_init_file(&wav, "ldw.wav")) {
        printf("load wav fails\n");
        return -1;
         // Error opening WAV file.
     }

     drwav_int32* pDecodedInterleavedSamples = malloc(wav.totalSampleCount * sizeof(drwav_int32));
     size_t numberOfSamplesActuallyDecoded = drwav_read_s32(&wav, wav.totalSampleCount, pDecodedInterleavedSamples);

     drwav_uninit(&wav);

    return 0;
}

