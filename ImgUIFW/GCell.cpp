#include "GCell.h"

namespace Grid
{
	GCell::GCell()
	{
		this->Initial("");
	}

	GCell::GCell(string const pcText)
	{
		this->Initial(pcText);
	}

	GCell::~GCell()
	{
		this->setRow(nullptr);
		this->setColumn(nullptr);
		delete this->Row;
		delete this->Column;
		delete	this->ContrastValue;
		delete	this->Value;
	}

	void GCell::Initial(string const pcText)
	{
		this->value = pcText;
		this->column = nullptr;
		this->row = nullptr;

		this->Value = new property<GCell, string, READ_WRITE>();
		Value->setContainer(this);
		Value->setter(&GCell::setValue);
		Value->getter(&GCell::getValue);

		this->ContrastValue = new property<GCell, string, READ_WRITE>();
		ContrastValue->setContainer(this);
		ContrastValue->setter(&GCell::setContrastValue);
		ContrastValue->getter(&GCell::getContrastValue);

		this->Row = new property<GCell, GRow*, READ_ONLY>();
		Row->setContainer(this);
		Row->getter(&GCell::getRow);

		this->Column = new property<GCell, GColumn*, READ_ONLY>();
		Column->setContainer(this);
		Column->getter(&GCell::getColumn);
	}

	string GCell::getValue() const
	{
		return this->value;
	}

	void GCell::setValue(string pcValue)
	{
		this->value = pcValue;
	}

	string GCell::getContrastValue() const
	{
		return this->contrastValue;
	}

	void GCell::setContrastValue(string pcValue)
	{
		this->contrastValue = pcValue;
	}

	GRow* GCell::getRow() const
	{
		return this->row;
	}

	void GCell::setRow(GRow* poRow)
	{
		this->row = poRow;
	}

	GColumn* GCell::getColumn() const
	{
		GColumn* loRefColumn = this->column;
		if (loRefColumn)
		{
			if (loRefColumn->getTable() == nullptr)
			{
				loRefColumn = nullptr;
			}
		}

		return loRefColumn;
	}

	void GCell::setColumn(GColumn* poColumn)
	{
		this->column = poColumn;
	}

	/*int GCell::getIndex() const
	{
		if (this->row)
		{
			ptr_list<GCell> loCell = this->row.get()->Cells;
			int liIndex = 0;
			for (ptr_list<GCell>::iterator loCitor = loCell.begin(); loCitor != loCell.end(); loCitor++)
			{
				GCell loCell = *loCitor;
				if ((&loCell) == this)
				{
					return liIndex;
				}

				liIndex++;
			}
		}

		return -1;
	}*/
}