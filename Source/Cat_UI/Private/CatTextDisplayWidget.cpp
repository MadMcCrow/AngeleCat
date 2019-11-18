// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "CatTextDisplayWidget.h"
#include "Cat_UIPCH.h"


void UCatTextDisplayWidget::NativeConstruct()
{
    Super::NativeConstruct();
    SetText(DisplayText);
}

void UCatTextDisplayWidget::SetText(const FText &inText)
{
    if(WDisplayText)
        WDisplayText->SetText(inText);
    DisplayText = inText;   
}