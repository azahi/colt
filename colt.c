#include <X11/extensions/Xrandr.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static const struct
{
	float r;
	float g;
	float b;
}
shift[] =
{
	{ 1.00000000, 0.18172716, 0.00000000, },
	{ 1.00000000, 0.42322816, 0.00000000, },
	{ 1.00000000, 0.54360078, 0.08679949, },
	{ 1.00000000, 0.64373109, 0.28819679, },
	{ 1.00000000, 0.71976951, 0.42860152, },
	{ 1.00000000, 0.77987699, 0.54642268, },
	{ 1.00000000, 0.82854786, 0.64816570, },
	{ 1.00000000, 0.86860704, 0.73688797, },
	{ 1.00000000, 0.90198230, 0.81465502, },
	{ 1.00000000, 0.93853986, 0.88130458, },
	{ 1.00000000, 0.97107439, 0.94305985, },
	{ 1.00000000, 1.00000000, 1.00000000, },
	{ 0.95160805, 0.96983355, 1.00000000, },
	{ 0.91194747, 0.94470005, 1.00000000, },
	{ 0.87906581, 0.92357340, 1.00000000, },
	{ 0.85139976, 0.90559011, 1.00000000, },
	{ 0.82782969, 0.89011714, 1.00000000, },
	{ 0.80753191, 0.87667891, 1.00000000, },
	{ 0.78988728, 0.86491137, 1.00000000, },
	{ 0.77442176, 0.85453121, 1.00000000, },
};

#define AVG(i) shift[temp / 500].i * (1 - ratio) + shift[temp / 500 + 1].i * ratio

int
main(int argc, char *argv[])
{
	int temp = 6500;
	double bright = 1.0;

	int opt;
	while ((opt = getopt(argc, argv, "t:b:hv")) != -1)
	{
		switch (opt)
		{
			case 't':
				temp = strtol(optarg, NULL, 10);
				fprintf(stderr, "%d\n", temp);
				break;
			case 'b':
				bright = strtod(optarg, NULL);
				fprintf(stderr, "%f\n", bright);
				break;
			default:
				fprintf(stderr, "Usage: %s [-t temperature] [-b brightness]\n", argv[0]);
				exit(EXIT_FAILURE);
		}
	}

	Display *dpy = XOpenDisplay(NULL);
	int scr = DefaultScreen(dpy);
	Window win = RootWindow(dpy, scr);
	XRRScreenResources *res = XRRGetScreenResourcesCurrent(dpy, win);

	if (temp < 1000 || temp > 10000)
		temp = 6500;

	if (bright < 0.1 || bright > 1.0)
		bright = 1.0;

	temp -= 1000;
	double ratio = temp % 500 / 500.0;
	double gammar = bright * (AVG(r));
	double gammag = bright * (AVG(g));
	double gammab = bright * (AVG(b));

	for (int i = 0; i < res->ncrtc; i++)
	{
		int crtcxid = res->crtcs[i];
		int size = XRRGetCrtcGammaSize(dpy, crtcxid);
		XRRCrtcGamma *crtc_gamma = XRRAllocGamma(size);

		for (int j = 0; j < size; j++)
		{
			double g = 65535.0 * j / size;
			crtc_gamma->red[j] = g * gammar;
			crtc_gamma->green[j] = g * gammag;
			crtc_gamma->blue[j] = g * gammab;
		}

		XRRSetCrtcGamma(dpy, crtcxid, crtc_gamma);

		XFree(crtc_gamma);
	}

	XRRFreeScreenResources(res);
	XCloseDisplay(dpy);

	exit(EXIT_SUCCESS);
}
