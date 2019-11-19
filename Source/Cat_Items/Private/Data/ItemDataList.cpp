// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "ItemDataList.h"
#include "Kismet/KismetSystemLibrary.h"


UItemData * UItemDataList::LoadItemFromSoftPtr_Blocking(TSoftObjectPtr<UItemDataList> list, int32 idx)
{
    auto asset = Cast<UItemDataList>(UKismetSystemLibrary::LoadAsset_Blocking(list));
    if(asset)
        return asset->LoadItem_Blocking(idx);
    return nullptr;
}

TArray<UItemData *> UItemDataList::LoadAllItemsFromSoftPtr_Blocking(TSoftObjectPtr<UItemDataList> list)
{
    auto asset = Cast<UItemDataList>(UKismetSystemLibrary::LoadAsset_Blocking(list));
    if(asset)
        return asset->LoadAllItems_Blocking();
    return TArray<UItemData *>();
}

UItemData * UItemDataList::LoadItem_Blocking(int32 idx)
{
    if(Data.IsValidIndex(idx))
        return Cast<UItemData>(UKismetSystemLibrary::LoadAsset_Blocking(Data[idx]));
    return nullptr;     
}

TArray<UItemData *> UItemDataList::LoadAllItems_Blocking()
{
    TArray<UItemData *> retval;
    for(auto it : Data)
    {
        const auto item = Cast<UItemData>(UKismetSystemLibrary::LoadAsset_Blocking(it));
        if(item)
            retval.Add(item);
    }
    return retval;
}