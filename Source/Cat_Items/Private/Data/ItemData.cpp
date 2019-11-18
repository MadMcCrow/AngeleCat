// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "ItemData.h"

bool UItemData::GetAllItemAssets(TArray<UItemData *> Assets, UItemData* Asset)
{
    Assets.Empty();
    auto AssetManager = UAssetManager::Get();
    if(!AssetManager)
        return false;
    if(!Asset)
        return false;
    TArray< FAssetData > AssetDataList;
    AssetManager->GetPrimaryAssetDataList(Asset->GetPrimaryAssetId().PrimaryAssetType, AssetDataList);
    for (auto itr : AssetDataList)
    {
        auto asset = Cast<UItemData>(itr.GetAsset())
        if(asset)
        Assets.Add(asset);
    }
    return Assets.IsValidIndex(0);
}