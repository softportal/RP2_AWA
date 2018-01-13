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
	AwaClientSetOperation_CreateObjectInstance(operation, "/1000/0");
	AwaClientSetOperation_CreateOptionalResource(operation, "/1000/0/101");
	AwaClientSetOperation_AddValueAsCString(operation, "/1000/0/101", "HotAir Systems Inc");
    AwaClientSetOperation_CreateOptionalResource(operation, "/1000/0/104");
	AwaClientSetOperation_Perform(operation, OPERATION_PERFORM_TIMEOUT);
	AwaClientSetOperation_Free(&operation);
}

static void process_temp(float temp)
{
    printf("has escrito %f parguelon\n", temp);
}



int main(void)
{
    float n1;
	AwaClientSession * session = AwaClientSession_New();
	AwaClientSession_Connect(session);
	DefineHeaterObject(session);
	SetInitialValues(session);

    while (true)
    {
        printf("enter temperature value ");
        scanf("%f", &n1);
        process_temp(n1);
    }


	AwaClientSession_Disconnect(session);
	AwaClientSession_Free(&session);

	return 0;
}
