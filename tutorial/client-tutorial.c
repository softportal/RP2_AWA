#include <stdlib.h>
#include <stdio.h>
#include <awa/common.h>
#include <awa/client.h>
#define OPERATION_PERFORM_TIMEOUT 1000

static void DefineHeaterObject(AwaClientSession * session)
{
	AwaObjectDefinition * objectDefinition = AwaObjectDefinition_New(1000, "Heater", 0, 1);
	AwaObjectDefinition_AddResourceDefinitionAsString(objectDefinition, 101, " Manufacturer", false, AwaResourceOperations_ReadWrite, NULL);
    AwaObjectDefinition_AddResourceDefinitionAsFloat(objectDefinition,  104, "Temperature", false, AwaResourceOperations_ReadWrite, 0.0);
	AwaClientDefineOperation * operation = AwaClientDefineOperation_New(session);
	AwaClientDefineOperation_Add(operation, objectDefinition);
	AwaClientDefineOperation_Perform(operation, OPERATION_PERFORM_TIMEOUT);
	AwaClientDefineOperation_Free(&operation);
}
static void SetInitialValues(AwaClientSession * session)
{
	AwaClientSetOperation * operation = AwaClientSetOperation_New(session);
    //instance
	AwaClientSetOperation_CreateObjectInstance(operation, "/1000/0");

    //manufacturer instance
	AwaClientSetOperation_CreateOptionalResource(operation, "/1000/0/101");
	AwaClientSetOperation_AddValueAsCString(operation, "/1000/0/101", "HotAir Systems Inc");

    //temperature instance
    AwaClientSetOperation_CreateOptionalResource(operation, "/1000/0/104");
    AwaClientSetOperation_AddValueAsFloat (operation, "/1000/0/104", 19.013);

	AwaClientSetOperation_Perform(operation, OPERATION_PERFORM_TIMEOUT);
    //perform op
	AwaClientSetOperation_Free(&operation);
}

static void process_temp(AwaFloat temp, AwaClientSession * session)
{

	AwaClientSetOperation * operation = AwaClientSetOperation_New(session);
    int result;
    printf("set %20lf temp \n", temp);

	if (AwaClientSetOperation_AddValueAsFloat(operation, "/1000/0/104", temp) != AwaError_Success)
	{
		result = -1;
	}

	AwaClientSetOperation_Perform(operation, OPERATION_PERFORM_TIMEOUT);

	AwaClientSetOperation_Free(&operation);

}



int main(void)
{
    AwaFloat n1;
	AwaFloat tmp = 0.0;
	AwaClientSession * session = AwaClientSession_New();
	AwaClientSession_Connect(session);
	DefineHeaterObject(session);


	SetInitialValues(session);

    while (true)
    {


        printf("enter temperature value ");
        scanf("%20lf", &tmp);
        process_temp(tmp, session);
    }


	AwaClientSession_Disconnect(session);
	AwaClientSession_Free(&session);

	return 0;
}
