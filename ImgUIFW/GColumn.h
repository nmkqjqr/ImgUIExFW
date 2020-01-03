#pragma once
#ifndef GridFW
#define GridFW
#include "GTableFW.h"
#endif // !GridFW

#ifndef GCOLUMN_DEF
#define GCOLUMN_DEF
#include "GTable.h"

namespace Grid
{
	class GColumn
	{
		friend class GTable;
	public:
		IMGUI_API	GColumn();
		IMGUI_API	~GColumn();
		IMGUI_API	GTable* getTable() const;
	private:
		GTable* table;
		void setTable(GTable* poTable);
		int getIndex() const;
	};
}
#endif // !GCOLUMN_DEF




