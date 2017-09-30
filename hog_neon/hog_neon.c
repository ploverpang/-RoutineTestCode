#include "hog_neon.h"

#include <stdio.h>
#include <stdlib.h>
#include <arm_neon.h>
#include <memory.h>
#include <stdbool.h>

#define PHASE_TYPE_SIGN     (0)

KCFHogFilter* tkHogCreateKCF(int width, int height, int cellSize, int nBinO, int useTrueOrientation)
{
    KCFHogFilter *hf = NULL;

    if(cellSize <= 0 || width < 3 || height < 3)
    {
        return NULL;
    }

    hf = (KCFHogFilter*)malloc(sizeof(KCFHogFilter));
    hf->imHeight = height;
    hf->imWidth = width;
    hf->cellSize = cellSize;
    hf->useTrueOrientation = useTrueOrientation;

    hf->nCellX = (width + cellSize/2) / cellSize;
    hf->nCellY = (height + cellSize/2) / cellSize;
    hf->nBinO = nBinO;

    /*
     The length of the cell descriptor is 3*nBinO + 4:
        2*nBinO directed orientations,
        1*nBinO undirected orientation,
        4 texture items.
     The above layout also shows how we store them in the 3rd dimesion of the feature.
   */
    hf->cellDim = hf->nBinO;
    hf->feature = (float*)calloc(hf->nCellX * hf->nCellY * hf->cellDim, sizeof(float));
    hf->cell = (float*)calloc(hf->nCellX * hf->nCellY * nBinO, sizeof(float));

    return hf;
}

void tkHogReleaseKCF(KCFHogFilter* hf)
{
	if(hf)
	{
		if(hf->cell)
			free(hf->cell);
		if(hf->feature)
			free(hf->feature);

		free(hf);
		hf = NULL;
	}
}

void tkNeHogProcessKCF(KCFHogFilter* hf, const unsigned char *im)
{
    short *dx, *dy;
    short *mag;
    unsigned char *phase;

	memset(hf->cell, 0, hf->nCellX * hf->nCellY * hf->nBinO * sizeof(float));
	memset(hf->feature, 0, hf->nCellX * hf->nCellY * hf->cellDim * sizeof(float));

    dx = (short*)calloc(hf->imHeight * hf->imWidth * sizeof(short));
    dy = (short*)calloc(hf->imHeight * hf->imWidth * sizeof(short));
    mag = (short*)calloc(hf->imHeight * hf->imWidth * sizeof(short));
    phase = (unsigned char*) calloc(hf->imHeight * hf->imWidth * sizeof(unsigned char));





    free(dx);
    free(dy);
    free(mag);
    free(phase);

}

