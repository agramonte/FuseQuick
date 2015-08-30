#include "FuseSDK.h"
#include "QFuse.h"
#include "QLuaHelpers.h"

QUICK_NAMESPACE_BEGIN;

int32 GotSessionReceived(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("fuseAds");
    LUA_EVENT_SET_STRING("type", "SessionReceived");
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);
	
    return 0;
}

int32 AdAvailableResponse(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("fuseAds");
    LUA_EVENT_SET_STRING("type", "AdAvailableResponse");
    
    struct paramList
	{
		int available;
		int error;
	};
    
	const paramList* params = (paramList*)systemData;

	// display status update for ad (see main loop)
    
    LUA_EVENT_SET_INTEGER("available", params->available);
    LUA_EVENT_SET_INTEGER("error", params->error);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

	return 0;
}

int32 AdWasClosed(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("fuseAds");
    LUA_EVENT_SET_STRING("type", "AdWasClosed");
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);
    
	return 0;
}

int32 RewardedAdCompleted(void* systemData, void* userData)
{
    struct paramList
    {
        const char* preMessage;
        const char* rewardMessage;
        const char* rewardItem;
        int rewardAmount;
    };
    const paramList* params = (paramList*)systemData;
    
    LUA_EVENT_PREPARE("fuseAds");
    LUA_EVENT_SET_STRING("type", "RewardedAdCompleted");

    LUA_EVENT_SET_STRING("preMessage",params->preMessage);
    LUA_EVENT_SET_STRING("rewardMessage", params->rewardMessage);
    LUA_EVENT_SET_STRING("rewardItem", params->rewardItem);
    LUA_EVENT_SET_INTEGER("rewardAmount", params->rewardAmount);
    
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 IAPOfferAccepted(void* systemData, void* userData)
{
    LUA_EVENT_PREPARE("fuseAds");
    LUA_EVENT_SET_STRING("type", "IAPOfferAccepted");

    struct paramList
    {
        float productPrice;
        int itemAmount;
        const char* itemName;
        const char* productID;
    };
    const paramList* params = (paramList*)systemData;
    LUA_EVENT_SET_INTEGER("itemAmount", params->itemAmount);
    LUA_EVENT_SET_STRING("itemName", params->itemName);
    LUA_EVENT_SET_STRING("productID", params->productID);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);

    return 0;
}

int32 VGOfferAccepted(void* systemData, void* userData)
{
    struct paramList
    {
        const char* purchaseCurrency;
        float purchasePrice;
        const char* itemName;
        int itemAmount;
    };
    const paramList* params = (paramList*)systemData;

    LUA_EVENT_PREPARE("fuseAds");
    LUA_EVENT_SET_STRING("type", "VGOfferAccepted");

    LUA_EVENT_SET_STRING("itemName", params->itemName);
    LUA_EVENT_SET_INTEGER("itemAmount", params->itemAmount);
    LUA_EVENT_SEND();
    lua_pop(g_L, 1);
    
    return 0;
}




//------------------------------------------------------------------------------
// QFuse
//------------------------------------------------------------------------------
QFuse::QFuse(){
    FuseSDKRegister(FUSESDK_SESSION_STARTED, &GotSessionReceived, NULL);
    FuseSDKRegister(FUSESDK_AD_AVAILABILITY_RESPONSE, &AdAvailableResponse, NULL);
    FuseSDKRegister(FUSESDK_AD_WILL_CLOSE, &AdWasClosed, NULL);
    FuseSDKRegister(FUSESDK_REWARDED_AD_COMPLETED, &RewardedAdCompleted, NULL);
    FuseSDKRegister(FUSESDK_IAPOFFER_ACCEPTED, &IAPOfferAccepted, NULL);
    FuseSDKRegister(FUSESDK_VIRTUALGOODSOFFER_ACCEPTED, &VGOfferAccepted, NULL);
}

//------------------------------------------------------------------------------
QFuse::~QFuse(){
    FuseSDKUnRegister(FUSESDK_SESSION_STARTED, &GotSessionReceived);
    FuseSDKUnRegister(FUSESDK_AD_AVAILABILITY_RESPONSE, &AdAvailableResponse);
    FuseSDKUnRegister(FUSESDK_AD_WILL_CLOSE, &AdWasClosed);
    FuseSDKUnRegister(FUSESDK_REWARDED_AD_COMPLETED, &RewardedAdCompleted);
    FuseSDKUnRegister(FUSESDK_IAPOFFER_ACCEPTED, &IAPOfferAccepted);
    FuseSDKUnRegister(FUSESDK_VIRTUALGOODSOFFER_ACCEPTED, &VGOfferAccepted);
}

//------------------------------------------------------------------------------
bool QFuse::isAvailable(){
    return FuseSDKAvailable();
}

//------------------------------------------------------------------------------
void QFuse::init(const char* apiKey){
    FuseSDKStartSession(apiKey, NULL);
}

//------------------------------------------------------------------------------
void QFuse::show(const char* zone){
    FuseSDKShowAdForZoneID(zone, NULL);
}

//------------------------------------------------------------------------------
bool QFuse::checkLoaded(const char* zone){
    return FuseSDKIsAdAvailableForZoneID(zone);
    
    
}

//------------------------------------------------------------------------------
void QFuse::load(const char* zone){
    FuseSDKPreloadAdForZoneID(zone);
}

//------------------------------------------------------------------------------
void QFuse::registerPushNotification(const char* projectId){
    FuseSDKRegisterForPushNotifications(projectId);
}

QUICK_NAMESPACE_END;
