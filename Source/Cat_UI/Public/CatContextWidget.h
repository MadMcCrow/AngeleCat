// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CatUserWidget.h"
#include "UCatContextWidget.generated.h"

/// @brief UCatUserWidget		base class for user widget
UCLASS(ClassGroup=(UI))
class CAT_UI_API UCatContextWidget : public UCatUserWidget
{
	GENERATED_BODY()
public:

    UPROPERTY(meta = (BindWidget), BlueprintReadWrite, Category= "widget")
    UTextBlock WTitle;


};
