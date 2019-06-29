#include "State.h"
#include "Ball.h"

#define HOTRED RGB(245, 66, 105)
#define MINT RGB(64, 237, 159)
#define LIGHTBLUE RGB(85, 164, 230)
#define BLACK RGB(0,0,0)
#define WHITE RGB(255,255,255)

void VerticalState::Update()
{
	BallManager* BM = BallManager::GetInstance();
	for (auto b : BM->balls)
	{
		b->Move();
		b->CheckCollision();
	}
}

void VerticalState::Render(const HDC & hdc)
{
	HBRUSH redbrush = CreateSolidBrush(HOTRED);
	HPEN nopen = CreatePen(PS_SOLID, 0, BLACK);
	HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, redbrush);
	HPEN oldpen = (HPEN)SelectObject(hdc, nopen);
	BallManager* BM = BallManager::GetInstance();
	
	for (auto B : BM->balls)
	{
		int x = B->pos.x;	int y = B->pos.y;	int r = B->radius;
		Ellipse(hdc, x - r, y - r, x + r, y + r);
	}

	(HBRUSH)SelectObject(hdc, oldbrush);
	(HPEN)SelectObject(hdc, oldpen);
	DeleteObject(redbrush);
	DeleteObject(nopen);
}

void HorizontalState::Update()
{
	BallManager* BM = BallManager::GetInstance();
	for (auto b : BM->balls)
	{
		b->Move();
		b->CheckCollision();
	}
}

void HorizontalState::Render(const HDC & hdc)
{
	HBRUSH bluebrush = CreateSolidBrush(LIGHTBLUE);
	HPEN nopen = CreatePen(PS_SOLID, 0, BLACK);
	HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, bluebrush);
	HPEN oldpen = (HPEN)SelectObject(hdc, nopen);
	BallManager* BM = BallManager::GetInstance();

	for (auto B : BM->balls)
	{
		int x = B->pos.x;	int y = B->pos.y;	int r = B->radius;
		Ellipse(hdc, x - r, y - r, x + r, y + r);
	}

	(HBRUSH)SelectObject(hdc, oldbrush);
	(HPEN)SelectObject(hdc, oldpen);
	DeleteObject(bluebrush);
	DeleteObject(nopen);
}

void DiagonalState::Update()
{
	BallManager* BM = BallManager::GetInstance();
	for (auto b : BM->balls)
	{
		b->Move();
		b->CheckCollision();
	}
}

void DiagonalState::Render(const HDC & hdc)
{
	HBRUSH mintbrush = CreateSolidBrush(MINT);
	HPEN nopen = CreatePen(PS_SOLID, 0, BLACK);
	HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, mintbrush);
	HPEN oldpen = (HPEN)SelectObject(hdc, nopen);
	BallManager* BM = BallManager::GetInstance();

	for (auto B : BM->balls)
	{
		int x = B->pos.x;	int y = B->pos.y;	int r = B->radius;
		Ellipse(hdc, x - r, y - r, x + r, y + r);
	}

	(HBRUSH)SelectObject(hdc, oldbrush);
	(HPEN)SelectObject(hdc, oldpen);
	DeleteObject(mintbrush);
	DeleteObject(nopen);
}
