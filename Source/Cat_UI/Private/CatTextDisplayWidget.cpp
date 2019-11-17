// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "CatTextDisplayWidget.h"


void UCatTextDisplayWidget::OnWidgetRebuilt()
{
    Super::OnWidgetRebuilt();
    SetText(DisplayText);
}

void UCatTextDisplayWidget::SetText(const FText &inText)
{
    if(WDisplayText)
        WDisplayText->SetText(inText);
    DisplayText = inText;   
}