/**
 * @example CompHotspot.ino
 *
 * @par How to Use
 * This example shows that ,when the hot component on the Nextion screen is pressed or released,
 * the debug serial will output the debug information every time. 
 *
 * @author  Wu Pengfei (email:<pengfei.wu@itead.cc>)
 * @date    2015/7/10
 * @updated 2016/12/25 bring HMI up to v0.32 to avoid too old issues
 * @convert by Patrick Martin, no other changes made
 * @copyright 
 * Copyright (C) 2014-2015 ITEAD Intelligent Systems Co., Ltd. \n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */
#include "Nextion.h"
#include "NexButton.h"


NexButton b_Schw    = NexButton(0, 1, "bschw");
NexButton b_bob    = NexButton(0, 2, "bbob");



NexTouch *nex_listen_list[] = 
{
    &b_Schw,
    &b_bob,
    NULL
};




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

void setup(void)
{
    
     
    nexInit();
   
    b_Schw.attachPush(Schw_PushCallback, &b_Schw);
    b_Schw.attachPop(Schw_PopCallback, &b_Schw);
    b_bob.attachPush(Bob_PushCallback, &b_bob);
    b_bob.attachPop(Bob_PopCallback, &b_bob);
    dbSerialPrintln("setup done");
     pinMode(BUILTIN_LED, OUTPUT);
}

void loop(void)
{
    nexLoop(nex_listen_list);
}