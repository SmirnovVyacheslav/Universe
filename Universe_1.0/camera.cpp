#include"camera.h"

Camera::Camera(HWND _hWnd) : hWnd(_hWnd)
{
	eye = XMVectorSet(0.0f, 1.0f, -1.0f, 0.0f);
	at = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	pos = Vector3(0.0f, 1.0f, -1.0f);
	viewPoint = { 0.0f, 0.0f, 0.0f };

	RECT wndSize;

	GetClientRect(hWnd, &wndSize);
	wndWidth  = wndSize.right;
	wndHeight = wndSize.bottom;

	GetWindowRect(hWnd, &wndSize);
	wndX = static_cast<int>(wndSize.left);
	wndY = static_cast<int>(wndSize.top);

	topBorder = GetSystemMetrics(SM_CYCAPTION);
	leftBorder = GetSystemMetrics(SM_CXFRAME);

	_view = XMMatrixLookAtLH(eye, at, up);
	_projection = XMMatrixPerspectiveFovLH(XM_PIDIV2, (FLOAT)wndWidth / (FLOAT)wndHeight, 0.01f, 100.0f);
}

void Camera::resize()
{
	RECT wndSize;

	GetClientRect(hWnd, &wndSize);
	wndWidth = wndSize.right;
	wndHeight = wndSize.bottom;

	GetWindowRect(hWnd, &wndSize);
	wndX = static_cast<int>(wndSize.left);
	wndY = static_cast<int>(wndSize.top);

	topBorder = GetSystemMetrics(SM_CYCAPTION);
	leftBorder = GetSystemMetrics(SM_CXFRAME);
}

XMMATRIX& Camera::view()
{
	return _view;
}

XMMATRIX& Camera::projection()
{
	return _projection;
}

void Camera::move(int _x, int _y)
{
	//SetCursorPos(wndX + leftBorder + wndWidth / 2, wndY + topBorder + wndHeight / 2);
	//return;

	//int xDiff = _x - x;
	//int yDiff = y - _y;

	//x = _x;
	//y = _y;

	//if (x <= 10)
	//{
	//	x = wndWidth - 20;
	//}
	//else if (x >= wndWidth - 10)
	//{
	//	x = 20;
	//}

	//if (y <= 30)
	//{
	//	y = wndHeight - 40;
	//}
	//else if (y >= wndHeight - 30)
	//{
	//	y = 40;
	//}

	//if (x != _x || y != _y)
	//{
	//	SetCursorPos(wndX + leftBorder + x, wndY + topBorder + y);
	//	//return;
	//}

	int half_wnd_width = wndWidth / 2;
	int half_wnd_height = wndHeight / 2;

	if (half_wnd_width == _x && half_wnd_height == _y)
	{
		return;
	}

	int xDiff = _x - half_wnd_width;
	int yDiff = half_wnd_height - _y;

	POINT pt;
	pt.x = half_wnd_width;
	pt.y = half_wnd_height;
	ClientToScreen(hWnd, &pt);
	SetCursorPos(pt.x, pt.y);
	//SetCursorPos(wndX + half_wnd_width, wndY + half_wnd_height);

	/*if (abs(xDiff) > 200 || abs(yDiff) > 200)
	{
		return;
	}*/

	xAngle += static_cast<float>(xDiff) * sensitivity;
	yAngle += static_cast<float>(yDiff) * sensitivity;

	if (yAngle > 89.0f)
		yAngle = 89.0f;
	if (yAngle < -89.0f)
		yAngle = -89.0f;

	float xAngleRad = xAngle * XM_PI / 180.0f;
	float yAngleRad = yAngle * XM_PI / 180.0f;

	float vx = cos(xAngleRad) * cos(yAngleRad);
	float vy = sin(yAngleRad);
	float vz = sin(xAngleRad) * cos(yAngleRad);

	eye = XMVectorSet(vx * radius, vy * radius, vz * radius, 0.0f);

	_view = XMMatrixLookAtLH(eye, at, up);

	pos = Vector3(vx * radius, vy * radius, vz * radius);

	viewPoint = { 0.0f, 0.0f, 0.0f };
}

