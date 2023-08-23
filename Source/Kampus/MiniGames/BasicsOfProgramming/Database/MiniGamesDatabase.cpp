#include "MiniGamesDatabase.h"

#include "K2Node_DoOnceMultiInput.h"
#include "Paths.h"
DEFINE_LOG_CATEGORY(LogDatabase)

MiniGamesDatabase::MiniGamesDatabase(FString Path, ESQLiteDatabaseOpenMode OpenMode)
{

	Database = new FSQLiteDatabase();
	if (!Database->Open(*Path, OpenMode) || !Database->IsValid())
	{
		UE_LOG(LogDatabase, Error, TEXT("Failed to open database: %s"), *Database->GetLastError());
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
	TArray<int32> CellXs;
	TArray<int32> CellYs;
	TArray<int32> CellTypes;
	if (Database->IsValid() && LoadStatement.IsValid())
	{
		LoadStatement.Reset();

		if (LoadStatement.SetBindingValueByName(TEXT("$id"), MapId) && LoadStatement.Execute())
		{
			while (LoadStatement.Step() == ESQLitePreparedStatementStepResult::Row)
			{
				int32 CellX;
				int32 CellY;
				int32 CellType;
				LoadStatement.GetColumnValueByName(TEXT("CellX"), CellX);
				LoadStatement.GetColumnValueByName(TEXT("CellY"), CellY);
				LoadStatement.GetColumnValueByName(TEXT("CellType"), CellType);
				CellXs.Add(CellX);
				CellYs.Add(CellY);
				CellTypes.Add(CellType);
			}
		}
	}
	int32 SquareSize = FMath::Sqrt(CellXs.Num());


	TArray<TArray<int32>> Map;

	int32 MapSizeX = SquareSize;
	int32 MapSizeY = SquareSize;

	Map.Init(TArray<int32>(), MapSizeX);

	for (int32 X = 0; X < MapSizeX; ++X)
	{
		Map[X].Init(0, MapSizeY);
	}

	if (CellXs.Num() != 0 && CellYs.Num() != 0 && CellTypes.Num() != 0)
	{
		for (int i = 0; i < CellXs.Num(); i++)
		{
			Map[CellXs[i]][CellYs[i]] = CellTypes[i];
		}
	}
	return Map;
}
