#include <base.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include "ipp_util.h"
#include"SelfDeviceInfo.h"
#include"ipp_defines.h"
#include "ipp_stub_def.h"

SelfDeviceInfo g_SelfDeviceInfo;

void setSelfDeviceIsOnline(BOOL isonline) {
	g_SelfDeviceInfo.IsOnline = isonline;
}
BOOL geSelfDevicetIsOnline() {
	return g_SelfDeviceInfo.IsOnline;
}

void setSelfDeviceType(int type) {
	g_SelfDeviceInfo.Type = type;
}
int getSelfDeviceType() {
	return g_SelfDeviceInfo.Type;
}

void setSelfDeviceDeviceId(int deviceid) {
	g_SelfDeviceInfo.DeviceId = deviceid;
}
int getSelfDeviceDeviceId() {
	return g_SelfDeviceInfo.DeviceId;
}

void setSelfDeviceConnectType(int connecttpye) {
	g_SelfDeviceInfo.ConnectType = connecttpye;
}
int getSelfDeviceConnectType() {
	return g_SelfDeviceInfo.ConnectType;
}

void setSelfDeviceModel(const char* model) {
	if (strlen(model)>25)
	{
		ipp_LogE("%s error: over flow\n",__FUNCTION__);
		return;
	}
	memset(g_SelfDeviceInfo.Model, '\0', sizeof(g_SelfDeviceInfo.Model));
	strcpy(g_SelfDeviceInfo.Model, model);
	ipp_LogE("%s: Model = %s\n", __FUNCTION__,g_SelfDeviceInfo.Model);
}
const char *getSelfDeviceModel() {
	return g_SelfDeviceInfo.Model;
}

void setSelfDeviceName(const char* name) {
	memset(g_SelfDeviceInfo.Name, '\0', sizeof(g_SelfDeviceInfo.Name));
	if (strlen(name)>25)
	{
		ipp_LogE("%s error: over flow\n",__FUNCTION__);
		return;
	}
	strcpy(g_SelfDeviceInfo.Name, name);
	ipp_LogV("%s: Name = %s\n",__FUNCTION__, g_SelfDeviceInfo.Name);
}
const char * getSelfDeviceName() {
	return g_SelfDeviceInfo.Name;
}

void setSelfDeviceFactory(const char* factory) {
	memset(g_SelfDeviceInfo.Factory, '\0', sizeof(g_SelfDeviceInfo.Factory));
	if (strlen(factory)>INFO_SIZE)
	{
		ipp_LogE("%s  error: over flow\n",__FUNCTION__);
		return;
	}
	strcpy(g_SelfDeviceInfo.Factory, factory);
	ipp_LogV("%s: Factory = %s\n",__FUNCTION__, g_SelfDeviceInfo.Factory);
}
const char *getSelfDeviceFactory() {
	return g_SelfDeviceInfo.Factory;
}

void setSelfDeviceSoftwareVersion(const char* softwareversion) {
	memset(g_SelfDeviceInfo.SoftwareVersion, '\0', sizeof(g_SelfDeviceInfo.SoftwareVersion));
	if (strlen(softwareversion)>30)
	{
		ipp_LogE("%s  error: over flow\n",__FUNCTION__);
		return;
	}
	strcpy(g_SelfDeviceInfo.SoftwareVersion, softwareversion);
	ipp_LogV("%s: SoftwareVersion = %s\n",__FUNCTION__, g_SelfDeviceInfo.SoftwareVersion);
}
const char *getSelfDeviceSoftwareVersion() {
	return g_SelfDeviceInfo.SoftwareVersion;
}

void setSelfDeviceLocation(const char * location) {
	memset(g_SelfDeviceInfo.Location, '\0', sizeof(g_SelfDeviceInfo.Location));
	if (strlen(location)>25)
	{
		ipp_LogE("%s  error: over flow\n",__FUNCTION__);
		return;
	}
	strcpy(g_SelfDeviceInfo.Location, location);
	ipp_LogV("%s: Location = %s\n",__FUNCTION__, g_SelfDeviceInfo.Location);
}
const char *getSelfDeviceLocation() {
	return g_SelfDeviceInfo.Location;
}

