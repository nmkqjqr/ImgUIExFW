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

		string getValue() const;
		void setValue(string pcValue);

		string getContrastValue() const;
		void setContrastValue(string pcValue);

		GRow* getRow() const;
		void setRow(GRow* poRow);

		GColumn* getColumn() const;
		void setColumn(GColumn* poColumn);

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

