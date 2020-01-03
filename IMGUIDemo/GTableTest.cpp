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

		ImGui::InputText(u8"连接字符串", buf, IM_ARRAYSIZE(buf));
		string lcNewCon = buf;
		this->setConnection(lcNewCon);
		ImGui::SameLine();

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

		static const char* lcDefaultName = (*(this->Tables->begin())).first.c_str();
		if (ImGui::BeginCombo(u8"表格", lcDefaultName, ImGuiComboFlags_::ImGuiComboFlags_None))
		{
			for (map<string, bool>::iterator loName = this->Tables->begin(); loName != this->Tables->end(); loName++)
			{
				const char* lcTableName = (*loName).first.c_str();
				bool is_selected = (lcTableName == lcTableName);
				if (ImGui::Selectable(lcTableName, is_selected))
					lcDefaultName = lcTableName;
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}

			ImGui::EndCombo();
		}

		this->setTableName(lcDefaultName);

		ImGui::End();
	}
}