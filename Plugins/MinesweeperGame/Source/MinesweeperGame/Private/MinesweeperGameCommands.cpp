#include "MinesweeperGameCommands.h"

#define LOCTEXT_NAMESPACE "FMinesweeperGameModule"

void FMinesweeperGameCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "Minesweeper", "Bring up the Minesweeper window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
