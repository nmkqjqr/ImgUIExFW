#include "GTableTest.h"
#include <imgui.h>

namespace Test
{
	GTableTest::GTableTest()
	{
		this->Initial();
	}

	GTableTest::~GTableTest()
	{
	}

	void GTableTest::setConnection(string pcConnection)
	{
		if (this->connection.compare(pcConnection) != 0)
		{
			this->connection = pcConnection;
			if (this->SQL)
			{
				this->SQL->close();
				delete this->SQL;
			}

			if (this->connection.empty() == false)
			{
				this->SQL = new session(this->dbName, this->connection);
				this->tableName = "";
				this->Tables->clear();

				rowset<row> loTableNames = (this->SQL->prepare << "SELECT TABLE_NAME  FROM USER_TABLES");
				for (rowset<row>::iterator loRow = loTableNames.begin(); loRow != loTableNames.end(); loRow++)
				{
					(*(this->Tables))[(*loRow).get<string>("TABLE_NAME")] = false;
				}
			}
		}

	}

	string GTableTest::getConnection() const
	{
		return this->connection;
	}

	void GTableTest::setTableName(string pcTableName)
	{
		if (this->tableName._Equal(pcTableName) == false)
		{
			this->tableName = pcTableName;
			if (this->tableName.empty() == false)
			{
				if (this->SQL)
				{
					/*	(this->SQL->prepare << "select C_NAME,I_NAME from T_CONNECT");*/
				}
			}
		}
	}

	string GTableTest::getTableName() const
	{
		return this->tableName;
	}

	void GTableTest::Initial()
	{
		this->Tables = new map<string, bool>();
		this->dbName = "oracle";
		this->connection = "";

		this->TableName = new property<GTableTest, string, READ_WRITE>();
		TableName->setContainer(this);
		TableName->setter(&GTableTest::setTableName);
		TableName->getter(&GTableTest::getTableName);

		this->Connection = new property<GTableTest, string, READ_WRITE>();
		Connection->setContainer(this);
		Connection->setter(&GTableTest::setConnection);
		Connection->getter(&GTableTest::getConnection);
		this->_Table = new GTable();
	}

	void GTableTest::ShowWindow()
	{
		ImGui::Begin(u8"数据库与Vulkan联合测试");
		char buf[200] = "service=FAST user=V45GDYH password=1 charset=utf8 ncharset=utf8";
		if (this->connection.empty() == false)
		{
			strcpy_s(buf, this->connection.c_str());
		}

		ImGui::SetNextItemWidth(400);
		ImGui::InputText(u8"连接字符串", buf, IM_ARRAYSIZE(buf));
		string lcNewCon = buf;
		this->setConnection(lcNewCon);
		ImGui::SameLine();

		ImGui::SetNextItemWidth(80);
		const char* loDBs[] = { "oracle", "sqlite3" };
		static const char* lcDBName = loDBs[0];
		if (ImGui::BeginCombo(u8"数据库", lcDBName, ImGuiComboFlags_::ImGuiComboFlags_None))
		{
			for (int liIndex = 0; liIndex < IM_ARRAYSIZE(loDBs); liIndex++)
			{
				bool is_selected = (lcDBName == loDBs[liIndex]);
				if (ImGui::Selectable(loDBs[liIndex], is_selected))
					lcDBName = loDBs[liIndex];
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}

			ImGui::EndCombo();
		}

		this->dbName = lcDBName;
		ImGui::SameLine();

		ImGui::SetNextItemWidth(200);
		static const char* lcDefaultName = (*(this->Tables->begin())).first.c_str();
		if (ImGui::BeginCombo(u8"表格", lcDefaultName, ImGuiComboFlags_::ImGuiComboFlags_None))
		{
			for (map<string, bool>::iterator loName = this->Tables->begin(); loName != this->Tables->end(); loName++)
			{
				bool is_selected = false;
				const char* lcTableName = (*loName).first.c_str();
				if (ImGui::Selectable(lcTableName, &is_selected))
				{
					lcDefaultName = lcTableName;
					(*(this->TableName)) = lcTableName;
				}

				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}

			ImGui::EndCombo();
		}

		ImGui::SameLine();
		ImGui::SetNextItemWidth(80);

		if (ImGui::Button(u8"查询"))
		{
			this->LoadTable();
		}

		this->ShowTable();

		ImGui::End();
	}

