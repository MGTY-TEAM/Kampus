#pragma once

#include "SQLiteDatabase.h"

DECLARE_LOG_CATEGORY_EXTERN(LogDatabase, Log, All);

class MiniGamesDatabase
{
public:
	MiniGamesDatabase(FString Path,ESQLiteDatabaseOpenMode OpenMode);
	~MiniGamesDatabase();

	bool SaveMap(int32 MapId, TArray<TArray<int32>> Map);
	TArray<TArray<int32>> LoadMap(int32 MapId);

private:
	FSQLiteDatabase* Database;

	FSQLitePreparedStatement SaveStatement;
	FSQLitePreparedStatement LoadStatement;
};
