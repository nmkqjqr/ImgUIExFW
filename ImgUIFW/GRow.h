#pragma once
#ifndef  GTableFW
#define GTableFW
#include "GTableFW.h"
#endif //  GTableFW

#ifndef GRIDROW_DEF
#define GRIDROW_DEF 
#include "GTable.h"

namespace Grid
{
	using namespace std;
	class GCell;
	class GRow
	{
		friend class GTable;
	private:
		int index;
		GTable* table;
		GTable* getTable() const;
		void setTable(GTable* poTable);
		int getIndex() const;
		void Initial();

	public:
		IMGUI_API GRow();
		IMGUI_API ~GRow();
		vector<GCell*>* Cells;
		property<GRow, GTable*, READ_ONLY>* Table;
		property<GRow, int, READ_ONLY>* Index;
		IMGUI_API void Insert(GCell* poCell, int piIndex);
		IMGUI_API void Add(GCell* poCell);
		IMGUI_API void Remove(GCell* poCell);
		IMGUI_API void ClearAll();
	};
}

#endif // !GRIDROW_DEF

