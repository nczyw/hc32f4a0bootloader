#include "main.h"
int32_t main(void){
	SysCLK_Init();
	while(1){
		DDL_DelayMS(20);
	}
}
