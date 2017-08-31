#include <stdio.h>
#include <stdlib.h>
#include <arm_neon.h>

void derivative_xy(unsigned char* img, short *dx, short *dy, const int width, const int height, const int y_step)
{
    int y,x;
    unsigned char *p;
    short *pdx, *pdy;

    for(y=1; y< height-1; y++)
    {
        const int width_offset = width*y + 1;
        p = img + width_offset;
        pdx = dx + width_offset;
        pdy = dy + width_offset;

        for(x=1; x<width-16; x+=16, p+=16, pdx+=16, pdy+=16)
        {
            const uint8x16_t t_data = vld1q_u8(p - y_step);
            const uint8x16_t b_data = vld1q_u8(p + y_step);
            const uint8x16_t l_data = vld1q_u8(p - 1);
            const uint8x16_t r_data = vld1q_u8(p + 1);

            /* Cast to int16 and perform the subtraction between the bottom and top data */
            const int16x8_t out0 = vsubq_s16(vreinterpretq_s16_u16(vmovl_u8(vget_low_u8(b_data))),
                    vreinterpretq_s16_u16(vmovl_u8(vget_low_u8(t_data))));

            /* Cast to int16 and perform the subtraction between the bottom and top data */
            const int16x8_t out1 = vsubq_s16(vreinterpretq_s16_u16(vmovl_u8(vget_high_u8(b_data))),
                    vreinterpretq_s16_u16(vmovl_u8(vget_high_u8(t_data))));

            /* Cast to int16 and perform the subtraction between the right and left data */
            const int16x8_t out2 = vsubq_s16(vreinterpretq_s16_u16(vmovl_u8(vget_low_u8(r_data))),
                    vreinterpretq_s16_u16(vmovl_u8(vget_low_u8(l_data))));

            /* Cast to int16 and perform the subtraction between the right and left data */
            const int16x8_t out3 = vsubq_s16(vreinterpretq_s16_u16(vmovl_u8(vget_high_u8(r_data))),
                    vreinterpretq_s16_u16(vmovl_u8(vget_high_u8(l_data))));

            /* Store result of derivative along the Y direction */
            vst1q_s16((int16_t *)pdy, out0);
            vst1q_s16((int16_t *)(pdy + 8), out1);

            /* Store result of derivative along the X direction */
            vst1q_s16((int16_t *)pdx, out2);
            vst1q_s16((int16_t *)(pdx + 8), out3);
        }
        for(; x<width-1; x++, p++, pdx++, pdy++)
        {
            const unsigned char t_data = *(p - y_step);
            const unsigned char b_data = *(p + y_step);
            const unsigned char l_data = *(p - 1);
            const unsigned char r_data = *(p + 1);

            *pdy = (short)b_data - (short)t_data;
            *pdy = (short)r_data - (short)l_data;
        }
    }
}


int load_data(FILE *infile, unsigned char *img_data, const int width)
{
    int rc;
    unsigned char *p_data = img_data;
    while((rc = fread(p_data, sizeof(unsigned char), width, infile)) != 0)
    {
        p_data += width;
    }
}

int main(int argc, char *argv[])
{
    FILE *infile, *outfile;

    const int width = 300;
    const int height = 128;

    if(argc < 3)
        return 0;

    infile = fopen(argv[1], "wb");
    if(infile == NULL)
    {
        printf("input image data load fails\n");
        exit(1);
    }

    unsigned char *img_data = (unsigned char*)malloc(width*height);
    /*unsigned char *out_data = (unsigned char*)malloc(width*height);*/
    short *dx = (short*)malloc(width*height);
    short *dy = (short*)malloc(width*height);

    load_data(infile, img_data, width);
    derivative_xy(img_data, dx, dy, width, height, width);


    return 0;
}
