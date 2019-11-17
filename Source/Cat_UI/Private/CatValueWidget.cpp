// Noe Perard-Gayot <noe.perard@gmail.com> 2019 - All Rights Reserved

#include "CatValueWidget.h"
#include "Cat_UIPCH.h"


void UCatValueWidget::SetValueAsFloat(float in)
{
	ValueText = FText::AsNumber(in);
	if (WValueText)
		WValueText->SetText(ValueText);
}

void UCatValueWidget::SetValueAsText(FText in)
{
	ValueText = in;
	if (WValueText)
		WValueText->SetText(ValueText);
}

void UCatValueWidget::SetValueAsCurrency(int32 in)
{
	ValueText = FText::AsCurrency(in);
	if (WValueText)
		WValueText->SetText(ValueText);
}
