// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "ItemData.h"
#include "Engine/AssetManager.h"
#include "Kismet/KismetSystemLibrary.h"

bool UItemData::GetAllItemAssetsByClass(TArray<UItemData *> &Assets, UItemData* Asset)
{
    Assets.Empty();
    UAssetManager * manager = UAssetManager::GetIfValid();
    if(!manager)
        return false;
    if(!Asset)
        return false;
    TArray< FAssetData > AssetDataList;
    const auto type = Asset->GetPrimaryAssetId().PrimaryAssetType;
    manager->GetPrimaryAssetDataList(type, AssetDataList);
    for (auto itr : AssetDataList)
    {
        UItemData* asset = Cast<UItemData>(itr.GetAsset());
        if (asset)
        {
            Assets.Add(asset);
        }
    }
    return Assets.IsValidIndex(0);
}


bool UItemData::GetAllItemAssets(TArray<UItemData *> &Assets)
{
    Assets.Empty();
    UAssetManager * manager = UAssetManager::GetIfValid();
    if(!manager)
        return false;
    TArray< FAssetData > AssetDataList;
    const auto type = UKismetSystemLibrary::GetPrimaryAssetIdFromObject(UItemData::StaticClass()->GetDefaultObject()).PrimaryAssetType;
    manager->GetPrimaryAssetDataList(type, AssetDataList);
    for (auto itr : AssetDataList)
    {
        UItemData* asset = Cast<UItemData>(itr.GetAsset());
        if (asset)
        {
            Assets.Add(asset);
        }
    }
    return Assets.IsValidIndex(0);
}