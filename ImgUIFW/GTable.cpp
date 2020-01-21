#include "GTable.h"
#include "GRow.h"
#include "GColumn.h"

using namespace std;
namespace Grid
{
	GTable::GTable()
	{
		this->Initial();
	}

	GTable::~GTable()
	{
		this->ClearAll();
		delete this->Rows;
		delete this->Columns;
	}

	void GTable::Insert(GRow* poRow, int piIndex)
	{
		if (poRow)
		{
			vector<GRow*>& loRows = *(this->Rows);
			int liSize = loRows.size();
			if (piIndex<0 || piIndex>liSize)
			{
				piIndex = liSize;
			}

			if (liSize != piIndex)
			{
				int beforeIndex = piIndex - 1;
				if (beforeIndex < 0)
				{
					beforeIndex = 0;
				}

				vector<GRow*>::iterator loIndexItr = loRows.begin();
				for (int liIndex = 0; liIndex < beforeIndex; liIndex++)
				{
					loIndexItr++;
				}

				loRows.insert(loIndexItr, poRow);
			}
			else
			{
				loRows.push_back(poRow);
			}

			poRow->setTable(this);
		}
	}

	void GTable::Remove(GRow* poRow)
	{
		for (vector<GRow*>::iterator loRow = this->Rows->begin(); loRow != this->Rows->end(); loRow++)
		{
			if (*loRow == poRow)
			{
				this->Rows->erase(loRow);
				poRow->~GRow();
				return;
			}
		}
	}

	void GTable::Insert(GColumn* poColumn, int piIndex)
	{
		if (poColumn)
		{
			vector<GColumn*>& loColumns = *(this->Columns);
			int liSize = loColumns.size();
			if (piIndex<0 || piIndex>liSize)
			{
				piIndex = liSize;
			}

			if (liSize != piIndex)
			{
				int beforeIndex = piIndex - 1;
				if (beforeIndex < 0)
				{
					beforeIndex = 0;
				}

				vector<GColumn*>::iterator loIndexItr = loColumns.begin();
				for (int liIndex = 0; liIndex < beforeIndex; liIndex++)
				{
					loIndexItr++;
				}

				loColumns.insert(loIndexItr, poColumn);
			}
			else
			{
				loColumns.push_back(poColumn);
			}

			poColumn->setTable(this);
		}
	}

	void GTable::Remove(GColumn* poColumn)
	{
		for (vector<GColumn*>::iterator loColomn = this->Columns->begin(); loColomn != this->Columns->end(); loColomn++)
		{
			if (*loColomn == poColumn)
			{
				this->Columns->erase(loColomn);
				poColumn->~GColumn();
				return;
			}
		}
	}

	void GTable::setName(string pcName)
	{
		this->name = make_shared<string>(pcName);
	}

	string GTable::getName() const
	{
		return this->name.get()->c_str();
	}

	void GTable::Initial()
	{
		this->Name = new property<GTable, string, READ_WRITE>();
		Name->setContainer(this);
		Name->setter(&GTable::setName);
		Name->getter(&GTable::getName);

		this->Rows = new vector<GRow*>();
		this->Columns = new vector<GColumn*>();
	}

	void GTable::ClearAll()
	{
		if (this->Rows)
		{
			vector<GRow*>::iterator loRow = this->Rows->begin();
			while (loRow != this->Rows->end())
			{
				GRow*& loTRow = *loRow;
				loRow++;
				delete loTRow;
			}

			this->Rows->clear();
		}

		if (this->Columns)
		{
			vector<GColumn*>::iterator loColumn = this->Columns->begin();
			while (loColumn != this->Columns->end())
			{
				GColumn*& loGColumn = *loColumn;
				loColumn++;
				delete loGColumn;
			}

			this->Columns->clear();
		}

	}
}