	void GTableTest::ShowTable()
	{
		if (this->_Table->Columns->size() > 0)
		{
			const ImDrawList* parent_draw_list = ImGui::GetWindowDrawList();
			static ImVector<int> selection;
			ImGuiTableFlags loTableFlags =
				ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_MultiSortable
				| ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_BordersVFullHeight
				| ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY
				| ImGuiTableFlags_ScrollFreezeTopRow;// | ImGuiTableFlags_ScrollFreezeLeftColumn; */
			int liColumnCount = this->_Table->Columns->size() + 1;
			if (ImGui::BeginTable("GTable", liColumnCount, loTableFlags))
			{
				ImU32 liIndex = 0;
				ImGui::TableSetupColumn("Index", ImGuiTableColumnFlags_WidthAlwaysAutoResize, -1.0f, liIndex);
				liIndex++;
				for (vector<GColumn*>::iterator loColumnIte = this->_Table->Columns->begin(); loColumnIte != this->_Table->Columns->end(); loColumnIte++)
				{
					string lcColumnName = (*loColumnIte)->getName();
					ImGui::TableSetupColumn(lcColumnName.c_str(), (liIndex == 1 ? ImGuiTableColumnFlags_DefaultSort : ImGuiTableColumnFlags_None) | ImGuiTableColumnFlags_WidthAlwaysAutoResize, -1.0f, liIndex);
					liIndex++;
				}

				ImGui::TableAutoHeaders();

				ImGuiListClipper loImGuiClipper;
				int liRouCount = this->_Table->Rows->size();
				loImGuiClipper.Begin(liRouCount);
				while (loImGuiClipper.Step())
				{
					for (int liRIndex = loImGuiClipper.DisplayStart; liRIndex < loImGuiClipper.DisplayEnd && liRIndex < liRouCount; liRIndex++)
					{
						char label[32];
						/*for (vector<GRow*>::iterator loRow = this->_Table->Rows.begin(); loRow != this->_Table->Rows.end() && row_n < 500; loRow++)*/
						{
							sprintf_s(label, sizeof(label), to_string(liRIndex).c_str());
							ImGui::PushID(liRIndex);
							ImGui::TableNextRow();
							const bool item_is_selected = selection.contains(liRIndex);
							if (ImGui::Selectable(label, item_is_selected, ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowItemOverlap, ImVec2(0, 20.0f)))
							{
								if (ImGui::GetIO().KeyCtrl)
								{
									if (item_is_selected)
										selection.find_erase_unsorted(liRIndex);
									else
										selection.push_back(liRIndex);
								}
								else
								{
									selection.clear();
									selection.push_back(liRIndex);
								}
							}

							GRow* loGRow = (*(this->_Table->Rows))[liRIndex];
							int liCellIndex = 0;
							for (vector<GColumn*>::iterator loColumnIte = this->_Table->Columns->begin(); loColumnIte != this->_Table->Columns->end(); loColumnIte++)
							{
								ImGui::TableNextCell();
								string lcCellValue = "";
								GCell* loCell = (*(loGRow->Cells))[liCellIndex];
								if (loCell)
								{
									lcCellValue = (*(loCell->Value));
								}

								ImGui::Text(lcCellValue.c_str());
								liCellIndex++;
							}

							ImGui::PopID();
						}
					}
				}
				loImGuiClipper.End();

				const ImDrawList* table_draw_list = ImGui::GetWindowDrawList();
				ImGui::EndTable();
			}
		}
	}

	void GTableTest::LoadTable()
	{
		this->_Table->~GTable();
		this->_Table = new GTable();
		if (this->getTableName().size() > 0)
		{
			if (this->SQL)
			{
				string lcSql = "SELECT *  FROM " + this->getTableName();
				rowset<row> loRowsets = (this->SQL->prepare << lcSql);
				if (&loRowsets)
				{
					GColumn* loGColumn;
					rowset<row>::iterator loTempRow = loRowsets.begin();
					if (&loTempRow && loTempRow != loRowsets.end())
					{
						for (size_t liIndex = 0; liIndex < loTempRow->size(); liIndex++)
						{
							column_properties loColumnProp = loTempRow->get_properties(liIndex);
							loGColumn = new GColumn(loColumnProp.get_name());
							this->_Table->Insert(loGColumn, INT32_MAX);
						}

						for (rowset<row>::iterator loItRow = loRowsets.begin(); loItRow != loRowsets.end(); loItRow++)
						{
							const row& loTempRow = (*loItRow);
							GRow* loGRow = CreateRowBySOCIrow(loTempRow);
							this->_Table->Insert(loGRow, INT32_MAX);
						}
					}
				}
			}
		}
	}

	GRow* Test::CreateRowBySOCIrow(const soci::row& poRow)
	{
		GRow* loRow = nullptr;
		if (&poRow && poRow.size() > 0)
		{
			loRow = new GRow();
			for (size_t liIndex = 0; liIndex < poRow.size(); liIndex++)
			{
				GCell* loCell = nullptr;
				column_properties loColumnProperty = poRow.get_properties(liIndex);
				data_type lodtype = loColumnProperty.get_data_type();
				indicator loIndicator = poRow.get_indicator(liIndex);
				if ((loIndicator == indicator::i_null) != 0 || (loIndicator == indicator::i_truncated) != 0)
				{
					loCell = new GCell();
					loRow->Add(loCell);
					continue;
				}

				string lcValue = "";
				switch (lodtype)
				{
				default:
				case soci::dt_xml:
				case soci::dt_blob:
				case soci::dt_string:
					lcValue = poRow.get<string>(liIndex);
					break;

				case soci::dt_date:
					char loTimes[32];
					strftime(loTimes, sizeof(loTimes), "%F %T", &poRow.get<tm>(liIndex));
					lcValue = loTimes;
					break;

				case soci::dt_double:
					lcValue = to_string(poRow.get<double>(liIndex));
					break;

				case soci::dt_integer:
					lcValue = to_string(poRow.get<int>(liIndex));
					break;

				case soci::dt_long_long:
					lcValue = to_string(poRow.get<long long>(liIndex));
					break;

				case soci::dt_unsigned_long_long:
					lcValue = to_string(poRow.get<unsigned long long>(liIndex));
					break;
				}

				loCell = new GCell(lcValue);
				loRow->Add(loCell);
			}
		}

		return loRow;
	}
}