void setSelfDeviceSN(const char * sn) {
	
	if (strlen(sn)>INFO_SIZE)
	{
		ipp_LogE("%s  error: over flow\n",__FUNCTION__);
		return;
	}
	memset(g_SelfDeviceInfo.SN, '\0', sizeof(g_SelfDeviceInfo.SN));
	strcpy(g_SelfDeviceInfo.SN, sn);
	ipp_LogV("%s: SN = %s\n", __FUNCTION__,g_SelfDeviceInfo.SN);
}
const char *getSelfDeviceSN() {
	return g_SelfDeviceInfo.SN;
}
void setSelfDeviceFlag(const char * flag) {
	memset(g_SelfDeviceInfo.flag, '\0', sizeof(g_SelfDeviceInfo.flag));
	if (strlen(flag)>20)
	{
		ipp_LogE("%s  error: over flow\n",__FUNCTION__);
		return;
	}
	strcpy(g_SelfDeviceInfo.flag, flag);
	ipp_LogV("%s: flag = %s\n", __FUNCTION__,g_SelfDeviceInfo.flag);
}
const char *getSelfDeviceFlag() {
	return g_SelfDeviceInfo.flag;
}
void setSelfDeviceRole(const char * role) {
	memset(g_SelfDeviceInfo.role, '\0', sizeof(g_SelfDeviceInfo.role));
	if (strlen(role)>20)
	{
		ipp_LogE("%s  error: over flow\n",__FUNCTION__);
		return;
	}
	strcpy(g_SelfDeviceInfo.role, role);
	ipp_LogV("%s: role = %s\n", __FUNCTION__,g_SelfDeviceInfo.role);
}
const char *getSelfDeviceRole() {

	return g_SelfDeviceInfo.role;
}
void setSelfDeviceIP(const char * ip) {
	if (strlen(ip)>INFO_SIZE)
	{
		ipp_LogE("%s  error: over flow\n",__FUNCTION__);
		return;
	}
	memset(g_SelfDeviceInfo.IP, '\0', sizeof(g_SelfDeviceInfo.IP));
	strcpy(g_SelfDeviceInfo.IP, ip);
	ipp_LogV("%s: IP = %s\n", __FUNCTION__,g_SelfDeviceInfo.IP);
}
const char *getSelfDeviceIP(){
	return g_SelfDeviceInfo.IP;
}

void setSelfDeviceMac(const char* mac) {
	memset(g_SelfDeviceInfo.MAC, '\0', sizeof(g_SelfDeviceInfo.MAC));
	if (strlen(mac)>30)
	{
		ipp_LogE("%s  error: over flow\n",__FUNCTION__);
		return;
	}
	strcpy(g_SelfDeviceInfo.MAC, mac);
	ipp_LogV("%s: MAC = %s\n", __FUNCTION__,g_SelfDeviceInfo.MAC);
}
const char * getSelfDeviceMac() {
	return g_SelfDeviceInfo.MAC;
}
void setSelfDeviceUserid(const char* userid) {
	memset(g_SelfDeviceInfo.UserID, '\0', sizeof(g_SelfDeviceInfo.UserID));
	if (strlen(userid)>INFO_SIZE)
	{
		ipp_LogE("%s  error: over flow\n",__FUNCTION__);
		return;
	}
	strcpy(g_SelfDeviceInfo.UserID, userid);
	ipp_LogV("%s: UserID = %s\n", __FUNCTION__,g_SelfDeviceInfo.UserID);
}
const char * getSelfDeviceUserid() {
	return g_SelfDeviceInfo.UserID;
}
void setSelfDeviceVCode(const char* vcode) {
	memset(g_SelfDeviceInfo.VCode, '\0', sizeof(g_SelfDeviceInfo.VCode));
	if (strlen(vcode)>20)
	{
		ipp_LogE("%s  error: over flow\n",__FUNCTION__);
		return;
	}
	strcpy(g_SelfDeviceInfo.VCode, vcode);
	ipp_LogV("%s: VCode = %s\n", __FUNCTION__,g_SelfDeviceInfo.VCode);
}
const char * getSelfDeviceVCode() {
	return g_SelfDeviceInfo.VCode;
}
void setSelfDeviceProductID(const char* productid) {
	memset(g_SelfDeviceInfo.ProductID, '\0', sizeof(g_SelfDeviceInfo.ProductID));
	if (strlen(productid)>30)
	{
		ipp_LogE("%s  error: over flow\n",__FUNCTION__);
		return;
	}
	strcpy(g_SelfDeviceInfo.ProductID, productid);
	ipp_LogV("%s: ProductID = %s\n", __FUNCTION__,g_SelfDeviceInfo.ProductID);
}
const char * getSelfDeviceProductID() {
	return g_SelfDeviceInfo.ProductID;
}



void InitDevInfo() {
	setSelfDeviceFlag("");
	setSelfDeviceIP("");
	setSelfDeviceRole("slave");
	setSelfDeviceSN("");
	setSelfDeviceIsOnline(TRUE);
	setSelfDeviceType(0xfb24);
	setSelfDeviceDeviceId(0);
	setSelfDeviceConnectType(0);
	setSelfDeviceModel("");
	setSelfDeviceName("");
	setSelfDeviceFactory("");
	setSelfDeviceSoftwareVersion("0.0.1");
	setSelfDeviceLocation("");
	setSelfDeviceMac("FF-YY-CC");
	setSelfDeviceVCode("");
	setSelfDeviceProductID("SB24_0");
	g_SelfDeviceInfo.FunctionCode[0] = 0;
	g_SelfDeviceInfo.FunctionCode[1] = 0;
	g_SelfDeviceInfo.FunctionCode[2] = 0;
	g_SelfDeviceInfo.FunctionCode[3] = 0;


	ipp_LogI("g_SelfDeviceInfo.SN = %s\n", g_SelfDeviceInfo.SN);
	ipp_LogI("g_SelfDeviceInfo.flag = %s\n", g_SelfDeviceInfo.flag);
	ipp_LogI("g_SelfDeviceInfo.IP = %s\n", g_SelfDeviceInfo.IP);
	ipp_LogI("g_SelfDeviceInfo.role = %s\n", g_SelfDeviceInfo.role);
	
}
