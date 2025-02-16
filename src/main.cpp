/*
Internetradio mit Nextion Display und ESP32.

 */
#include "Nextion.h"
#include "NexButton.h"
#include <WiFiManager.h>
#include "Arduino.h"
#include "AudioTools.h"   // AudioTools library coming soon
#include "AudioTools/AudioLibs/VS1053Stream.h"

// Display related stuff
NexButton b_Schw = NexButton(0, 1, "bschw");
NexButton b_bob = NexButton(0, 2, "bbob");
NexTouch *nex_listen_list[] =
    {
        &b_Schw,
        &b_bob,
        NULL};

void Schw_PopCallback(void *ptr);
void Schw_PushCallback(void *ptr);
void Bob_PopCallback(void *ptr);
void Bob_PushCallback(void *ptr);

// Audio related stuff
URLStream url("","");  // or replace with ICYStream to get metadata
VS1053Stream vs1053; // final output
StreamCopy copier(vs1053, url); // copy url to decoder


bool Setup_WiFi_();

void setup(void)
{

    setup_display();
    bool wifi = Setup_WiFi_();

    pinMode(BUILTIN_LED, OUTPUT);
}

void loop(void)
{
    nexLoop(nex_listen_list);
}

// Setup the display
void setup_display()
{
    nexInit();
    b_Schw.attachPush(Schw_PushCallback, &b_Schw);
    b_Schw.attachPop(Schw_PopCallback, &b_Schw);
    b_bob.attachPush(Bob_PushCallback, &b_bob);
    b_bob.attachPop(Bob_PopCallback, &b_bob);
    dbSerialPrintln("setup done");
}
void Schw_PopCallback(void *ptr)
{
    dbSerialPrintln("hot0PopCallback");
    dbSerialPrint("ptr=");
    dbSerialPrintln((uint32_t)ptr);
    digitalWrite(BUILTIN_LED, LOW);
}
void Schw_PushCallback(void *ptr)
{
    dbSerialPrintln("hot0PushCallback");
    dbSerialPrint("ptr=");
    dbSerialPrintln((uint32_t)ptr);
    digitalWrite(BUILTIN_LED, HIGH);
}
void Bob_PopCallback(void *ptr)
{
    dbSerialPrintln("hot1PopCallback");
    dbSerialPrint("ptr=");
    dbSerialPrintln((uint32_t)ptr);
}
void Bob_PushCallback(void *ptr)
{
    dbSerialPrintln("hot1PopCallback");
    dbSerialPrint("ptr=");
    dbSerialPrintln((uint32_t)ptr);
}
// Setup the WiFi
bool Setup_WiFi_()
{
    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    WiFiManager wm;
    bool res;
    res = wm.autoConnect("AutoConnectAP"); // anonymous ap
    if (!res)
    {
        dbSerialPrintln("Failed to connect");
        ESP.restart();
    }
    else
    {
        dbSerialPrintln("connected...yeey :)");
        return true;
    }
}