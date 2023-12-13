
#include "STD_types.h"
#include "BIT_MATH.h"
#include "GIE_int.h"
#include "GIE_private.h"

void GIE_voidEnable(void)
{
	SET_BIT(SREG , 7);
}
void GIE_voidDisable(void)
{
	CLEAR_BIT(SREG , 7);
}