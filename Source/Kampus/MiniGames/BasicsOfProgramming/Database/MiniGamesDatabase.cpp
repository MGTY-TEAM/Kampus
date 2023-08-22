#include "MiniGamesDatabase.h"

#include "Paths.h"
DEFINE_LOG_CATEGORY(LogDatabase)

MiniGamesDatabase::MiniGamesDatabase(FString Path, ESQLiteDatabaseOpenMode OpenMode)
{
	

	Database = new FSQLiteDatabase();
	if (!Database->Open(*Path, OpenMode) || !Database->IsValid())
	{
		UE_LOG(LogDatabase, Warning, TEXT("Failed to open database: %s"), *Database->GetLastError());
	}
	else
	{
		const TCHAR* SaveQuery = TEXT(
			"INSERT INTO MapItem (MapID, CellX, CellY, CellType) values ($MapID, $CellX, $CellY, $CellType)");
		SaveStatement.Create(*Database, SaveQuery, ESQLitePreparedStatementFlags::Persistent);
		const TCHAR* LoadQuery = TEXT("SELECT * from MapItem where MapID = $id");
		LoadStatement.Create(*Database, LoadQuery, ESQLitePreparedStatementFlags::Persistent);
		
	}


	// ? (index)            e.g. select * from people where name = '?'
	// ?integer (index)     e.g. select * from people where name = '?3'
	// :alphanumeric (name) e.g. select * from people where name = ':name'
	// @alphanumeric (name) e.g. select * from people where name = '@name'
	// $alphanumeric (name) e.g. select * from people where name = '@name'
}

MiniGamesDatabase::~MiniGamesDatabase()
{
	SaveStatement.Destroy();
	LoadStatement.Destroy();

	
	if (!Database->Close())
	{
		UE_LOG(LogDatabase, Warning, TEXT("Failed to close database: %s"), *Database->GetLastError());
	}
	else
	{
		delete Database;
	}
}

bool MiniGamesDatabase::SaveMap(int32 MapId, TArray<TArray<int32>> Map)
{
	for (int32 i = 0; i < Map.Num(); i++)
	{
		for (int32 j = 0; j < Map[i].Num(); j++)

			if (Database->IsValid() && SaveStatement.IsValid())
			{
				SaveStatement.Reset();

				bool bBindingSuccess = true;
				bBindingSuccess = bBindingSuccess && SaveStatement.SetBindingValueByName(TEXT("$MapID"), MapId);
				bBindingSuccess = bBindingSuccess && SaveStatement.SetBindingValueByName(TEXT("$CellX"), i);
				bBindingSuccess = bBindingSuccess && SaveStatement.SetBindingValueByName(TEXT("$CellY"), j);
				bBindingSuccess = bBindingSuccess && SaveStatement.SetBindingValueByName(TEXT("$CellType"), Map[i][j]);

				if (!bBindingSuccess || !SaveStatement.Execute())
				{
					return false;
				}
			}
	}
	return true;
}

TArray<TArray<int32>> MiniGamesDatabase::LoadMap(int32 MapId)
{
	TArray<TArray<int32>> Map;
	
	if (Database->IsValid() && LoadStatement.IsValid())
	{
		LoadStatement.Reset();
 
		if (LoadStatement.SetBindingValueByName(TEXT("$id"), PlayerId) && LoadStatement.Execute() && LoadStatement.Step() == ESQLitePreparedStatementStepResult::Row)
		{
			LoadStatement.GetColumnValueByIndex(TEXT(""))
			LoadStatement.GetColumnValueByName(TEXT("y"), Position.Y);
			LoadStatement.GetColumnValueByName(TEXT("z"), Position.Z);
		}
	}
	return Map;
}
