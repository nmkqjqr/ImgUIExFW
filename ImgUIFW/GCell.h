#pragma once
#ifndef  GTableFW
#define GTableFW
#include "GTableFW.h"
#endif //  GTableFW

#ifndef GCELL_DEF
#define GCELL_DEF
#include "GRow.h"
#include "GColumn.h"

namespace Grid
{
	using namespace std;
	class GCell
	{
		friend class GRow;
	private:
		string value;
		string contrastValue;
		GRow* row;
		GColumn* column;

		void Initial(string const pcText);

		IMGUI_API string getValue() const;
		IMGUI_API void setValue(string pcValue);

		IMGUI_API string getContrastValue() const;
		IMGUI_API void setContrastValue(string pcValue);

		IMGUI_API GRow* getRow() const;
		IMGUI_API void setRow(GRow* poRow);

		IMGUI_API GColumn* getColumn() const;
		IMGUI_API void setColumn(GColumn* poColumn);

	public:
		IMGUI_API GCell();
		IMGUI_API GCell(string const pcValue);
		IMGUI_API ~GCell();
		property<GCell, GRow*, READ_ONLY>* Row;
		property<GCell, GColumn*, READ_ONLY>* Column;
		property<GCell, string, READ_WRITE>* Value;
		property<GCell, string, READ_WRITE>* ContrastValue;
	};
}

#endif // !GCELL_DEF

