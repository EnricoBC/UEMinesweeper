#include "MinesweeperGame.h"
#include "MinesweeperGameStyle.h"
#include "MinesweeperGameCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Widgets/SMinesweeperWidget.h"
#include "ToolMenus.h"

static const FName MinesweeperGameTabName("Minesweeper");

#define LOCTEXT_NAMESPACE "FMinesweeperGameModule"

void FMinesweeperGameModule::StartupModule()
{
	FMinesweeperGameStyle::Initialize();
	FMinesweeperGameStyle::ReloadTextures();

	FMinesweeperGameCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FMinesweeperGameCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FMinesweeperGameModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FMinesweeperGameModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(MinesweeperGameTabName, FOnSpawnTab::CreateRaw(this, &FMinesweeperGameModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FMinesweeperGameTabTitle", "Minesweeper"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FMinesweeperGameModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FMinesweeperGameStyle::Shutdown();

	FMinesweeperGameCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(MinesweeperGameTabName);
}

TSharedRef<SDockTab> FMinesweeperGameModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	// Always create new window to ensure clean UI.
	MinesweeperWindow = MakeShareable(new FMinesweeperWindow);
	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			MinesweeperWindow->GetWidget()
		];
}

void FMinesweeperGameModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(MinesweeperGameTabName);
}

void FMinesweeperGameModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
	{
		FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
		Section.AddMenuEntryWithCommandList(FMinesweeperGameCommands::Get().OpenPluginWindow, PluginCommands);
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMinesweeperGameModule, MinesweeperGame)