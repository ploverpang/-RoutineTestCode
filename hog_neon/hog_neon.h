#ifndef HOG_NEON_H_9AROVU07
#define HOG_NEON_H_9AROVU07

typedef struct _kcf_hog_filter {
	int imWidth;
	int imHeight;

	int cellSize;
	int nBinO;

	int useTrueOrientation;

	int nCellX;
	int nCellY;

	int   cellDim;
	float *feature;

	float *cell;
} KCFHogFilter;

KCFHogFilter* tkHogCreateKCF(int width, int height, int cellSize, int nBinO, int useTrueOrientation);

void tkHogReleaseKCF(KCFHogFilter* hf);

void ne_derivative_xy(unsigned char* img, short *dx, short *dy, const int width, const int height);

void ne_magnitude_phase(const short *dx, const short *dy, short *mag, unsigned char *phase, const width, const height);

#endif /* end of include guard: HOG_NEON_H_9AROVU07 */
