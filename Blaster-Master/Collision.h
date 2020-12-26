#pragma once
#include "GameObject.h"

class Collision
{
public:
	static void SweptAABB(
		float ml, float mt, float mr, float mb,
		float dx, float dy,
		float sl, float st, float sr, float sb,
		float& t, float& nx, float& ny)
	{

		float dx_entry, dx_exit, tx_entry, tx_exit;
		float dy_entry, dy_exit, ty_entry, ty_exit;

		float t_entry;
		float t_exit;

		t = -1.0f;			// no collision
		nx = ny = 0;

		//
		// Broad-phase test 
		//

		float bl = dx > 0 ? ml : ml + dx;
		float bt = dy > 0 ? mt + dy : mt;
		float br = dx > 0 ? mr + dx : mr;
		float bb = dy > 0 ? mb : mb + dy;

		if (br < sl || bl > sr || bb > st || bt < sb) return;


		if (dx == 0 && dy == 0) return;		// moving object is not moving > obvious no collision

		if (dx > 0)
		{
			dx_entry = sl - mr;
			dx_exit = sr - ml;
		}
		else if (dx < 0)
		{
			dx_entry = sr - ml;
			dx_exit = sl - mr;
		}


		if (dy > 0)
		{
			dy_entry = sb - mt;
			dy_exit = st - mb;
		}
		else if (dy < 0)
		{
			dy_entry = st - mb;
			dy_exit = sb - mt;
		}

		if (dx == 0)
		{
			tx_entry = -999999.0f;
			tx_exit = 999999.0f;
		}
		else
		{
			tx_entry = dx_entry / dx;
			tx_exit = dx_exit / dx;
		}

		if (dy == 0)
		{
			ty_entry = -99999.0f;
			ty_exit = 99999.0f;
		}
		else
		{
			ty_entry = dy_entry / dy;
			ty_exit = dy_exit / dy;
		}


		if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

		t_entry = (tx_entry > ty_entry) ? tx_entry : ty_entry;
		t_exit = (tx_exit < ty_exit) ? tx_exit : ty_exit;

		if (t_entry > t_exit)
		{
			return;
		}

		t = t_entry;

		if (tx_entry > ty_entry)
		{
			ny = 0.0f;
			dx > 0 ? nx = -1.0f : nx = 1.0f; // huong
		}
		else
		{
			nx = 0.0f;
			dy > 0 ? ny = -1.0f : ny = 1.0f; // huong
		}

	}

	static bool CheckContain(LPGAMEOBJECT objThis, LPGAMEOBJECT objThat)
	{
		float l, t, r, b;
		float lOther, tOther, rOther, bOther;

		objThis->GetBoundingBox(l, t, r, b);
		objThat->GetBoundingBox(lOther, tOther, rOther, bOther);

		return !(l > rOther || r < lOther || t < bOther || b > tOther);
	}
};

