#pragma once
#ifndef GRIDREF_DEF
#define GRIDREF_DEF
#include <GTable.h>
#include <GRow.h>
#include <GColumn.h>
#include <GCell.h>
#endif // !GRIDREF_DEF

#ifndef SOCI_DEF
#define SOCI_DEF
#include <soci/soci.h>
#include <soci/sqlite3/soci-sqlite3.h>
#include <soci/oracle/soci-oracle.h>
#include <private/soci-compiler.h>

#if defined(_MSC_VER) && (_MSC_VER < 1500)
#undef SECTION
#define SECTION(name) INTERNAL_CATCH_SECTION(name, "dummy-for-vc8")
#endif SECTION

#endif // !SOCI_DEF

#include <map>

using namespace Grid;
using namespace soci;
namespace Test
{
	class GTableTest
	{
	private:
		GTable* _Table;
		string dbName;
		string connection;
		string tableName;
		session* SQL;
		map<string, bool>* Tables;

		void setConnection(string pcConnection);
		string getConnection() const;

		void setTableName(string pcTableName);
		string getTableName() const;

		void Initial();
	public:
		GTableTest();
		~GTableTest();
		property<GTableTest, string, READ_WRITE>* Connection;
		property<GTableTest, string, READ_WRITE>* TableName;
		void ShowWindow();
	};

}


