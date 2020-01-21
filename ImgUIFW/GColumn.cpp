#include "GTable.h"
#include "GColumn.h"
#include <ctime>

namespace Grid
{
	GColumn::GColumn()
	{
	}

	GColumn::GColumn(string psName)
	{
		this->name = psName;
	}

	GColumn::~GColumn()
	{
		this->setTable(nullptr);
	}

	GTable* GColumn::getTable() const
	{
		return this->table;
	}

	void GColumn::setTable(GTable* poTable)
	{
		this->table = poTable;
	}

	void GColumn::setName(string name)
	{
		if (this->name.compare(name) != 0)
		{
			this->name = name;
		}

		if (this->name.empty())
		{
			std::clock_t c_tm = std::clock();
			this->name = "GCOLUMN" + to_string(1000.0 * c_tm / CLOCKS_PER_SEC);
		}
	}

	string GColumn::getName() const
	{
		return this->name;
	}

	void GColumn::setText(string text)
	{
		this->text = text;
	}

	string GColumn::getText() const
	{
		if (this->text.empty())
		{
			return this->name;
		}

		return this->text;
	}

}