bool Camera::cameraCross(Vector3 srcPos, Vector3 dstPos)
{
	/*
	Теорема. Если в пространстве задана точка М0(х0, у0, z0),
	то уравнение плоскости, проходящей через точку М0 перпендикулярно вектору нормали (A, B, C) имеет вид:

	A(x – x0) + B(y – y0) + C(z – z0) = 0.
	z = z0 - (A(x - x0) + B(y - y0)) / C
	*/

	float tmpX, tmpY, tmpZ;
	Vector3 normal = viewPoint - pos;

	tmpX = pos.x - (float)wndWidth / 2.0f;
	tmpY = pos.y - (float)wndHeight / 2.0f;
	tmpZ = pos.z - (normal.x * (tmpX - pos.x) + normal.y * (tmpY - pos.y)) / normal.z;
	Vector3 pointA = { tmpX, tmpY, tmpZ };

	tmpX = pos.x + (float)wndWidth / 2.0f;
	tmpY = pos.y - (float)wndHeight / 2.0f;
	tmpZ = pos.z - (normal.x * (tmpX - pos.x) + normal.y * (tmpY - pos.y)) / normal.z;
	Vector3 pointB = { tmpX, tmpY, tmpZ };

	tmpX = pos.x - (float)wndWidth / 2.0f;
	tmpY = pos.y + (float)wndHeight / 2.0f;
	tmpZ = pos.z - (normal.x * (tmpX - pos.x) + normal.y * (tmpY - pos.y)) / normal.z;
	Vector3 pointC = { tmpX, tmpY, tmpZ };

	tmpX = pos.x + (float)wndWidth / 2.0f;
	tmpY = pos.y + (float)wndHeight / 2.0f;
	tmpZ = pos.z - (normal.x * (tmpX - pos.x) + normal.y * (tmpY - pos.y)) / normal.z;
	Vector3 pointD = { tmpX, tmpY, tmpZ };


	Vector3 crossPoint;

	//Normal to plane
	normal = ((pointB - pointA) ^ (pointC - pointA)).normalize();
	Vector3 vectorToPlane = pointA - srcPos;

	//dst to plane using normal
	float dist = normal & vectorToPlane;
	Vector3 srcVec = dstPos - srcPos;

	//Approx to plane with interseption
	float eRes = normal & srcVec;

	if (eRes != 0) //one point
	{
		crossPoint = srcPos + srcVec * dist / eRes;
		/*
		// триангл задается тремя вершинами v1,v2,v3
		bool intersect(vertex a, vertex b, vertex &c) {
		vertex tn = normal(); // нормаль триангла
		float d1 = (a-v1).proj(tn), d2 = (b-v1).proj(tn); // проекции на нормаль траингла
		if(msign(d1)==msign(d2)) return false; // если обе точки с одной стороны (знаки совпадают) то нет пересечения
		c = (a + ((b - a) * (-d1 / (d2 - d1)))); // в c точка лежащая в плоскости треугольника в месте пересечения
		if( (((v2 - v1) ^ (c - v1)) * tn) <= 0) return false; // функции проверки попадания внутрь триангла точки c
		if( (((v3 - v2) ^ (c - v2)) * tn) <= 0) return false; // ^ - векторное, * - скалярное произведение векторов
		if( (((v1 - v3) ^ (c - v3)) * tn) <= 0) return false;
		return true; // если точка попала в триангл
		}
		*/

		if ((((pointB - pointA) ^ (crossPoint - pointA)) & normal) <= 0)
			return false;
		if ((((pointD - pointB) ^ (crossPoint - pointB)) & normal) <= 0)
			return false;
		if ((((pointA - pointC) ^ (crossPoint - pointC)) & normal) <= 0)
			return false;
		if ((((pointC - pointD) ^ (crossPoint - pointD)) & normal) <= 0)
			return false;

		return true;
	}
	else
	{
		return false;
	}

	return false;
}