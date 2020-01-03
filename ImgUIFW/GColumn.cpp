#include "GTable.h"
#include "GColumn.h"

namespace Grid
{
	GColumn::GColumn()
	{
	}
	GColumn::~GColumn()
	{
	}

	GTable* GColumn::getTable() const
	{
		return nullptr;
	}
	void GColumn::setTable(GTable* poTable)
	{
	}
	int GColumn::getIndex() const
	{
		return 0;
	}
}

