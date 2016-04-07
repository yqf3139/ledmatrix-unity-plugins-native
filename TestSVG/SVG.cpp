#include "SVG.h"
#include "nanosvg.h"

FILE *pConsole;
NSVGimage* g_image = NULL;

float fx0, fy0, fx1, fy1;
int pathnum;
int pointnum;
int colorbuf[MAXPATH];
int pathbuf[MAXPATH];
float pointbuf[MAXPOINT];

int *getColorbuf() { return colorbuf; }
int *getPathbuf() { return pathbuf; }
float *getPointbuf() { return pointbuf; }

long long dlltest()
{
	return 0;
}

void construct()
{
	AllocConsole();
	freopen_s(&pConsole, "CONOUT$", "wb", stdout);
}

void deconstruct()
{

}

static float distPtSeg(float x, float y, float px, float py, float qx, float qy)
{
	float pqx, pqy, dx, dy, d, t;
	pqx = qx - px;
	pqy = qy - py;
	dx = x - px;
	dy = y - py;
	d = pqx*pqx + pqy*pqy;
	t = pqx*dx + pqy*dy;
	if (d > 0) t /= d;
	if (t < 0) t = 0;
	else if (t > 1) t = 1;
	dx = px + t*pqx - x;
	dy = py + t*pqy - y;
	return dx*dx + dy*dy;
}

static void cubicBez(float x1, float y1, float x2, float y2,
	float x3, float y3, float x4, float y4,
	float tol, int level)
{
	float x12, y12, x23, y23, x34, y34, x123, y123, x234, y234, x1234, y1234;
	float d;

	if (level > 14) return;

	x12 = (x1 + x2)*0.5f;
	y12 = (y1 + y2)*0.5f;
	x23 = (x2 + x3)*0.5f;
	y23 = (y2 + y3)*0.5f;
	x34 = (x3 + x4)*0.5f;
	y34 = (y3 + y4)*0.5f;
	x123 = (x12 + x23)*0.5f;
	y123 = (y12 + y23)*0.5f;
	x234 = (x23 + x34)*0.5f;
	y234 = (y23 + y34)*0.5f;
	x1234 = (x123 + x234)*0.5f;
	y1234 = (y123 + y234)*0.5f;

	d = distPtSeg(x1234, y1234, x1, y1, x4, y4);
	if (d > tol*tol) {
		cubicBez(x1, y1, x12, y12, x123, y123, x1234, y1234, tol, level + 1);
		cubicBez(x1234, y1234, x234, y234, x34, y34, x4, y4, tol, level + 1);
	}
	else {
		pointbuf[pointnum * 2] = x4;
		pointbuf[pointnum * 2 + 1] = y4;
		pointnum++;
		pathbuf[pathnum]++;
		if (pointnum == 1)
		{
			fx0 = fx1 = x4;
			fy0 = fy1 = y4;
		}
		else
		{
			if (x4 > fx0) { fx0 = x4; }
			if (x4 < fx1) { fx1 = x4; }
			if (y4 > fy0) { fy0 = y4; }
			if (y4 < fy1) { fy1 = y4; }
		}
	}
}

void drawPath(float* pts, int npts, char closed, float tol)
{
	int i;
	for (i = 0; i < npts - 1; i += 3) {
		float* p = &pts[i * 2];
		cubicBez(p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], tol, 0);
	}
	//for (i = 0; i < npts; i ++) {
	//	float* p = &pts[i * 2];
	//	pointbuf[pointnum * 2] = p[0];
	//	pointbuf[pointnum * 2 + 1] = p[1];
	//	pointnum++;
	//	pathbuf[pathnum]++;
	//}
}

int parse(char *name)
{
	pathnum = pointnum = 0;
	g_image = nsvgParseFromFile(name, "px", 96.0f);
	if (g_image == NULL)
	{
		printf("error while parsing %s\n", name);
		return 0;
	}

	NSVGshape* shape;
	NSVGpath* path;

	float px = 1.0f;

	int shapenum = 0;
	for (shape = g_image->shapes; shape != NULL; shape = shape->next) {
		shapenum++;
		for (path = shape->paths; path != NULL; path = path->next) {
			colorbuf[pathnum] = shape->fill.color;
			pathbuf[pathnum] = 0;
			drawPath(path->pts, path->npts, path->closed, px);
			pathnum++;
		}
	}

	int offsetx = -(fx0 + fx1)/2, offsety = -(fy0 + fy1);
	for (int i = 0; i < pointnum; i++)
	{
		pointbuf[2 * i] += offsetx;
		pointbuf[2 * i + 1] += offsety;
	}

	printf("shapenum %d, pathnum %d, pointnum %d\n", shapenum, pathnum, pointnum);
	printf("fx0 %f, fy0 %f, fx1 %f, fy1 %f\n", fx0, fy0, fx1, fy1);

	nsvgDelete(g_image);
	return pathnum;
}