void ne_derivative_xy(unsigned char* img, short *dx, short *dy, const int width, const int height)
{
    int y,x;
    unsigned char *p;
    short *pdx, *pdy;
    const int y_step = width;

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

inline int16x8_t magnitude_l2(int16x8_t input1, int16x8_t input2)
{
    const int32x4x2_t square_x =
    {
        {
            vmull_s16(vget_low_s16(input1), vget_low_s16(input1)),
            vmull_s16(vget_high_s16(input1), vget_high_s16(input1))
        }
    };

    const int32x4x2_t square_y =
    {
        {
            vmull_s16(vget_low_s16(input2), vget_low_s16(input2)),
            vmull_s16(vget_high_s16(input2), vget_high_s16(input2))
        }
    };

    const uint32x4x2_t sum =
    {
        {
            vaddq_u32(vreinterpretq_u32_s32(square_x.val[0]), vreinterpretq_u32_s32(square_y.val[0])),
            vaddq_u32(vreinterpretq_u32_s32(square_x.val[1]), vreinterpretq_u32_s32(square_y.val[1]))
        }
    };

    const float32x4x2_t res =
    {
        {
            sqrtv(vcvtq_f32_u32(sum.val[0])),
            sqrtv(vcvtq_f32_u32(sum.val[1]))
        }
    };

    return vcombine_s16(vqmovn_s32(vcvtq_s32_f32(res.val[0])),
                        vqmovn_s32(vcvtq_s32_f32(res.val[1])));
}

inline float32x4_t inv(float32x4_t x)
{
    float32x4_t result = vrecpeq_f32(x);
    result             = vmulq_f32(vrecpsq_f32(x, result), result);
    return result;
}

inline float32x4_t atan2_0_360(float32x4_t gx, float32x4_t gy)
{
    const float32x4_t zero       = vdupq_n_f32(0.0f);
    const float32x4_t epsilon    = vdupq_n_f32(1e-9f);
    const float32x4_t piover4    = vdupq_n_f32(PI_4);
    const float32x4_t coeff1     = vdupq_n_f32(COEFF1);
    const float32x4_t coeff2     = vdupq_n_f32(COEFF2);
    const float32x4_t ninety     = vdupq_n_f32(90.0f * SCALE_FACTOR);
    const float32x4_t oneeighty  = vdupq_n_f32(180.0f * SCALE_FACTOR);
    const float32x4_t threesixty = vdupq_n_f32(360.0f * SCALE_FACTOR);
    const float32x4_t scale      = vdupq_n_f32(SCALE_360);

    float32x4_t abs_gx = vabsq_f32(gx);
    float32x4_t abs_gy = vabsq_f32(gy);
    float32x4_t tmin   = vminq_f32(abs_gx, abs_gy);
    float32x4_t tmax   = vmaxq_f32(abs_gx, abs_gy);
    float32x4_t z      = vmulq_f32(tmin, inv(vaddq_f32(tmax, epsilon)));
    float32x4_t absz   = vabsq_f32(z);
    float32x4_t term   = vmulq_f32(z, vsubq_f32(vdupq_n_f32(1.0f), absz));

    /* Compute y = pi/4 * x - x*(abs(x)-1)*(0.2447+0.0663 * abs(x) */
    float32x4_t result = vaddq_f32(coeff2, vmulq_f32(absz, coeff1));
    result             = vmulq_f32(result, term);
    result             = vmlaq_f32(result, piover4, z);

    /* Radians to degrees conversion with applied a scale factor in order to have the result [0, 255]  */
    result = vmulq_f32(result, scale);

    /* If z > 1, result = 90 - result */
    result = vbslq_f32(vcgeq_f32(abs_gx, abs_gy), result, vsubq_f32(ninety, result));

    /* Choose correct quadrant */
    result = vbslq_f32(vcltq_f32(gx, zero), vsubq_f32(oneeighty, result), result);
    result = vbslq_f32(vcltq_f32(gy, zero), vsubq_f32(threesixty, result), result);

    return result;
}

inline float32x4_t atan2_0_180(float32x4_t gx, float32x4_t gy)
{
    const float32x4_t zero       = vdupq_n_f32(0.0f);
    const float32x4_t epsilon    = vdupq_n_f32(1e-9f); // epsilon used to avoiding division by 0
    const float32x4_t piover4    = vdupq_n_f32(PI_4);
    const float32x4_t coeff1     = vdupq_n_f32(COEFF1);
    const float32x4_t coeff2     = vdupq_n_f32(COEFF2);
    const float32x4_t ninety     = vdupq_n_f32(90.0f);
    const float32x4_t oneeighty  = vdupq_n_f32(180.0f);
    const float32x4_t threesixty = vdupq_n_f32(360.0f);
    const float32x4_t scale      = vdupq_n_f32(SCALE_180);

    float32x4_t abs_gx = vabsq_f32(gx);
    float32x4_t abs_gy = vabsq_f32(gy);
    float32x4_t tmin   = vminq_f32(abs_gx, abs_gy);
    float32x4_t tmax   = vmaxq_f32(abs_gx, abs_gy);
    float32x4_t z      = vmulq_f32(tmin, inv(vaddq_f32(tmax, epsilon)));
    float32x4_t absz   = vabsq_f32(z);

    /* Compute y = pi/4 * z - z*(abs(z)-1)*(0.2447+0.0663 * abs(z) */
    float32x4_t term   = vmulq_f32(z, vsubq_f32(vdupq_n_f32(1.0f), absz));
    float32x4_t result = vaddq_f32(coeff2, vmulq_f32(absz, coeff1));
    result             = vmulq_f32(result, term);
    result             = vmlaq_f32(result, piover4, z);

    /* Radians to degrees conversion */
    result = vmulq_f32(result, scale);

    /* If z > 1, result = 90 - result */
    result = vbslq_f32(vcgeq_f32(abs_gx, abs_gy), result, vsubq_f32(ninety, result));

    /* Choose correct quadrant */
    result = vbslq_f32(vcltq_f32(gx, zero), vsubq_f32(oneeighty, result), result);
    result = vbslq_f32(vcltq_f32(gy, zero), vsubq_f32(threesixty, result), result);
    result = vbslq_f32(vcgtq_f32(result, oneeighty), vsubq_f32(result, oneeighty), result);

    return result;
}

inline float32x4_t invsqrtv(float32x4_t x)
{
    float32x4_t sqrt_reciprocal = vrsqrteq_f32(x);

    sqrt_reciprocal = vmulq_f32(vrsqrtsq_f32(vmulq_f32(x, sqrt_reciprocal), sqrt_reciprocal),
                                sqrt_reciprocal);
    sqrt_reciprocal = vmulq_f32(vrsqrtsq_f32(vmulq_f32(x, sqrt_reciprocal), sqrt_reciprocal),
                                sqrt_reciprocal);

    return sqrt_reciprocal;
}

inline float32x4_t sqrtv(float32x4_t x)
{
    float32x4_t res = vdupq_n_f32(0.5f);
    return vmlaq_f32(res, x, invsqrtv(x));
}

inline uint8x8_t phase_signed(int16x8_t input1, int16x8_t input2)
{
    const float32x4_t zeropointfive = vdupq_n_f32(0.5f);

    float32x4_t inputx_f32_high = vcvtq_f32_s32(vmovl_s16(vget_high_s16(input1)));
    float32x4_t inputx_f32_low  = vcvtq_f32_s32(vmovl_s16(vget_low_s16(input1)));
    float32x4_t inputy_f32_high = vcvtq_f32_s32(vmovl_s16(vget_high_s16(input2)));
    float32x4_t inputy_f32_low  = vcvtq_f32_s32(vmovl_s16(vget_low_s16(input2)));

    /* Compute fast atan2 */
    float32x4_t angle_high = atan2_0_360(inputx_f32_high, inputy_f32_high);
    float32x4_t angle_low  = atan2_0_360(inputx_f32_low, inputy_f32_low);

    angle_high = vaddq_f32(angle_high, zeropointfive);
    angle_low  = vaddq_f32(angle_low, zeropointfive);

    return vmovn_u16(vcombine_u16(vqmovun_s32(vcvtq_s32_f32(angle_low)),
                                  vqmovun_s32(vcvtq_s32_f32(angle_high))));
}

inline uint8x8_t phase_unsigned(int16x8_t input1, int16x8_t input2)
{
    const float32x4_t zeropointfive = vdupq_n_f32(0.5f);

    float32x4_t inputx_f32_high = vcvtq_f32_s32(vmovl_s16(vget_high_s16(input1)));
    float32x4_t inputx_f32_low  = vcvtq_f32_s32(vmovl_s16(vget_low_s16(input1)));
    float32x4_t inputy_f32_high = vcvtq_f32_s32(vmovl_s16(vget_high_s16(input2)));
    float32x4_t inputy_f32_low  = vcvtq_f32_s32(vmovl_s16(vget_low_s16(input2)));

    /* Compute fast atan2 */
    float32x4_t angle_high = atan2_0_180(inputx_f32_high, inputy_f32_high);
    float32x4_t angle_low  = atan2_0_180(inputx_f32_low, inputy_f32_low);

    angle_high = vaddq_f32(angle_high, zeropointfive);
    angle_low  = vaddq_f32(angle_low, zeropointfive);

    return vmovn_u16(vcombine_u16(vqmovun_s32(vcvtq_s32_f32(angle_low)),
                                  vqmovun_s32(vcvtq_s32_f32(angle_high))));
}

void ne_magnitude_phase(const short *dx, const short *dy, short *mag, unsigned char *phase, const width, const height)
{
    int y,x;
    unsigned char *p;
    short *pmag;
    unsigned char *p_phase;

    short pdx, pdy;

    for(y=0; y< height; y++)
    {
        const int width_offset = width*y;
        pdx = dx + width_offset;
        pdy = dy + width_offset;
        pmag = mag + width_offset;
        p_phase = phase + width_offset;

        for(x=0; x<=width-16; x+=16, pdx+=16, pdy+=16, pmag+=16, p_phase+=16)
        {
            const int16x8x2_t input1 =
            {
                {
                    vld1q_s16((int16_t *)pdx),
                    vld1q_s16((int16_t *)(pdx+8))
                }
            };

            const int16x8x2_t input2 =
            {
                {
                    vld1q_s16((int16_t *)pdy),
                    vld1q_s16((int16_t *)(pdy+8))
                }
            };

            /* Compute magnitude */
            int16x8x2_t mag_result{ {} };

            mag_result.val[0] = magnitude_l2(input1.val[0], input2.val[0]);
            mag_result.val[1] = magnitude_l2(input1.val[1], input2.val[1]);

            /* Store magnitude */
            vst1q_s16((int16_t *)>pmag, mag_result.val[0]);
            vst1q_s16((int16_t *)>pmag+8, mag_result.val[1]);

            /* Compute phase*/
            uint8x8x2_t vphase{ {} };

            if(PHASE_TYPE_SIGN)
            {
                vphase.val[0] = phase_signed(input1.val[0], input2.val[0]);
                vphase.val[1] = phase_signed(input1.val[1], input2.val[1]);
            }
            else
            {
                vphase.val[0] = phase_unsigned(input1.val[0], input2.val[0]);
                vphase.val[1] = phase_unsigned(input1.val[1], input2.val[1]);
            }

            /* Store phase */
            vst1q_u8(p_phase, vcombine_u8(vphase.val[0], vphase.val[1]));
        }
    }
}

void cell_width_ge8(const int16_t *mag_row_ptr, const uint8_t *phase_row_ptr, float *output_ptr, size_t mag_stride, size_t phase_stride, size_t cell_width,
                    size_t cell_height, size_t num_bins, float phase_scale)
{
    const float32x4_t        scale_f32    = vdupq_n_f32(phase_scale);
    static const float32x4_t one_f32      = vdupq_n_f32(1.0f);
    static const float32x4_t zerofive_f32 = vdupq_n_f32(0.5f);
    static const int32x4_t   zero_s32     = vdupq_n_s32(0);
    static const int32x4_t   one_s32      = vdupq_n_s32(1);
    const int32x4_t          num_bins_s32 = vdupq_n_s32(num_bins);

    memset(output_ptr, 0, sizeof(float) * num_bins);

    for(size_t yc = 0; yc < cell_height; ++yc)
    {
        int32_t xc = 0;

        for(; xc <= static_cast<int32_t>(cell_width) - 8; xc += 8)
        {
            // Load magnitude and phase values
            const uint8x8_t phase_u8 = vld1_u8(phase_row_ptr + xc + yc * phase_stride);
            const int16x8_t mag_s16  = vld1q_s16(mag_row_ptr + xc + yc * mag_stride);

            // Convert phase to U16
            const uint16x8_t phase_u16 = vmovl_u8(phase_u8);

            // Convert magnitude to float32
            const float32x4x2_t mag_f32 =
            {
                {
                    vcvtq_f32_s32(vmovl_s16(vget_low_s16(mag_s16))),
                    vcvtq_f32_s32(vmovl_s16(vget_high_s16(mag_s16)))
                }
            };

            // Convert phase to float32
            float32x4x2_t phase_f32 =
            {
                {
                    vcvtq_f32_u32(vmovl_u16(vget_low_u16(phase_u16))),
                    vcvtq_f32_u32(vmovl_u16(vget_high_u16(phase_u16)))
                }
            };

            // Scale phase: phase * scale + 0.5f
            phase_f32.val[0] = vmlaq_f32(zerofive_f32, phase_f32.val[0], scale_f32);
            phase_f32.val[1] = vmlaq_f32(zerofive_f32, phase_f32.val[1], scale_f32);

            // Compute histogram index.
            int32x4x2_t hidx_s32 =
            {
                {
                    vcvtq_s32_f32(phase_f32.val[0]),
                    vcvtq_s32_f32(phase_f32.val[1])
                }
            };

            // Compute magnitude weights (w0 and w1)
            const float32x4x2_t hidx_f32 =
            {
                {
                    vcvtq_f32_s32(hidx_s32.val[0]),
                    vcvtq_f32_s32(hidx_s32.val[1])
                }
            };

            float32x4x2_t w1_f32 =
            {
                {
                    vsubq_f32(phase_f32.val[0], hidx_f32.val[0]),
                    vsubq_f32(phase_f32.val[1], hidx_f32.val[1])
                }
            };

            float32x4x2_t w0_f32 =
            {
                {
                    vsubq_f32(one_f32, w1_f32.val[0]),
                    vsubq_f32(one_f32, w1_f32.val[1])
                }
            };

            // Compute contribute for splitting vote
            const float32x4x2_t mag_w0_f32 =
            {
                {
                    vmulq_f32(mag_f32.val[0], w0_f32.val[0]),
                    vmulq_f32(mag_f32.val[1], w0_f32.val[1])
                }
            };

            const float32x4x2_t mag_w1_f32 =
            {
                {
                    vmulq_f32(mag_f32.val[0], w1_f32.val[0]),
                    vmulq_f32(mag_f32.val[1], w1_f32.val[1])
                }
            };

            // Weighted vote between 2 bins

            // Check if the histogram index is equal to num_bins
            uint32x4x2_t mask =
            {
                {
                    vceqq_s32(hidx_s32.val[0], num_bins_s32),
                    vceqq_s32(hidx_s32.val[1], num_bins_s32)
                }
            };

            hidx_s32.val[0] = vbslq_s32(mask.val[0], zero_s32, hidx_s32.val[0]);
            hidx_s32.val[1] = vbslq_s32(mask.val[1], zero_s32, hidx_s32.val[1]);

            // First bin - Low
            *(output_ptr + vgetq_lane_s32(hidx_s32.val[0], 0)) += vgetq_lane_f32(mag_w0_f32.val[0], 0);
            *(output_ptr + vgetq_lane_s32(hidx_s32.val[0], 1)) += vgetq_lane_f32(mag_w0_f32.val[0], 1);
            *(output_ptr + vgetq_lane_s32(hidx_s32.val[0], 2)) += vgetq_lane_f32(mag_w0_f32.val[0], 2);
            *(output_ptr + vgetq_lane_s32(hidx_s32.val[0], 3)) += vgetq_lane_f32(mag_w0_f32.val[0], 3);

            // First bin - high
            *(output_ptr + vgetq_lane_s32(hidx_s32.val[1], 0)) += vgetq_lane_f32(mag_w0_f32.val[1], 0);
            *(output_ptr + vgetq_lane_s32(hidx_s32.val[1], 1)) += vgetq_lane_f32(mag_w0_f32.val[1], 1);
            *(output_ptr + vgetq_lane_s32(hidx_s32.val[1], 2)) += vgetq_lane_f32(mag_w0_f32.val[1], 2);
            *(output_ptr + vgetq_lane_s32(hidx_s32.val[1], 3)) += vgetq_lane_f32(mag_w0_f32.val[1], 3);

            hidx_s32.val[0] = vaddq_s32(hidx_s32.val[0], one_s32);
            hidx_s32.val[1] = vaddq_s32(hidx_s32.val[1], one_s32);

            // Check if the histogram index is equal to num_bins
            mask.val[0] = vceqq_s32(hidx_s32.val[0], num_bins_s32);
            mask.val[1] = vceqq_s32(hidx_s32.val[1], num_bins_s32);

            hidx_s32.val[0] = vbslq_s32(mask.val[0], zero_s32, hidx_s32.val[0]);
            hidx_s32.val[1] = vbslq_s32(mask.val[1], zero_s32, hidx_s32.val[1]);

            // Second bin - Low
            *(output_ptr + vgetq_lane_s32(hidx_s32.val[0], 0)) += vgetq_lane_f32(mag_w1_f32.val[0], 0);
            *(output_ptr + vgetq_lane_s32(hidx_s32.val[0], 1)) += vgetq_lane_f32(mag_w1_f32.val[0], 1);
            *(output_ptr + vgetq_lane_s32(hidx_s32.val[0], 2)) += vgetq_lane_f32(mag_w1_f32.val[0], 2);
            *(output_ptr + vgetq_lane_s32(hidx_s32.val[0], 3)) += vgetq_lane_f32(mag_w1_f32.val[0], 3);

            // Second bin - high
            *(output_ptr + vgetq_lane_s32(hidx_s32.val[1], 0)) += vgetq_lane_f32(mag_w1_f32.val[1], 0);
            *(output_ptr + vgetq_lane_s32(hidx_s32.val[1], 1)) += vgetq_lane_f32(mag_w1_f32.val[1], 1);
            *(output_ptr + vgetq_lane_s32(hidx_s32.val[1], 2)) += vgetq_lane_f32(mag_w1_f32.val[1], 2);
            *(output_ptr + vgetq_lane_s32(hidx_s32.val[1], 3)) += vgetq_lane_f32(mag_w1_f32.val[1], 3);
        }

        for(; xc < static_cast<int32_t>(cell_width); xc++)
        {
            const float phase_value = *(phase_row_ptr + xc + yc * phase_stride) * phase_scale + 0.5f;
            const float mag_value   = *(mag_row_ptr + xc + yc * mag_stride);

            const float w1 = phase_value - std::floor(phase_value);

            // The quantised phase is the histogram index [0, num_bins - 1] - Round
            // Check limit of histogram index. If hidx == num_bins, hidx = 0
            const size_t hidx = static_cast<size_t>(phase_value) % num_bins;

            // Weighted vote between 2 bins
            *(output_ptr + hidx) += mag_value * (1.0f - w1);
            *(output_ptr + ((hidx + 1) % (num_bins))) += mag_value * w1;
        }
    }
}

void cell_width_lt8(const int16_t *mag_row_ptr, const uint8_t *phase_row_ptr, float *output_ptr,
                    size_t mag_stride, size_t phase_stride, size_t cell_width, size_t cell_height, size_t num_bins, float phase_scale)
{
    const float32x4_t        scale_f32    = vdupq_n_f32(phase_scale);
    static const float32x4_t one_f32      = vdupq_n_f32(1.0f);
    static const float32x4_t zerofive_f32 = vdupq_n_f32(0.5f);
    static const int32x4_t   zero_s32     = vdupq_n_s32(0);
    static const int32x4_t   one_s32      = vdupq_n_s32(1);
    const int32x4_t          num_bins_s32 = vdupq_n_s32(num_bins);

    memset(output_ptr, 0, sizeof(float) * num_bins);

    for(size_t yc = 0; yc < cell_height; ++yc)
    {
        int32_t xc = 0;

        for(; xc <= static_cast<int32_t>(cell_width) - 4; xc += 4)
        {
            // Load magnitude and phase values
            const uint8x8_t phase_u8 = vld1_u8(phase_row_ptr + xc + yc * phase_stride);
            const int16x4_t mag_s16  = vld1_s16(mag_row_ptr + xc + yc * mag_stride);

            // Convert magnitude and phase to float
            const float32x4_t mag_f32   = vcvtq_f32_s32(vmovl_s16(mag_s16));
            float32x4_t       phase_f32 = vcvtq_f32_u32(vmovl_u16(vget_low_u16(vmovl_u8(phase_u8))));

            // Scale phase: phase * scale + 0.5f
            phase_f32 = vmlaq_f32(zerofive_f32, phase_f32, scale_f32);

            // Compute histogram index.
            int32x4_t hidx_s32 = vcvtq_s32_f32(phase_f32);

            // Compute magnitude weights (w0 and w1)
            const float32x4_t hidx_f32 = vcvtq_f32_s32(hidx_s32);

            // w1 = phase_f32 - hidx_f32
            const float32x4_t w1_f32 = vsubq_f32(phase_f32, hidx_f32);

            // w0 = 1.0 - w1
            const float32x4_t w0_f32 = vsubq_f32(one_f32, w1_f32);

            // Compute contribute for splitting vote
            const float32x4_t mag_w0_f32 = vmulq_f32(mag_f32, w0_f32);
            const float32x4_t mag_w1_f32 = vmulq_f32(mag_f32, w1_f32);

            // Weighted vote between 2 bins

            // Check if the histogram index is equal to num_bins. If so, replace the index with 0
            uint32x4_t mask = vceqq_s32(hidx_s32, num_bins_s32);
            hidx_s32        = vbslq_s32(mask, zero_s32, hidx_s32);

            // Bin 0
            *(output_ptr + vgetq_lane_s32(hidx_s32, 0)) += vgetq_lane_f32(mag_w0_f32, 0);
            *(output_ptr + vgetq_lane_s32(hidx_s32, 1)) += vgetq_lane_f32(mag_w0_f32, 1);
            *(output_ptr + vgetq_lane_s32(hidx_s32, 2)) += vgetq_lane_f32(mag_w0_f32, 2);
            *(output_ptr + vgetq_lane_s32(hidx_s32, 3)) += vgetq_lane_f32(mag_w0_f32, 3);

            hidx_s32 = vaddq_s32(hidx_s32, one_s32);

            // Check if the histogram index is equal to num_bins
            mask     = vceqq_s32(hidx_s32, num_bins_s32);
            hidx_s32 = vbslq_s32(mask, zero_s32, hidx_s32);

            // Bin1
            *(output_ptr + vgetq_lane_s32(hidx_s32, 0)) += vgetq_lane_f32(mag_w1_f32, 0);
            *(output_ptr + vgetq_lane_s32(hidx_s32, 1)) += vgetq_lane_f32(mag_w1_f32, 1);
            *(output_ptr + vgetq_lane_s32(hidx_s32, 2)) += vgetq_lane_f32(mag_w1_f32, 2);
            *(output_ptr + vgetq_lane_s32(hidx_s32, 3)) += vgetq_lane_f32(mag_w1_f32, 3);
        }

        for(; xc < static_cast<int32_t>(cell_width); ++xc)
        {
            const float phase_value = *(phase_row_ptr + xc + yc * phase_stride) * phase_scale + 0.5f;
            const float mag_value   = *(mag_row_ptr + xc + yc * mag_stride);

            const float w1 = phase_value - std::floor(phase_value);

            // The quantised phase is the histogram index [0, num_bins - 1] - Round
            // Check limit of histogram index. If hidx == num_bins, hidx = 0
            const auto hidx = static_cast<size_t>(phase_value) % num_bins;

            // Weighted vote between 2 bins
            *(output_ptr + hidx) += mag_value * (1.0f - w1);
            *(output_ptr + ((hidx + 1) % (num_bins))) += mag_value * w1;
        }
    }
}

void ne_hog_orientation_binning(const short *mag, const unsigned char *phase, float *cells,
        const int width, const int height, const int cell_size, const int num_bins)
{
    float _phase_scale = (PHASE_TYPE_SIGN ? _num_bins / 360.0f : _num_bins / 180.0f);
    _phase_scale *= (PHASE_TYPE_SIGN ? 360.0f / 255.0f : 1.0f);

    int y,x;
    short *pmag;
    unsigned char *p_phase;
    float *p_cells = cells;
    for(y=0; y<= height-cell_size; y+=cell_size)
    {
        const int width_offset = width*y;
        pmag = mag + width_offset;
        p_phase = phase + width_offset;

        for(x=0; x<=width-cell_size; x+=cell_size, pmag+=cell_size, p_phase+=cell_size, p_cells += num_bins)
        {
            if(cell_size < 8)
            {
                cell_width_lt8(pmag, p_phase, p_cells, width, width, cell_size,
                    cell_size, num_bins, _phase_scale);
            }
            else
            {
                cell_width_ge8(pmag, p_phase, p_cells, width, width, cell_size,
                    cell_size, num_bins, _phase_scale);
            }
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

    unsigned char *img_data = (unsigned char*)malloc(width*height*sizeof(unsigned char));
    /*unsigned char *out_data = (unsigned char*)malloc(width*height);*/
    short *dx = (short*)malloc(width*height);
    short *dy = (short*)malloc(width*height);

    load_data(infile, img_data, width);
    ne_derivative_xy(img_data, dx, dy, width, height, width);


    return 0;
}
