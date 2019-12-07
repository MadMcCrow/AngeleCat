// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#pragma once

#include "CatTextDisplayWidget.h"
#include "CatValueWidget.generated.h"

class UTextBlock;

/// @brief UCatUserWidget		base class for user widget
UCLASS(ClassGroup=(UI))
class CAT_UI_API UCatValueWidget : public UCatTextDisplayWidget
{
	GENERATED_BODY()

protected:

    UPROPERTY(meta = (BindWidget),VisibleAnywhere, BlueprintReadOnly, Category= "Widget")
	UTextBlock * WValueText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Text", meta = (BlueprintSetter = "SetValueAsText"))
	FText ValueText;

public:

	UFUNCTION(BlueprintCallable, Category = "Value")
	void SetValueAsFloat(float in);

	UFUNCTION(BlueprintCallable, BlueprintSetter, Category = "Value")
	void SetValueAsText(FText in);

	UFUNCTION(BlueprintCallable, Category = "Value")
	void SetValueAsCurrency(int32 in);

};
