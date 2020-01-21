#include "GRow.h"
#include "GCell.h"

using namespace std;
namespace Grid
{
	GRow::GRow()
	{
		this->Initial();
	}

	GRow::~GRow()
	{
		this->ClearAll();
		this->setTable(nullptr);
	}

	GTable* GRow::getTable() const
	{
		return this->table;
	}

	void GRow::setTable(GTable* poTable)
	{
		if (this->table != poTable)
		{
			this->table = poTable;
			if (this->Cells->size() > 0)
			{
				bool llShouldResetColumns = this->table && this->table->Columns->size() > 0;
				int liColIndex = 0;
				for (vector<GCell*>::iterator loCell = this->Cells->begin(); loCell != this->Cells->end(); loCell++)
				{
					if (llShouldResetColumns)
					{
						if (liColIndex < this->table->Columns->size())
						{
							(*loCell)->setColumn((*(this->table->Columns))[liColIndex]);
						}
						else
						{
							(*loCell)->setColumn(nullptr);
						}
					}
					else
					{
						(*loCell)->setColumn(nullptr);
					}

					liColIndex++;
				}
			}
		}
	}

	int GRow::getIndex() const
	{
		return -1;
	}

	void GRow::Initial()
	{
		this->table = nullptr;
		this->Cells = new vector<GCell*>();

		this->Table = new property<GRow, GTable*, READ_ONLY>();
		Table->setContainer(this);
		Table->getter(&GRow::getTable);

		this->Index = new property<GRow, int, READ_ONLY>();
		Index->setContainer(this);
		Index->getter(&GRow::getIndex);
	}

	void GRow::Insert(GCell* poCell, int piIndex)
	{
		if (&poCell && (&this->Cells))
		{
			vector<GCell*>& loCells = *(this->Cells);
			int liSize = loCells.size();
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

				vector<GCell*>::iterator loIndexItr = loCells.begin();
				for (int liIndex = 0; liIndex < beforeIndex; liIndex++)
				{
					loIndexItr++;
				}

				loCells.insert(loIndexItr, poCell);
			}
			else
			{
				loCells.push_back(poCell);
			}

			poCell->setRow(this);
			if (this->table)
			{
				vector<GColumn*>& loColumns = *(this->table->Columns);
				if (loColumns.size() > 0 && loColumns.size() > piIndex)
				{
					poCell->setColumn(loColumns[piIndex]);
				}
			}
			else
			{
				poCell->setColumn(nullptr);
			}
		}
	}

	void GRow::Add(GCell* poCell)
	{
		this->Insert(poCell, INT32_MAX);
	}

	void GRow::Remove(GCell* poCell)
	{
		for (vector<GCell*>::iterator loCell = this->Cells->begin(); loCell != this->Cells->end(); loCell++)
		{
			if (*loCell == poCell)
			{
				this->Cells->erase(loCell);
				poCell->~GCell();
				return;
			}
		}
	}

	void GRow::ClearAll()
	{
		vector<GCell*>::iterator loCell = this->Cells->begin();
		while (loCell != this->Cells->end())
		{
			GCell* loGCell = *loCell;
			if (&loCell)
			{
				loGCell->~GCell();
			}

			loCell++;
		}

		this->Cells->clear();
	}
}

