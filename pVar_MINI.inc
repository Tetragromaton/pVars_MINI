/*
**
*/
#if defined _PVMINI_included
 #endinput
#endif
#define _PVMINI_included

StringMap GLOBAL;
bool Created = false;
PVM_StartWorker()
{
	if(Created == false)
	{
		if(GLOBAL == INVALID_HANDLE)
		{
			GLOBAL = CreateTrie();
			Created = true;
		}
	}	
}
int PVM_GetInt(const char[] sid, const char[] varx, int client = -1)
{
	PVM_StartWorker();
	char SID_Post[255];
	if(client > 0)
	{
		GetClientAuthId(client, AuthId_Steam2, SID_Post, sizeof(SID_Post));
	}else strcopy(SID_Post, sizeof(SID_Post), sid);
	char BATCH_STRIX[1024];
	Format(BATCH_STRIX, sizeof(BATCH_STRIX), "%s_%s", SID_Post, varx);
	int resultf = 0;
	//PrintToChatAll("Get:%s", BATCH_STRIX);
	GetTrieValue(GLOBAL, BATCH_STRIX, resultf);
	return resultf;
}
bool PVM_SetInt(const char[] sid, const char[] varx, int value,int client = -1)
{
	PVM_StartWorker();
	char SID_Post[255];
	if(client > 0)
	{
		GetClientAuthId(client, AuthId_Steam2, SID_Post, sizeof(SID_Post));
	}else  strcopy(SID_Post, sizeof(SID_Post), sid);
	char BATCH_STRIX[1024];
	Format(BATCH_STRIX, sizeof(BATCH_STRIX), "%s_%s", SID_Post, varx);
	//PrintToChatAll("Set DEBUG RESULT:%s", BATCH_STRIX);
	SetTrieValue(GLOBAL, BATCH_STRIX, value);
	return true;
}
