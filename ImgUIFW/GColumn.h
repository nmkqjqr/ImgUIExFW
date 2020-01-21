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
	using namespace std;
	class GColumn
	{
		friend class GTable;
	public:
		IMGUI_API	GColumn();
		IMGUI_API	GColumn(string psName);
		IMGUI_API	~GColumn();
		IMGUI_API	GTable* getTable() const;
		IMGUI_API  void setTable(GTable* poTable);
		IMGUI_API void setName(string name);
		IMGUI_API string getName() const;

		IMGUI_API void setText(string text);
		IMGUI_API string getText() const;
	private:
		GTable* table;
		string name;
		string text;
	};
}
#endif // !GCOLUMN_DEF




