#pragma once
#ifndef  GTableFW
#define GTableFW
#include "GTableFW.h"
#endif //  GTableFW

namespace Grid
{
#ifndef GTABLE_DEF
#define GTABLE_DEF
	using namespace std;
	class GRow;
	class GColumn;

	class GTable
	{
	private:
		std::shared_ptr<string> name;
		string getName() const;
		void setName(string pcName);
		void Initial();
	public:
		IMGUI_API GTable();
		IMGUI_API ~GTable();
		property<GTable, string, READ_WRITE>* Name;
		vector<GRow*>* Rows;
		vector<GColumn*>* Columns;
		IMGUI_API void Insert(GRow* poRow, int piIndex);
		IMGUI_API void Remove(GRow* poRow);

		IMGUI_API void Insert(GColumn* poColumn, int piIndex);
		IMGUI_API void Remove(GColumn* poColumn);

		IMGUI_API void ClearAll();
	};

#endif // !GTABLE_DEF	
}


