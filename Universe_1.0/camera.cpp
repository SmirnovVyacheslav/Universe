#include"camera.h"

Camera::Camera(HWND _hWnd) : hWnd(_hWnd)
{
	eye = XMVectorSet(0.0f, 1.0f, -1.0f, 0.0f);
	at = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	pos = Vector3(0.0f, 1.0f, -1.0f);

	float tmpX, tmpY, tmpZ;
	Vector3 normal = viewPoint - pos;

	tmpX = pos.x - (float)wndWidth / 2.0f;
	tmpY = pos.y - (float)wndHeight / 2.0f;
	tmpZ = pos.z - (normal.x * (tmpX - pos.x) + normal.y * (tmpY - pos.y)) / normal.z;
	Vector3 pointA = { tmpX, tmpY, tmpZ };
	camera_def.a = pointA;

	tmpX = pos.x + (float)wndWidth / 2.0f;
	tmpY = pos.y - (float)wndHeight / 2.0f;
	tmpZ = pos.z - (normal.x * (tmpX - pos.x) + normal.y * (tmpY - pos.y)) / normal.z;
	Vector3 pointB = { tmpX, tmpY, tmpZ };
	camera_def.b = pointB;

	tmpX = pos.x - (float)wndWidth / 2.0f;
	tmpY = pos.y + (float)wndHeight / 2.0f;
	tmpZ = pos.z - (normal.x * (tmpX - pos.x) + normal.y * (tmpY - pos.y)) / normal.z;
	Vector3 pointC = { tmpX, tmpY, tmpZ };
	camera_def.c = pointC;

	tmpX = pos.x + (float)wndWidth / 2.0f;
	tmpY = pos.y + (float)wndHeight / 2.0f;
	tmpZ = pos.z - (normal.x * (tmpX - pos.x) + normal.y * (tmpY - pos.y)) / normal.z;
	Vector3 pointD = { tmpX, tmpY, tmpZ };
	camera_def.d = pointD;

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

XMMATRIX Camera::view()
{
	camera_mutex.lock();
	XMMATRIX tmp_view = _view;
	camera_mutex.unlock();
	return tmp_view;
}

XMMATRIX& Camera::projection()
{
	return _projection;
}

void Camera::move(int _x, int _y)
{
	/*if (abs(xDiff) > 200 || abs(yDiff) > 200)
	{
		return;
	}*/

	int xDiff = _x;
	int yDiff = _y;

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

	camera_mutex.lock();
	_view = XMMatrixLookAtLH(eye, at, up);
	camera_mutex.unlock();

	pos = Vector3(vx * radius, vy * radius, vz * radius);


	float tmpX, tmpY, tmpZ;
	Vector3 normal = viewPoint - pos;

	tmpX = pos.x - (float)wndWidth / 2.0f;
	tmpY = pos.y - (float)wndHeight / 2.0f;
	tmpZ = pos.z - (normal.x * (tmpX - pos.x) + normal.y * (tmpY - pos.y)) / normal.z;
	Vector3 pointA = { tmpX, tmpY, tmpZ };
	camera_def.a = pointA;

	tmpX = pos.x + (float)wndWidth / 2.0f;
	tmpY = pos.y - (float)wndHeight / 2.0f;
	tmpZ = pos.z - (normal.x * (tmpX - pos.x) + normal.y * (tmpY - pos.y)) / normal.z;
	Vector3 pointB = { tmpX, tmpY, tmpZ };
	camera_def.b = pointB;

	tmpX = pos.x - (float)wndWidth / 2.0f;
	tmpY = pos.y + (float)wndHeight / 2.0f;
	tmpZ = pos.z - (normal.x * (tmpX - pos.x) + normal.y * (tmpY - pos.y)) / normal.z;
	Vector3 pointC = { tmpX, tmpY, tmpZ };
	camera_def.c = pointC;

	tmpX = pos.x + (float)wndWidth / 2.0f;
	tmpY = pos.y + (float)wndHeight / 2.0f;
	tmpZ = pos.z - (normal.x * (tmpX - pos.x) + normal.y * (tmpY - pos.y)) / normal.z;
	Vector3 pointD = { tmpX, tmpY, tmpZ };
	camera_def.d = pointD;

	viewPoint = { 0.0f, 0.0f, 0.0f };
}

bool Camera::cameraCross(Vector3 srcPos, Vector3 dstPos)
{
	/*
	�������. ���� � ������������ ������ ����� �0(�0, �0, z0),
	�� ��������� ���������, ���������� ����� ����� �0 ��������������� ������� ������� (A, B, C) ����� ���:

	A(x � x0) + B(y � y0) + C(z � z0) = 0.
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
		// ������� �������� ����� ��������� v1,v2,v3
		bool intersect(vertex a, vertex b, vertex &c) {
		vertex tn = normal(); // ������� ��������
		float d1 = (a-v1).proj(tn), d2 = (b-v1).proj(tn); // �������� �� ������� ��������
		if(msign(d1)==msign(d2)) return false; // ���� ��� ����� � ����� ������� (����� ���������) �� ��� �����������
		c = (a + ((b - a) * (-d1 / (d2 - d1)))); // � c ����� ������� � ��������� ������������ � ����� �����������
		if( (((v2 - v1) ^ (c - v1)) * tn) <= 0) return false; // ������� �������� ��������� ������ �������� ����� c
		if( (((v3 - v2) ^ (c - v2)) * tn) <= 0) return false; // ^ - ���������, * - ��������� ������������ ��������
		if( (((v1 - v3) ^ (c - v3)) * tn) <= 0) return false;
		return true; // ���� ����� ������ � �������
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

cameraDef& Camera::get_def()
{
	return camera_def;
}