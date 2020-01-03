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
			}

			this->tableName = "";
			this->Columns->clear();
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
			this->Columns->clear();
			if (this->tableName.empty() == false)
			{
				if (this->SQL)
				{
					(this->SQL->prepare << "select C_NAME,I_NAME from T_CONNECT");
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
		this->Columns = new map<string, bool>();
		this->dbName = "oracle";
		this->connection = "service=FAST user=V45GDYH password=1 charset=utf8 ncharset=utf8";

		TableName->setContainer(this);
		TableName->setter(&GTableTest::setTableName);
		TableName->getter(&GTableTest::getTableName);

		Connection->setContainer(this);
		Connection->setter(&GTableTest::setConnection);
		Connection->getter(&GTableTest::getConnection);
	}

	void GTableTest::ShowWindow()
	{
		ImGui::Begin(u8"数据库与Valkan联合测试");

		const char* loDBs[] = { "oracle", "sqlite3" };
		static const char* item_current = loDBs[0];
		if (ImGui::BeginCombo(u8"数据库", item_current, ImGuiComboFlags_::ImGuiComboFlags_None))
		{
			for (int liIndex = 0; liIndex < IM_ARRAYSIZE(loDBs); liIndex++)
			{
				bool is_selected = (item_current == loDBs[liIndex]);
				if (ImGui::Selectable(loDBs[liIndex], is_selected))
					item_current = loDBs[liIndex];
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}

			ImGui::EndCombo();
		}

		ImGui::SameLine();

		char buf[200];
		this->connection._Copy_s(buf, this->connection.size(), 0);
		ImGui::InputText("连接字符串：", buf, IM_ARRAYSIZE(buf));
		this->connection = buf;

		ImGui::End();
	}
}