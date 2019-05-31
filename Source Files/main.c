#include "grayscale.h"
#include "color_reduction.h"
//#include "error_diffusion.h"
#include "inversion.h"
#include "solarisation.h"
#include "brightness.h"
#include "contrast.h"
#include "gamma_correction.h"

int main(int argc, char** argv)
{
	//grayscale_test("grass.png");
	//color_reduction_test("parrot.png");
	//inversion_test("ball.png");
	//solarisation_test("sunflower.png");
	//contrast_test("zebra.png");
	//brightness_test("pansy.png");
	gamma_correction_test("tree.png");
	return 0;
}