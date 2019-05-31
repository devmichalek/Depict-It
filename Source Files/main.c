#include "grayscale.h"
#include "reduce.h"
//#include "error_diffusion.h"
#include "inversion.h"
#include "solarisation.h"
#include "brightness.h"
#include "contrast.h"

int main(int argc, char** argv)
{
	//grayscale_test("grass.png");
	//reduce_test("parrot.png");
	//inversion_test("ball.png");
	//solarisation_test("sunflower.png");
	//contrast_test("zebra.png");
	brightness_test("pansy.png");
	return 0;
}