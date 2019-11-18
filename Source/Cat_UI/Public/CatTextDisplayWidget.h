// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CatUserWidget.h"
#include "Components/Button.h"
#include "CatTextDisplayWidget.generated.h"

class UTextBlock;


/// @brief UCatUserWidget		base class for user widget
UCLASS(ClassGroup=(UI))
class CAT_UI_API UCatTextDisplayWidget : public UCatUserWidget
{
	GENERATED_BODY()

public :

virtual void NativeConstruct() override;

protected:

    UPROPERTY(meta = (BindWidget),VisibleAnywhere, BlueprintReadOnly, Category= "Widget")
    UTextBlock * WDisplayText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text", meta= (BlueprintSetter = "SetText"))
    FText DisplayText;

public:

    UFUNCTION(BlueprintSetter, BlueprintCallable, Category = Text)
    virtual void SetText(const FText &inText);


};
